use std::sync::{mpsc, Arc, Mutex};
use std::thread;
use std::time::{Duration, Instant};
use image::GrayImage;
use image::buffer::ConvertBuffer;
use image::imageops::FilterType;
use image::{DynamicImage, RgbImage, GenericImageView};
use image::imageops::colorops::grayscale;
use rxing::{BinaryBitmap, common::HybridBinarizer, RGBLuminanceSource, MultiFormatReader};
use rxing::Reader;

struct Settings {
    delay_between_same_symbol: f64, // in seconds
    delay_between_scans: f64, // in seconds
}

pub struct BarcodeDetect {
    settings: Arc<Settings>,
    last_barcode: Arc<Mutex<String>>,
    last_time: Arc<Mutex<Instant>>,
    enable_queue: mpsc::Receiver<bool>,
    is_enabled: bool,
}

impl BarcodeDetect {
    fn new(settings: Arc<Settings>) -> Self {
        let (tx, rx) = mpsc::channel::<bool>();

        BarcodeDetect {
            settings,
            last_barcode: Arc::new(Mutex::new(String::new())),
            last_time: Arc::new(Mutex::new(Instant::now())),
            enable_queue: rx,
            is_enabled: true,
        }
    }

    fn set_enable(tx: &mpsc::Sender<bool>, enable: bool) {
        tx.send(enable).expect("Failed to send enable signal");
    }

    fn process(&mut self, img: &GrayImage) -> Option<serde_json::Value> {
        if let Ok(is_enabled) = self.enable_queue.try_recv() {
            self.is_enabled = is_enabled;
        }

        if self.is_enabled {
            // Convert image buffer to grayscale
            let gray_img: DynamicImage = DynamicImage::ImageLuma8(grayscale(img));

            // Convert grayscale image to RGB format
            let rgb_img: RgbImage = gray_img.into_rgb8();
            let buffer: Vec<u8> = rgb_img.into_raw();

            // Decode QR code from the buffer
            let result = decode_qr_from_buffer(&buffer);

            if let Ok(qr_data) = result {
                let mut last_barcode = self.last_barcode.lock().unwrap();
                let mut last_time = self.last_time.lock().unwrap();

                if *last_barcode != qr_data || last_time.elapsed().as_secs_f64() > self.settings.delay_between_same_symbol {
                    *last_barcode = qr_data.clone();
                    *last_time = Instant::now();
                    thread::sleep(Duration::from_secs_f64(self.settings.delay_between_scans));
                    return Some(serde_json::json!({"control": {"command": "barcodefound", "barcode": qr_data}}));
                }
            }
        }

        None
    }
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

fn main() {
    let settings = Arc::new(Settings {
        delay_between_same_symbol: 5.0,
        delay_between_scans: 0.5,
    });

    let mut detector = BarcodeDetect::new(settings.clone());
    let (tx, _rx) = mpsc::channel::<bool>();

    // Placeholder for actual image fetching and processing
    let img = GrayImage::new(640, 480); // Example image

    BarcodeDetect::set_enable(&tx, true); // Enable barcode detection
    if let Some(result) = detector.process(&img) {
        println!("{:?}", result);
    }
}