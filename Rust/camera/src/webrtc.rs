use webrtc::peer_connection::RTCPeerConnection;
use webrtc::peer_connection::configuration::RTCConfiguration;
use webrtc::ice_transport::ice_credential_type::RTCIceCredentialType;
use webrtc::ice_transport::ice_server::RTCIceServer;
use webrtc::api::APIBuilder;
use anyhow::Result;

pub async fn create_peer_connection() -> Result<RTCPeerConnection> {
    let ice_servers = vec![
        RTCIceServer {
            urls: vec!["stun:stun.example.com:3478".to_string()],
            username: "username".to_string(),
            credential: "credential".to_string(),
            credential_type: RTCIceCredentialType::Password, 
        },
        // More ICE servers if needed
    ];

    let config = RTCConfiguration {
        ice_servers,
        ..Default::default()
    };

    let api = APIBuilder::new().build();

    api.new_peer_connection(config).await.map_err(anyhow::Error::from)
}

//     let video_file = matches.value_of("video").unwrap();
//     if !Path::new(video_file).exists() {
//         return Err(Error::new(format!("video file: '{video_file}' not exist")).into());
//     }

//     // Everything below is the WebRTC-rs API! Thanks for using it ❤️.

//     // Create a MediaEngine object to configure the supported codec
//     let mut m = MediaEngine::default();

//     m.register_default_codecs()?;

//     // Create a InterceptorRegistry. This is the user configurable RTP/RTCP Pipeline.
//     // This provides NACKs, RTCP Reports and other features. If you use `webrtc.NewPeerConnection`
//     // this is enabled by default. If you are manually managing You MUST create a InterceptorRegistry
//     // for each PeerConnection.
//     let mut registry = Registry::new();

//     // Use the default set of Interceptors
//     registry = register_default_interceptors(registry, &mut m)?;

//     // Create the API object with the MediaEngine
//     let api = APIBuilder::new()
//         .with_media_engine(m)
//         .with_interceptor_registry(registry)
//         .build();

//     // Prepare the configuration
//     let config = RTCConfiguration {
//         ice_servers: vec![RTCIceServer {
//             urls: vec!["stun:stun.l.google.com:19302".to_owned()],
//             ..Default::default()
//         }],
//         ..Default::default()
//     };

//     // Create a new RTCPeerConnection
//     let peer_connection = Arc::new(api.new_peer_connection(config).await?);

//     let (done_tx, mut done_rx) = tokio::sync::mpsc::channel::<()>(1);
//     let video_done_tx = done_tx.clone();

//     // Create a video track
//     let video_track = Arc::new(TrackLocalStaticSample::new(
//         RTCRtpCodecCapability {
//             mime_type: MIME_TYPE_VP8.to_owned(),
//             ..Default::default()
//         },
//         "video".to_owned(),
//         "webrtc-rs".to_owned(),
//     ));

//     // Add this newly created track to the PeerConnection
//     let rtp_sender = peer_connection
//         .add_track(Arc::clone(&video_track) as Arc<dyn TrackLocal + Send + Sync>)
//         .await?;

//     // Read incoming RTCP packets
//     // Before these packets are returned they are processed by interceptors. For things
//     // like NACK this needs to be called.
//     tokio::spawn(async move {
//         let mut rtcp_buf = vec![0u8; 1500];
//         while let Ok((_, _)) = rtp_sender.read(&mut rtcp_buf).await {}
//         Result::<()>::Ok(())
//     });

//     let notify_tx = Arc::new(Notify::new());
//     let notify_video = notify_tx.clone();

//     let video_file_name = video_file.to_owned();
//     tokio::spawn(async move {
//         // Open a IVF file and start reading using our IVFReader
//         let file = File::open(video_file_name)?;
//         let reader = BufReader::new(file);
//         let (mut ivf, header) = IVFReader::new(reader)?;

//         // Wait for connection established
//         notify_video.notified().await;

//         println!("play video from disk file output.ivf");

//         // Send our video file frame at a time. Pace our sending so we send it at the same speed it should be played back as.
//         // This isn't required since the video is timestamped, but we will such much higher loss if we send all at once.
//         let sleep_time = Duration::from_millis(
//             ((1000 * header.timebase_numerator) / header.timebase_denominator) as u64,
//         );
//         loop {
//             let mut frame = match ivf.parse_next_frame() {
//                 Ok((frame, _)) => frame,
//                 Err(err) => {
//                     println!("All video frames parsed and sent: {err}");
//                     break;
//                 }
//             };

//             // Encrypt video using XOR Cipher
//             for b in &mut frame[..] {
//                 *b ^= CIPHER_KEY;
//             }

//             tokio::time::sleep(sleep_time).await;

//             video_track
//                 .write_sample(&Sample {
//                     data: frame.freeze(),
//                     duration: Duration::from_secs(1),
//                     ..Default::default()
//                 })
//                 .await?;
//         }

//         let _ = video_done_tx.try_send(());

//         Result::<()>::Ok(())
//     });

//     // Set the handler for ICE connection state
//     // This will notify you when the peer has connected/disconnected
//     peer_connection.on_ice_connection_state_change(Box::new(
//         move |connection_state: RTCIceConnectionState| {
//             println!("Connection State has changed {connection_state}");
//             if connection_state == RTCIceConnectionState::Connected {
//                 notify_tx.notify_waiters();
//             }
//             Box::pin(async {})
//         },
//     ));

//     // Set the handler for Peer connection state
//     // This will notify you when the peer has connected/disconnected
//     peer_connection.on_peer_connection_state_change(Box::new(move |s: RTCPeerConnectionState| {
//         println!("Peer Connection State has changed: {s}");

//         if s == RTCPeerConnectionState::Failed {
//             // Wait until PeerConnection has had no network activity for 30 seconds or another failure. It may be reconnected using an ICE Restart.
//             // Use webrtc.PeerConnectionStateDisconnected if you are interested in detecting faster timeout.
//             // Note that the PeerConnection may come back from PeerConnectionStateDisconnected.
//             println!("Peer Connection has gone to failed exiting");
//             let _ = done_tx.try_send(());
//         }

//         Box::pin(async {})
//     }));

//     // Wait for the offer to be pasted
//     let line = signal::must_read_stdin()?;
//     let desc_data = signal::decode(line.as_str())?;
//     let offer = serde_json::from_str::<RTCSessionDescription>(&desc_data)?;

//     // Set the remote SessionDescription
//     peer_connection.set_remote_description(offer).await?;

//     // Create an answer
//     let answer = peer_connection.create_answer(None).await?;

//     // Create channel that is blocked until ICE Gathering is complete
//     let mut gather_complete = peer_connection.gathering_complete_promise().await;

//     // Sets the LocalDescription, and starts our UDP listeners
//     peer_connection.set_local_description(answer).await?;

//     // Block until ICE Gathering is complete, disabling trickle ICE
//     // we do this because we only can exchange one signaling message
//     // in a production application you should exchange ICE Candidates via OnICECandidate
//     let _ = gather_complete.recv().await;

//     // Output the answer in base64 so we can paste it in browser
//     if let Some(local_desc) = peer_connection.local_description().await {
//         let json_str = serde_json::to_string(&local_desc)?;
//         let b64 = signal::encode(&json_str);
//         println!("{b64}");
//     } else {
//         println!("generate local_description failed!");
//     }



//     peer_connection.close().await?;

