// Note: Not used currently, but may be in future implementations. --- IGNORE ---

use std::sync::Arc;
use v4l::{Device, Format, FourCC};
use crate::control_socket::Settings;

pub struct CaptureController {
    settings: Arc<Settings>,
    camera: Option<Device>,
}

impl CaptureController {
    pub fn new(settings: Arc<Settings>) -> Self {
        CaptureController {
            settings,
            camera: None,
        }
    }

    pub fn start(&mut self) -> Result<(), Box<dyn std::error::Error>> {
        println!("CaptureController started successfully.");
        Ok(())
    }
}
