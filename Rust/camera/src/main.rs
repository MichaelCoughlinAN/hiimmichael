#![allow(warnings)]

mod barcode_detect;
mod webrtc_connection;

use ab_glyph::{FontRef, PxScale};
use async_stream::stream;
use barcode_detect::BarcodeDetect;
use chrono::prelude::*;
use futures::{stream::Stream as AsyncStream, SinkExt, StreamExt};
use image::{DynamicImage, ImageError, ImageFormat, Rgb, RgbImage};
use image::io::Reader as ImageReader;
use imageproc::drawing::draw_text_mut;
use rxing::{BinaryBitmap, common::HybridBinarizer, MultiFormatReader, Reader, RGBLuminanceSource};
use serde::{Deserialize, Serialize};
use serde_json::{self, json, Value as JsonValue};
use std::{
    collections::HashMap, error::Error, fs::{self, File, read_to_string}, io::{self, Cursor, Read, Write},
    path::Path, process::{Command, Stdio}, str, sync::{Arc, atomic::{AtomicBool, Ordering}, Mutex, mpsc::{channel, Receiver}}, 
    thread, time::{self, Duration, Instant, SystemTime}
};
use tokio::{io::AsyncWriteExt, net::TcpListener, sync::{mpsc, mpsc::Sender}};
use tokio_tungstenite::{accept_async, tungstenite::protocol::Message, WebSocketStream};
use turbojpeg::{compress_image, decompress_image, Subsamp};
use v4l::{
    buffer::Type, Device, FourCC, io::{mmap::Stream, traits::{CaptureStream, Stream as V4lStream}}, 
    prelude::MmapStream, video::Capture
};
use webrtc::{
    media::Sample,
    peer_connection::RTCPeerConnection,
    rtp_transceiver::rtp_codec::RTCRtpCodecCapability,
    track::track_local::{TrackLocal, track_local_static_rtp::TrackLocalStaticRTP, track_local_static_sample::TrackLocalStaticSample, TrackLocalWriter}
};
use webrtc_connection::*;

enum VideoCodec {
    VP8,
    H264,
}

enum StreamControl {
    Start,
    Stop,
}

struct Buffer {
    data: Vec<u8>,
    width: u32,
    height: u32,
}

#[derive(Debug, Deserialize)]
struct NetworkConfig {
    listener1_address: String,
    listener2_address: String,
}

#[derive(Debug, Deserialize)]
struct Config {
    video: VideoConfig,
    network: NetworkConfig,
}

#[derive(Debug, Deserialize)]
struct VideoConfig {
    full_paths: Vec<PathConfig>,
}

#[derive(Debug, Deserialize)]
struct PathConfig {
    key: String,
    identifier: String,
}

#[derive(Clone)]
struct VideoFormat {
    width: u32,
    height: u32,
    fourcc: FourCC,
}

impl VideoFormat {
    fn new(width: u32, height: u32, fourcc: FourCC) -> Self {
        VideoFormat { width, height, fourcc }
    }
}

#[derive(Deserialize, Serialize)]
struct CommandPacket {
    command: String,
    description: Option<String>,
    enabled: Option<bool>,
    count: Option<i32>,
    width: Option<i32>,
    height: Option<i32>,
    serial: Option<String>,
    job: Option<String>,
    userid: Option<String>,
}

#[derive(Clone)] 
struct SnapshotRequest {
    timestamp: std::time::Instant,
    filename: String,
}

fn load_config() -> Config {
    let config_str = read_to_string("config.toml").expect("Failed to read config file");
    toml::from_str(&config_str).expect("Failed to parse config file")
}

fn decode_qr_from_buffer(buffer: &[u8]) -> Result<String, Box<dyn std::error::Error>> {
    let img = image::load_from_memory(buffer)?.to_rgb8();
    let width = img.width() as usize;
    let height = img.height() as usize;
    let pixels: Vec<u32> = img.pixels()
        .map(|p| ((p[0] as u32) << 16) | ((p[1] as u32) << 8) | p[2] as u32)
        .collect();

    let source = RGBLuminanceSource::new_with_width_height_pixels(width, height, &pixels);
    let mut bitmap = BinaryBitmap::new(HybridBinarizer::new(source));

    let mut reader = MultiFormatReader::default();
    let result = reader.decode(&mut bitmap)?;
    
    Ok(result.getText().to_string())
}

