// Note: Not used but file compiles --- IGNORE ---

use image::{ImageBuffer, Rgba};
use std::sync::{mpsc, Arc, Mutex};
use std::thread;
use std::path::PathBuf;
use chrono::Utc;

struct Settings {
    image_directory: String,
    extension: String,
}

struct Snapshot {
    settings: Arc<Settings>,
    snapshot_directory: PathBuf,
    extension: String,
    snapshot_names: Arc<Mutex<mpsc::Sender<String>>>,
    snapshot_taken: Arc<Mutex<bool>>,
    description: String,
}

impl Snapshot {
    fn new(settings: Arc<Settings>) -> Self {
        let (tx, _) = mpsc::channel::<String>();

        // Clone the Arc before moving it to allow further usage
        let settings_clone = Arc::clone(&settings);

        Snapshot {
            settings: settings_clone,
            snapshot_directory: PathBuf::from(&settings.image_directory),
            extension: settings.extension.clone(),
            snapshot_names: Arc::new(Mutex::new(tx)),
            snapshot_taken: Arc::new(Mutex::new(false)),
            description: "startup".to_string(),
        }
    }

    fn take_snapshot(&self, description: &str) {
        println!("Snapshot: queuing up {}", description);
        let tx = self.snapshot_names.lock().unwrap();
        tx.send(description.to_string()).unwrap();
    }

    fn process(&self, img: &ImageBuffer<Rgba<u8>, Vec<u8>>) {
        let time_stamp = Utc::now().format("%Y-%m-%dT%H:%M:%SZ").to_string();
        let file_name = self.snapshot_directory.join(format!("{}-{}.{}", self.description, time_stamp, self.extension));

        println!("Snapshot: writing to {:?}", file_name);

        img.save(file_name).unwrap();

        let mut taken = self.snapshot_taken.lock().unwrap();
        if self.description != "startup" {
            *taken = true;
        }


    }
}

fn main() {
    let settings = Arc::new(Settings {
        image_directory: "snapshots".to_string(),
        extension: "jpeg".to_string(),
    });

    let snapshot = Snapshot::new(settings.clone());
    let snapshot_clone = Arc::new(Mutex::new(snapshot));  // Wrap the snapshot in an Arc<Mutex<>> for shared access

    // Example usage of Snapshot struct in a separate thread
    let snapshot_for_thread = Arc::clone(&snapshot_clone);  // Clone the Arc for thread use
    thread::spawn(move || {
        let img = ImageBuffer::new(800, 600);
        let snap = snapshot_for_thread.lock().unwrap();
        snap.process(&img);
    });

    // The main thread retains ownership of snapshot and can still use it
    let snap = snapshot_clone.lock().unwrap();
    snap.take_snapshot("test snapshot");
}
