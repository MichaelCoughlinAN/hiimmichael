// Note: Not used but file compiles

use std::sync::{mpsc, Arc, Mutex};
use std::time::{Duration, Instant};
use std::path::PathBuf;

struct Settings {
    video_width: i32,
    video_height: i32,
    file_extension: String,
    video_directory: String,
    video_time_limit: u64, // seconds
}

struct Recorder {
    settings: Arc<Settings>,
    command_queue: mpsc::Receiver<(String, String)>,
    current_video: Option<()>, // Placeholder for the video writer object
    description: String,
    current_filename: PathBuf,
    resolution: (i32, i32),
    start_time: Instant,
}

impl Recorder {
    fn new(settings: Arc<Settings>) -> Self {
        let (_, rx) = mpsc::channel::<(String, String)>();
        let resolution = (settings.video_width, settings.video_height);
        Recorder {
            settings,
            command_queue: rx,
            current_video: None,
            description: String::new(),
            current_filename: PathBuf::new(),
            resolution,
            start_time: Instant::now(),
        }
    }

    fn process(&mut self) {
        if let Ok((command, arg)) = self.command_queue.try_recv() {
            match command.as_str() {
                "start" => {
                    self.description = arg;
                    let description = self.description.clone(); // Clone the description
                    self.start_new_video(&description); // Pass the cloned description
                },
                "stop" => self.close_current_video(),
                _ => (),
            }
        }
    
        if self.current_video.is_some() &&
           Instant::now().duration_since(self.start_time) > Duration::from_secs(self.settings.video_time_limit) {
            let description = self.description.clone(); // Clone the description
            self.start_new_video(&description); // Pass the cloned description
        }
    }
    

    fn close_current_video(&mut self) {
        println!("Closing video: {}", self.current_filename.display());
        self.current_video = None;
    }

    fn start_new_video(&mut self, description: &str) {
        self.close_current_video();

        self.current_filename = PathBuf::from(format!("{}.{}", self.settings.video_directory, self.settings.file_extension));
        self.start_time = Instant::now();
        println!("Recorder: starting video {}", description);

        self.current_video = Some(()); // Placeholder for the video writer object initialization
    }
}

fn main() {
    let settings = Arc::new(Settings {
        video_width: 1920,
        video_height: 1080,
        file_extension: "avi".to_string(),
        video_directory: "videos".to_string(),
        video_time_limit: 600,
    });

    let mut recorder = Recorder::new(settings.clone());
    recorder.process(); // Simulating the recording process
}