fn draw_text_on_image(image: &mut DynamicImage, text: &str) {
    let font = FontRef::try_from_slice(include_bytes!("DejaVuSans.ttf")).unwrap();
    let height = 12.4;
    let scale = PxScale {
        x: height * 2.0,
        y: height,
    };

    let text_color = Rgb([255u8, 255u8, 255u8]);

    if let DynamicImage::ImageRgb8(ref mut image) = image {
        let image_dimensions = image.dimensions();
        let text_width = text.len() as u32 * (height as u32); 
        let text_height = height as u32;
        let x = (image_dimensions.0.saturating_sub(text_width)) as i32;
        let y = (image_dimensions.1.saturating_sub(text_height)) as i32;

        draw_text_mut(
            image,
            text_color,
            x, 
            y, 
            scale,
            &font,
            text,
        );
    }
}

fn add_timestamp_to_image(buffer: &[u8]) -> Result<Vec<u8>, Box<dyn Error>> {
    let now = Local::now(); 
    let timestamp = now.format("%Y-%m-%d %H:%M:%S").to_string();

    let rgb_image: RgbImage = turbojpeg::decompress_image(buffer)?;
    let mut image = DynamicImage::ImageRgb8(rgb_image);

    draw_text_on_image(&mut image, &timestamp);

    let image_buffer = match image {
        DynamicImage::ImageRgb8(img) => img,
        _ => return Err("Unsupported image format".into()),
    };
    
    let jpeg_data = turbojpeg::compress_image(&image_buffer, 95, turbojpeg::Subsamp::Sub2x2)?;
    Ok(jpeg_data.to_vec()) 
}

fn save_images_in_order(rx: Receiver<(usize, String, Vec<u8>)>) {
    let mut next_frame_to_save = 0;
    let mut frame_buffer: HashMap<usize, (String, Vec<u8>)> = HashMap::new();

    while let Ok((frame_number, file_name, data)) = rx.recv() {
        frame_buffer.insert(frame_number, (file_name, data));

        while let Some((file_name, data)) = frame_buffer.remove(&next_frame_to_save) {
            if std::fs::write(&file_name, &data).is_ok() {
                println!("Saved image {}", file_name);
            } else {
                eprintln!("Failed to save image {}", file_name);
            }
            next_frame_to_save += 1;
        }
    }
}

async fn process_stream<'a>(
    mut stream: Stream<'a>, 
    mut control_rx: tokio::sync::mpsc::Receiver<StreamControl>,
    mut snapshot_rx: tokio::sync::mpsc::Receiver<SnapshotRequest>,
) {
    let (tx, rx) = channel();
    let current_thread = thread::current();
    let thread_name = current_thread.name().unwrap_or("Unnamed Thread").to_string();
    
    println!("{} started processing", thread_name);

    thread::spawn(move || save_images_in_order(rx));

    let mut frame_count = 0;
    let start_time = Instant::now();
    let mut is_active = true; 

    while let Ok((buf, _meta)) = stream.next() {
        if let Ok(control_message) = control_rx.try_recv() {
            match control_message {
                StreamControl::Start => is_active = true,
                StreamControl::Stop => is_active = false,
            }
        }

        if is_active {
            let buf_clone = buf.to_vec();
            let tx_clone = tx.clone();
            let thread_name_clone = thread_name.clone();
            let frame_number = frame_count;

            if let Ok(snapshot_request) = snapshot_rx.try_recv() {
                println!("Taking snapshot at {:?}", snapshot_request.timestamp);
                thread::spawn(move || {
                    let add_timestamp_start = Instant::now();
    
                    match add_timestamp_to_image(&buf_clone) {
                        Ok(modified_buf) => {
                            let file_name = format!("frames/{}frame_{}.jpg", thread_name_clone, frame_number);
                            if tx_clone.send((frame_number, file_name, modified_buf)).is_err() {
                                eprintln!("Failed to send image to the saving thread.");
                            }
                        }
                        Err(e) => eprintln!("Failed to add timestamp to image: {}", e),
                    }
                    println!("Time taken for adding timestamp: {} ms", add_timestamp_start.elapsed().as_millis());
                });
            }

            frame_count += 1;

            if frame_count % 100 == 0 {
                let elapsed = start_time.elapsed().as_secs_f32();
                let fps = frame_count as f32 / elapsed;
                println!("{}: Processed {} frames in {:.2} seconds, FPS: {:.2}", thread_name, frame_count, elapsed, fps);
            }
        }
    }
}

