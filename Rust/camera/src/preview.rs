// Note: Not used but file compiles --- IGNORE ---

use std::sync::{Arc, Mutex};
use std::collections::VecDeque;
use warp::Filter;
use image::{ImageBuffer, Rgba};
use tokio;

#[derive(Clone)]
struct Settings {
    key_file: Option<String>,
    cert_file: Option<String>,
}

#[derive(Clone)]
struct Preview {
    settings: Arc<Settings>,
    img_queue: Arc<Mutex<VecDeque<ImageBuffer<Rgba<u8>, Vec<u8>>>>>,
    auth_token: Arc<Mutex<String>>,
}

impl Preview {
    fn new(settings: Arc<Settings>) -> Self {
        Self {
            settings,
            img_queue: Arc::new(Mutex::new(VecDeque::new())),
            auth_token: Arc::new(Mutex::new(String::new())),
        }
    }

    async fn handle_request(&self, auth_header: String) -> Result<impl warp::Reply, warp::Rejection> {
        let auth_token = self.auth_token.lock().unwrap();
        if auth_header == *auth_token {
            Ok(warp::http::Response::builder()
                .status(200)
                .body("Authorized".to_string()))
        } else {
            Ok(warp::http::Response::builder()
                .status(401)
                .body("Unauthorized".to_string()))
        }
    }

    async fn start_server(self) {
        let preview_clone = self.clone();
        let route = warp::get()
            .and(warp::header::<String>("authorization"))
            .and_then(move |auth_header| {
                let inner_preview = preview_clone.clone();
                async move { 
                    inner_preview.handle_request(auth_header).await
                }
            });

        warp::serve(route)
            .run(([0, 0, 0, 0], 5000)) // Bind to port 5000
            .await;
    }
}

#[tokio::main]
async fn main() {
    let settings = Arc::new(Settings {
        key_file: Some("path/to/key.pem".to_string()),
        cert_file: Some("path/to/cert.pem".to_string()),
    });

    let preview = Preview::new(settings);

    // Start the server
    preview.start_server().await;
}
