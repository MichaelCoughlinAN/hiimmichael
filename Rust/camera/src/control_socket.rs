// Note: Not used but file compiles --- IGNORE ---

use std::sync::Arc;
use tokio::sync::{Mutex, mpsc};
use warp::Filter;
use futures_util::stream::StreamExt;


pub struct ControlSocket {
    settings: Settings,
    pending_in: mpsc::Receiver<serde_json::Value>,
    pending_out: mpsc::Sender<serde_json::Value>,
    websockets: Vec<warp::ws::WebSocket>,
}

impl ControlSocket {
    pub fn new(settings: Settings) -> Self {
        let (tx, rx) = mpsc::channel(100); // Buffer size of 100, adjust as needed
        ControlSocket {
            settings,
            pending_in: rx,
            pending_out: tx,
            websockets: Vec::new(),
        }
    }

    pub async fn recv(&mut self) -> Option<serde_json::Value> {
        self.pending_in.recv().await
    }

    pub async fn send(&self, msg: serde_json::Value) {
        let _ = self.pending_out.send(msg).await; // Ignoring the result for simplicity
    }

    pub async fn run(&self) {
        let routes = warp::ws()
            .map(|ws: warp::ws::Ws| {
                ws.on_upgrade(|websocket| async move {
                    let (tx, mut rx) = websocket.split();
                    while let Some(msg) = rx.next().await {
                        match msg {
                            Ok(msg) => {
                                if let Ok(s) = msg.to_str() {
                                    println!("> {}", s);
                                    // Process the message and send responses if needed
                                }
                            }
                            Err(e) => {
                                eprintln!("Error: {}", e);
                                break;
                            }
                        }
                    }
                })
            });

        warp::serve(routes)
            .run(([127, 0, 0, 1], self.settings.server_port))
            .await;
    }
}

#[tokio::main]
async fn main() {
    let settings = Settings { server_port: 5431 };
    let control_socket = ControlSocket::new(settings);
    control_socket.run().await;
}

pub struct Settings {
    server_port: u16,
}