fn initialize_video_stream<'a>(
    device_index: usize,
    format: &VideoFormat
) -> Result<Stream<'a>, String> {
    let dev = Device::new(device_index).map_err(|e| e.to_string())?;
    let mut fmt = dev.format().map_err(|e| e.to_string())?;

    fmt.width = format.width;
    fmt.height = format.height;
    fmt.fourcc = format.fourcc;
    dev.set_format(&fmt).map_err(|e| e.to_string())?;

    Stream::new(&dev, Type::VideoCapture).map_err(|e| e.to_string())
}

fn extract_video_numbers() -> HashMap<String, String> {
    let config = load_config();
    let output = Command::new("ls")
        .arg("-la")
        .arg("/dev/v4l/by-path")
        .output()
        .expect("Failed to execute command");

    let mut video_numbers = HashMap::new();

    if output.status.success() {
        let output_str = String::from_utf8(output.stdout).expect("Invalid UTF-8 sequence");

        for line in output_str.lines() {
            for path_config in &config.video.full_paths {
                if line.contains(&path_config.identifier) {
                    if let Some(path) = line.split("-> ").nth(1) {
                        if let Some(video_number) = path.split("video").last() {
                            let key = path_config.key.clone();
                            video_numbers.insert(key, video_number.trim().to_string());
                        }
                    }
                }
            }
        }
    }

    video_numbers
}

fn update_current_user_id(id: String) -> std::io::Result<()> {
    let mut file = File::create("/tmp/product_current_user_id_camera")?;
    file.write_all(id.as_bytes())?;
    file.flush()?;

    Command::new("sudo")
        .arg("mv")
        .arg("/tmp/product_current_user_id_camera")
        .arg("/tmp/product_current_user_id")
        .status()?;

    Ok(())
}

async fn check_for_printers(enable_printers: bool) -> JsonValue {
    println!("Checking for printers...");

    if enable_printers {
        let output = Command::new("./scripts/printer_enum.sh")
            .arg("enum")
            .stdout(Stdio::piped())
            .stderr(Stdio::null())
            .output();

        match output {
            Ok(output) => {
                let stdout = String::from_utf8_lossy(&output.stdout);
                serde_json::from_str(&stdout).unwrap_or_else(|_| JsonValue::Array(vec![]))
            },
            Err(e) => {
                println!("Error executing command: {:?}", e);
                JsonValue::Array(vec![])
            }
        }
    } else {
        JsonValue::Array(vec![])
    }
}

fn print_job(enable_printers: bool, packet: &CommandPacket) {
    if enable_printers {
        let job_length = packet.job.as_ref().map_or(0, |job| job.len() / 2);
        let default_serial = String::from("unknown");
        let serial = packet.serial.as_ref().unwrap_or(&default_serial);

        println!("Printing {} bytes to {}...", job_length, serial);

        if let Some(job_data) = packet.job.as_ref() {
            let output = Command::new("./scripts/printer_helper.sh")
                .arg("print")
                .arg(serial)
                .arg(job_data)
                .stderr(Stdio::null())
                .output();

            match output {
                Ok(output) => {
                    println!(" resulted in {} bytes output", output.stdout.len());
                },
                Err(e) => {
                    println!("Error executing print command: {:?}", e);
                }
            }
        } else {
            println!("No job data to print.");
        }
    }
}

async fn send_to_control(
    ws_stream: &mut WebSocketStream<tokio::net::TcpStream>, 
    command: &str, 
    message: &str) {
    let control_message = serde_json::json!({
        "command": command,
        "message": message
    }).to_string();

    if let Err(e) = ws_stream.send(Message::Text(control_message)).await {
        eprintln!("Error sending to control: {:?}", e);
    }
}

