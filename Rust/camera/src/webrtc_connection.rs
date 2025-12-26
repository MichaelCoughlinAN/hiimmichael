use std::sync::Arc;
use webrtc::api::{APIBuilder, media_engine::MediaEngine, interceptor_registry::register_default_interceptors};
use webrtc::peer_connection::{RTCPeerConnection, configuration::RTCConfiguration};
use webrtc::ice_transport::ice_server::RTCIceServer;
use webrtc::ice_transport::ice_credential_type::RTCIceCredentialType;
use serde_json::{json, Value};
use tokio_tungstenite::{connect_async, tungstenite::protocol::Message};
use url::Url;
use webrtc::peer_connection::sdp::session_description::RTCSessionDescription;
use futures::stream::StreamExt;
use serde::{Deserialize, Serialize};
use webrtc::ice_transport::ice_candidate::RTCIceCandidateInit;
use webrtc::Error;
use futures::SinkExt;
use webrtc::track::track_local::track_local_static_sample::TrackLocalStaticSample;
use webrtc::rtp_transceiver::rtp_codec::{RTCRtpCodecCapability, RTCRtpCodecParameters, RTPCodecType};

#[derive(Serialize, Deserialize)]
struct SignalingMessage {
    #[serde(rename = "type")]
    msg_type: String,
    sdp: Option<String>,
    candidate: Option<String>,
}

pub struct VideoFormat {
    pub width: u32,
    pub height: u32,
    pub fourcc: String, 
}

pub async fn create_peer_connection() -> Result<RTCPeerConnection, Error> {
    let mut media_engine = MediaEngine::default();
    media_engine.register_default_codecs()?;

    let mut registry = webrtc::interceptor::registry::Registry::new();
    let registry = register_default_interceptors(registry, &mut media_engine)?;

    let api = APIBuilder::new()
        .with_media_engine(media_engine)
        .with_interceptor_registry(registry)
        .build();

    let config = RTCConfiguration {
        ice_servers: vec![
            RTCIceServer {
                urls: vec!["stun:stun.example.com:3478".to_string()],
                ..Default::default()
            },
            RTCIceServer {
                urls: vec![
                    "turn:turn.example.com:3478".to_string(),
                    "turn:turn.example.com:5349?transport=tcp".to_string(),
                ],
                username: "replace_username_here".to_string(),
                credential: "replace_password_here".to_string(),
                credential_type: RTCIceCredentialType::Password,
            }
        ],
        ..Default::default()
    };

    api.new_peer_connection(config).await
}

pub async fn start_webrtc_signaling(
    peer_connection: Arc<RTCPeerConnection>,
    username: &str,
    room: &str
) -> Result<(), Error> {
    let ws_url = "ws://turn.example.com:5004";
    let (mut ws_stream, _) = connect_async(Url::parse(ws_url).unwrap()).await.expect("Can't connect to WebSocket");

    // Send "join" message similar to the JavaScript logic
    let join_msg = json!({
        "username": username,
        "room": room,
        "action": "join"
    });
    ws_stream.send(Message::Text(join_msg.to_string())).await.map_err(|e| webrtc::Error::new(e.to_string()))?;

    while let Some(message) = ws_stream.next().await {
        match message {
            Ok(Message::Text(text)) => {
                let data: Value = serde_json::from_str(&text).expect("Failed to parse JSON");

                match data["type"].as_str() {
                    Some("offer") => {
                        let offer = serde_json::from_value::<RTCSessionDescription>(data["sdp"].clone()).expect("Failed to parse offer");
                        peer_connection.set_remote_description(offer).await?;

                        let answer = peer_connection.create_answer(None).await?;
                        peer_connection.set_local_description(answer.clone()).await?;

                        let msg = json!({
                            "type": "answer",
                            "sdp": answer.sdp
                        });
                        ws_stream.send(Message::Text(msg.to_string())).await.map_err(|e| webrtc::Error::new(e.to_string()))?;
                    },
                    Some("answer") => {
                        let answer = serde_json::from_value::<RTCSessionDescription>(data["sdp"].clone()).expect("Failed to parse answer");
                        peer_connection.set_remote_description(answer).await?;
                    },
                    Some("candidate") => {
                        if let Some(candidate) = data["candidate"].as_str() {
                            let ice_candidate = serde_json::from_str::<RTCIceCandidateInit>(&candidate).expect("Failed to parse ICE candidate");
                            peer_connection.add_ice_candidate(ice_candidate).await?;
                        }
                    },
                    _ => println!("Unknown signaling message type"),
                }
            },
            Err(e) => eprintln!("WebSocket error: {:?}", e),
            _ => {}
        }
    }

    Ok(())
}