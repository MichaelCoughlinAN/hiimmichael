# Camera

A high-performance Rust-based camera application with multi-camera support, real-time video processing, barcode detection, WebRTC streaming, and printer integration.

## Author

Michael Coughlin

## Features

- **Multi-Camera Support**: Simultaneously capture from two video devices
- **Real-Time Video Processing**: Efficient frame capture and processing using V4L
- **Barcode/QR Code Detection**: Integrated barcode scanning with multiple libraries (ZXing, RXing, ZBar)
- **WebRTC Streaming**: Real-time video streaming capabilities
- **Snapshot Capture**: Take timestamped snapshots with automatic saving
- **Video Recording**: Record video streams to disk
- **Motion Detection**: Advanced motion analysis and detection
- **Printer Integration**: Print detected barcodes and labels
- **WebSocket Control**: Remote control interface for camera operations
- **Configurable Resolution**: Dynamic resolution changes
- **Multi-Threaded Processing**: Optimized for performance with async/await

## Requirements

- Linux system with V4L-compatible cameras
- Rust 1.70+ (2021 edition)
- Video devices accessible at `/dev/v4l/by-path/`

## Dependencies

Key crates used:
- `v4l` - Video4Linux camera interface
- `tokio` - Async runtime
- `webrtc` - WebRTC implementation
- `image` / `imageproc` - Image processing
- `zxing_rust`, `rxing`, `zbar-rust` - Barcode detection
- `warp` - Web framework
- `turbojpeg` - JPEG compression/decompression
- `serde` - Serialization
- `clap` - Command line argument parsing

## Installation

1. Clone the repository:
```bash
git clone <repository-url>
cd camera
```

2. Build the project:
```bash
cargo build --release
```

3. Configure your cameras in `config.toml`

## Configuration

Edit `config.toml` to configure:

- **Video Devices**: Specify camera device paths and identifiers
- **Network**: Set listener addresses for control interfaces
- **Directories**: Configure snapshot and video recording directories

Example configuration:
```toml
[video]
full_paths = [
    { key = "platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.1:1.0-video-index0", identifier = "usb-0:1.1:1.0-video-index0" },
    { key = "platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.3:1.0-video-index0", identifier = "usb-0:1.3:1.0-video-index0" }
]

[network]
listener1_address = "0.0.0.0:8080"  # Camera control
listener2_address = "0.0.0.0:8081"  # Stream control

[Snapshot]
image_directory = "/home/camera/camera_dump/"

[Recorder]
video_directory = "/home/camera/video_dump/"
```

## Usage

Run the application:
```bash
cargo run --release
```

The application will:
1. Detect and initialize configured cameras
2. Start WebSocket servers on configured ports
3. Begin processing video streams

## Control Interface

### Camera Control (Port 8080)
Send JSON commands via WebSocket:

- **Snapshot**: `{"command": "snapshot"}`
- **Multi-Snapshot**: `{"command": "multisnapshot", "count": 15}`
- **Change Resolution**: `{"command": "videoresolution", "width": 1920, "height": 1080}`
- **Print Query**: `{"command": "printquery"}`
- **Print Job**: `{"command": "printjob", "serial": "printer_id", "job": "data"}`
- **Set User ID**: `{"command": "useridset", "userid": "user123"}`
- **Shutdown**: `{"command": "shutdown"}`

### Stream Control (Port 8081)
Control camera streaming:

- **Start Front Camera**: `{"command": "start_front_camera"}`
- **Stop Front Camera**: `{"command": "stop_front_camera"}`
- **Start Back Camera**: `{"command": "start_back_camera"}`
- **Stop Back Camera**: `{"command": "stop_back_camera"}`
- **Start Both Cameras**: `{"command": "start_both_camera"}`
- **Stop Both Cameras**: `{"command": "stop_both_cameras"}`

## Printer Integration

The application includes printer support for barcode/label printing:

- **Printer Enumeration**: `./scripts/printer_enum.sh`
- **Print Helper**: `./scripts/printer_helper.sh print <serial> <data>`

Customize these scripts for your specific printer hardware.

## Modules

- `capture.rs` - Video capture handling
- `motion.rs` - Motion detection algorithms
- `preview.rs` - Video preview functionality
- `recorder.rs` - Video recording
- `snapshot.rs` - Image capture and processing
- `barcode_detect.rs` - Barcode/QR code detection
- `webrtc.rs` / `webrtc_connection.rs` - WebRTC streaming
- `control_socket.rs` - WebSocket control interfaces
- `image_consumer.rs` - Image processing pipeline

## Development

### Building
```bash
cargo build
```

### Testing
```bash
cargo test
```

### Running Individual Modules
Some modules can be run independently for testing:
```bash
cargo run --bin motion
cargo run --bin barcode_detect
# etc.
```

## Performance

- Optimized for multi-threaded processing
- Uses async I/O for network operations
- Efficient JPEG compression/decompression
- Frame buffering for smooth capture

## Troubleshooting

### Camera Detection Issues
- Ensure cameras are connected and accessible via V4L
- Check device permissions
- Verify configuration matches actual device paths

### Network Issues
- Confirm ports 8080 and 8081 are available
- Check firewall settings
- Verify WebSocket client configuration

### Performance Issues
- Adjust video resolution in config
- Monitor CPU usage during operation
- Ensure sufficient RAM for frame buffering

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Contributing

Michael Coughlin</content>
<parameter name="filePath">/Users/studio/Documents/GitHub/hiimmichael/Rust/camera/README.md