async fn process_webrtc_stream<'a, S>(
    mut stream: S,
    device_index: usize,
    format: VideoFormat,
    username: &str, 
    room: &str
) -> Result<(), Box<dyn std::error::Error>>
where
    S: AsyncStream<Item = Result<(Vec<u8>, v4l::buffer::Metadata), std::io::Error>> + Unpin + Send + 'a,
{
    let peer_connection = Arc::new(webrtc_connection::create_peer_connection().await?);
    webrtc_connection::start_webrtc_signaling(peer_connection.clone(), username, room).await?;

    let codec_capability = RTCRtpCodecCapability::default();
    let track_id = "video_track".to_string();
    let stream_id = "stream_id".to_string();

    let video_track = Arc::new(TrackLocalStaticSample::new(codec_capability, track_id, stream_id));
    let rtp_sender = peer_connection.add_track(video_track.clone()).await?;

    while let Some(Ok((buf, _meta))) = stream.next().await {
        let sample = Sample {
            data: buf.into(),
            duration: Duration::from_millis(33), 
            timestamp: SystemTime::now(), 
            packet_timestamp: 0, 
            prev_dropped_packets: 0, 
            prev_padding_packets: 0, 
        };
    
        video_track.write_sample(&sample).await?;
    }

    peer_connection.remove_track(&rtp_sender).await?;

    Ok(())
}

fn determine_mime_type(fourcc: &FourCC) -> String {
    match fourcc.to_string().as_str() {
        "VP80" => "video/VP8",
        "H264" => "video/H264",
        _ => "application/octet-stream",
    }.to_string()
}

fn create_video_track(format: &VideoFormat) -> Result<TrackLocalStaticRTP, Box<dyn std::error::Error>> {
    let mime_type = determine_mime_type(&format.fourcc);
    let video_track = TrackLocalStaticRTP::new(
        RTCRtpCodecCapability { mime_type, ..Default::default() },
        "video".to_string(),
        "webrtc-rs".to_string(),
    );

    Ok(video_track)
}

async fn handle_camera_control_socket(
    mut ws_stream: WebSocketStream<tokio::net::TcpStream>,
    tx: Sender<SnapshotRequest>, 
    snapshot_tx_1: tokio::sync::mpsc::Sender<SnapshotRequest>, 
    snapshot_tx_2: tokio::sync::mpsc::Sender<SnapshotRequest>,
    running: Arc<AtomicBool>,
    format_1: Arc<Mutex<VideoFormat>>,
    format_2: Arc<Mutex<VideoFormat>>,
) {
    while let Some(message_result) = ws_stream.next().await {
        match message_result {
            Ok(Message::Text(text)) => {
                println!("Received message: {:?}", text);
                if let Ok(packet) = serde_json::from_str::<CommandPacket>(&text) {
                    match packet.command.as_str() {
                        "quit" => break,
                        "snapshot" => {
                            println!("Snapshot command!");
                            let request = SnapshotRequest { filename: "".to_string(), timestamp: std::time::Instant::now() };
                            snapshot_tx_1.send(request.clone()).await.expect("Failed to send snapshot request to stream 1");
                            snapshot_tx_2.send(request).await.expect("Failed to send snapshot request to stream 2");
                        },
                        "shutdown" => {
                            println!("Shutdown command!");
                            running.store(false, Ordering::SeqCst);
                            break;
                        },
                        "multisnapshot" => {
                            println!("Multisnapshot command!");
                            let count = packet.count.unwrap_or(15);
                            for _ in 0..count {
                                let request = SnapshotRequest { filename: "".to_string(), timestamp: std::time::Instant::now() };
                                snapshot_tx_1.send(request.clone()).await.expect("Failed to send snapshot request to stream 1");
                                snapshot_tx_2.send(request.clone()).await.expect("Failed to send snapshot request to stream 2");
                            }
                        },
                        "videoresolution" => {
                            println!("Video resolution command received!");

                            let width = packet.width.unwrap_or(1920) as u32;
                            let height = packet.height.unwrap_or(1080) as u32;
                            
                            let mut front_camera_format = format_1.lock().unwrap();
                            *front_camera_format = VideoFormat::new(width, height, FourCC::new(b"MJPG"));
                            
                            let mut back_camera_format = format_2.lock().unwrap();
                            *back_camera_format = VideoFormat::new(width, height, FourCC::new(b"MJPG"));
                        },
                        "printquery" => {
                            println!("Print query command received!");
                            let printers = check_for_printers(true).await;

                            let data = json!({
                                "command": "printquery",
                                "printers": printers
                            });
                            
                            let message = serde_json::to_string(&data).unwrap();
                            
                            if let Err(e) = ws_stream.send(Message::Text(message)).await {
                                eprintln!("Error sending printer query response: {:?}", e);
                            }
                        },
                        "printjob" => {
                            println!("Print job command received!");
                            print_job(true, &packet);    
                        },
                        "impact_sensor_alarm" => {
                            println!("impact_sensor_alarm command!");
                            let request = SnapshotRequest { filename: "".to_string(), timestamp: std::time::Instant::now() };
                            snapshot_tx_1.send(request.clone()).await.expect("Failed to send snapshot request to stream 1");
                            snapshot_tx_2.send(request).await.expect("Failed to send snapshot request to stream 2");
                        },
                        "useridset" => {
                            if let Some(user_id_str) = packet.userid.as_deref() {
                                update_current_user_id(user_id_str.to_string());
                            } else {
                                println!("Userid is none");
                            }
                        },
                        _ => println!("Unknown command"),
                    }
                } else {
                    eprintln!("Failed to parse command from message");
                }
            },
            Err(e) => {
                eprintln!("Error in WebSocket stream: {:?}", e);
                break;
            },
            _ => {
                println!("Received an unhandled message type");
            }
        }

        let file_path = "/tmp/sensor_alert";
        let result = File::open(file_path).and_then(|mut f| {
            let mut message = String::new();
            f.read_to_string(&mut message)?;
            tokio::runtime::Runtime::new().unwrap().block_on(async {
                send_to_control(
                    &mut ws_stream, 
                    "impact_sensor_alarm", 
                    "The alarm message").await;
            });
            Ok(message)
        });

        if let Ok(message) = result {
            let pending_security_snap_count = 15; 
            for _ in 0..pending_security_snap_count {
                let request = SnapshotRequest { filename: "".to_string(), timestamp: std::time::Instant::now() };
                snapshot_tx_1.send(request.clone()).await.expect("Failed to send snapshot request to stream 1");
                snapshot_tx_2.send(request.clone()).await.expect("Failed to send snapshot request to stream 2");
            }
            if let Err(e) = fs::remove_file(file_path) {
                eprintln!("Failed to remove file: {:?}", e);
            }
    
            println!("Processed alarm with message: {}", message);
        } else {
            println!("No shock alert file found or reading failed.");
        }
    }
}

