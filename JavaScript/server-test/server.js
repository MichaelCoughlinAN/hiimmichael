const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const path = require('path');
const { spawn } = require('child_process');

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

// Generic RTSP stream URL (replace with your own)
const rtspStreamURL = 'rtsp://your-stream-server:8554/stream';

// Serve static files from the "public" folder
app.use(express.static(path.join(__dirname, 'public')));

// WebSocket connection handler
wss.on('connection', (ws) => {
    console.log('Client connected');

    // Spawn GStreamer process
    const gst = spawn('gst-launch-1.0', [
        'rtspsrc', `location=${rtspStreamURL}`, 'latency=0',
        '!', 'decodebin',
        '!', 'videoconvert',
        '!', 'jpegenc',
        '!', 'fdsink'
    ]);

    gst.stderr.on('data', (data) => console.error(`GStreamer stderr: ${data}`));

    let dataBuffer = Buffer.alloc(0);

    // Stream JPEG frames to client
    gst.stdout.on('data', (data) => {
        dataBuffer = Buffer.concat([dataBuffer, data]);
        let endOfFrameIndex = dataBuffer.indexOf(Buffer.from([0xFF, 0xD9])); // JPEG end marker

        while (endOfFrameIndex !== -1) {
            const frame = dataBuffer.slice(0, endOfFrameIndex + 2);
            if (ws.readyState === WebSocket.OPEN) {
                ws.send(frame, { binary: true });
            }

            dataBuffer = dataBuffer.slice(endOfFrameIndex + 2);
            endOfFrameIndex = dataBuffer.indexOf(Buffer.from([0xFF, 0xD9]));
        }
    });

    ws.on('close', () => {
        console.log('Client disconnected');
        gst.kill('SIGINT');
    });

    ws.on('error', (err) => {
        console.error('WebSocket error:', err);
        gst.kill('SIGINT');
    });
});

// Serve main page
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Start server
const PORT = 8081;
server.listen(PORT, () => console.log(`Server running at http://localhost:${PORT}`));