async fn handle_command_control_socket(
    mut ws_stream: WebSocketStream<tokio::net::TcpStream>,
    control_tx_1: Sender<StreamControl>,
    control_tx_2: Sender<StreamControl>,
    tx: Sender<SnapshotRequest>,
    running: Arc<AtomicBool>,
) {
    while let Some(message_result) = ws_stream.next().await {
        match message_result {
            Ok(Message::Text(text)) => {
                println!("Received message: {:?}", text);
                if let Ok(packet) = serde_json::from_str::<CommandPacket>(&text) {
                    match packet.command.as_str() {
                        "quit" => break,
                        "start_front_camera" => {
                            println!("Play front-facing camera command");
                            let _ = control_tx_1.send(StreamControl::Start).await;
                        },
                        "stop_front_camera" => {
                            println!("Stop front-facing camera command");
                            let _ = control_tx_1.send(StreamControl::Stop).await;
                        },
                        "start_back_camera" => {
                            println!("Play back-facing camera command");
                            let _ = control_tx_2.send(StreamControl::Start).await;
                        },
                        "stop_back_camera" => {
                            println!("Stop back facing camera command");
                            let _ = control_tx_2.send(StreamControl::Stop).await;
                        },
                        "stop_both_cameras" => {
                            println!("Stop back facing camera command");
                            control_tx_1.send(StreamControl::Stop).await;
                            control_tx_2.send(StreamControl::Stop).await;
                        },
                        "start_both_camera" => {
                            println!("Stop back facing camera command");
                            control_tx_1.send(StreamControl::Start).await;
                            control_tx_2.send(StreamControl::Start).await;
                        },
                        _ => println!("Unknown command"),
                    }
                } else {
                    eprintln!("Failed to parse command from message");
                }
            },
            Err(e) => {
                eprintln!("Error in WebSocket stream: {:?}", e);
                break;
            },
            _ => {
                println!("Received an unhandled message type");
            }
        }
    }
}

// TODO: Break code up into modules and functions instead of everything in the main function and main.rs
// TODO: Check for missing commands, missing functionality
// TODO: Test on a raspberrypi 
#[tokio::main]
async fn main() {
    let video_numbers = extract_video_numbers();

    if video_numbers.is_empty() {
        println!("No specified video devices found.");
        return;
    }

    let (mut device_index_1, mut device_index_2) = (None, None);

    for (key, video_number) in &video_numbers {
        match key.as_str() {
            "platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.1:1.0-video-index0" => device_index_1 = video_number.parse::<usize>().ok(),
            "platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.3:1.0-video-index0" => device_index_2 = video_number.parse::<usize>().ok(),
            _ => {}
        }
    }

    let device_index_1 = match device_index_1 {
        Some(index) => index,
        None => {
            println!("Camera index 1 not found.");
            return;
        },
    };

    let device_index_2 = match device_index_2 {
        Some(index) => index,
        None => {
            println!("Camera index 2 not found.");
            return;
        },
    };

    let shared_buffer_1 = Arc::new(Mutex::new(Buffer { data: Vec::new(), width: 3840, height: 2160 }));
    let shared_buffer_2 = Arc::new(Mutex::new(Buffer { data: Vec::new(), width: 3840, height: 2160 }));

    println!("Using camera device indices: {} and {}", device_index_1, device_index_2);

    let format_1 = Arc::new(Mutex::new(VideoFormat::new(1280, 720, FourCC::new(b"MJPG"))));
    let format_1_for_thread = format_1.clone();

    let format_2 = Arc::new(Mutex::new(VideoFormat::new(1280, 720, FourCC::new(b"MJPG"))));
    let format_2_for_thread = format_2.clone();

    let stream_2 = initialize_video_stream(device_index_2, &format_2.lock().unwrap()).expect("Failed to initialize stream 2");
    let stream_1 = initialize_video_stream(device_index_1, &format_1.lock().unwrap()).expect("Failed to initialize stream 1");

    let (control_tx_1, control_rx_1) = mpsc::channel::<StreamControl>(100); 
    let (control_tx_2, control_rx_2) = mpsc::channel::<StreamControl>(100);  
    
    let (snapshot_tx_1, snapshot_rx_1) = tokio::sync::mpsc::channel::<SnapshotRequest>(100);
    let (snapshot_tx_2, snapshot_rx_2) = tokio::sync::mpsc::channel::<SnapshotRequest>(100);
    
    let handle_1 = tokio::spawn(async move {
        process_stream(stream_1, control_rx_1, snapshot_rx_1).await;
    });
    
    let handle_2 = tokio::spawn(async move {
        process_stream(stream_2, control_rx_2, snapshot_rx_2).await;
    });

    let (tx, mut rx) = mpsc::channel::<SnapshotRequest>(100);
    let running = Arc::new(AtomicBool::new(true));

    tokio::spawn(async move {
        while let Some(request) = rx.recv().await {
            println!("Processing snapshot at {:?}", request.timestamp);
        }
    });

    let config = load_config(); 

    let listener = TcpListener::bind(&config.network.listener1_address)
        .await
        .expect("Failed to bind to address for listener 1");
    let listener2 = TcpListener::bind(&config.network.listener2_address)
        .await
        .expect("Failed to bind to address for listener 2");

    println!("Local camera socket server listening");
    println!("Camera control socket server listening");

    while running.load(Ordering::SeqCst) {
        tokio::select! {
            Ok((stream, _)) = listener.accept() => {
                let tx_clone = tx.clone();
                let running_clone = running.clone();
                let format_1_clone = format_1_for_thread.clone();
                let format_2_clone = format_2_for_thread.clone();
                let ws_stream = accept_async(stream).await.unwrap();
                
                tokio::spawn(handle_camera_control_socket(
                    ws_stream,
                    tx_clone,
                    snapshot_tx_1.clone(),
                    snapshot_tx_2.clone(),
                    running_clone,
                    format_1_clone,
                    format_2_clone,
                ));
            },
            Ok((stream, _)) = listener2.accept() => {
                let tx_clone = tx.clone();
                let running_clone = running.clone();
                let ws_stream = accept_async(stream).await.unwrap();
                
                tokio::spawn(handle_command_control_socket(
                    ws_stream,
                    control_tx_1.clone(),
                    control_tx_2.clone(),
                    tx_clone,
                    running_clone
                ));
            },
            _ = tokio::time::sleep(Duration::from_millis(500)) => {
                if !running.load(Ordering::SeqCst) {
                    break;
                }
            }
        }
    }
    
    println!("Exiting...");
}