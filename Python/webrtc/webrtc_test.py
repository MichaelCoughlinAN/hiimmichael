import asyncio
from aiortc import (
    RTCPeerConnection,
    RTCSessionDescription,
    RTCConfiguration,
    RTCIceServer,
    RTCIceCandidate,
    MediaStreamTrack
)
from aiortc.contrib.media import MediaPlayer
import socketio


class VideoStreamTrack(MediaStreamTrack):
    """
    Simple passthrough track that reads frames from a MediaPlayer.
    """
    kind = "video"

    def __init__(self, player):
        super().__init__()
        self.player = player

    async def recv(self):
        frame = await self.player.video.recv()
        return frame


async def run_peer_connection(server_url: str, username: str, room: str) -> None:
    """
    Establish a WebRTC peer connection and exchange ICE candidates and SDP
    through a Socket.IO signaling server.
    """

    # WebRTC ICE configuration. Credentials must be provided via environment vars or config.
    config = RTCConfiguration(
        iceServers=[
            RTCIceServer(urls=["stun:turn.yourdomain.net:3478"]),
            RTCIceServer(
                urls=[
                    "turn:turn.yourdomain.net:3478",
                    "turn:turn.yourdomain.net:5349?transport=tcp"
                ],
                username="",        # Replace externally if needed
                credential=""       # Replace externally if needed
            )
        ]
    )

    pc = RTCPeerConnection(configuration=config)

    # Open default video device
    player = MediaPlayer(
        "/dev/video0",
        format="v4l2",
        options={"video_size": "640x480"}
    )
    track = VideoStreamTrack(player)
    pc.addTrack(track)

    sio = socketio.AsyncClient()

    @sio.event
    async def connect():
        print("Connected to signaling server")
        await sio.emit("join", {"username": username, "room": room})

    @sio.event
    async def disconnect():
        print("Disconnected from signaling server")

    @pc.on("icecandidate")
    async def on_ice_candidate(event):
        if event.candidate:
            await sio.emit(
                "candidate",
                {
                    "type": "candidate",
                    "candidate": event.candidate.candidate,
                    "sdpMid": event.candidate.sdpMid,
                    "sdpMLineIndex": event.candidate.sdpMLineIndex
                }
            )

    @sio.on("offer")
    async def on_offer(data):
        offer = RTCSessionDescription(sdp=data["sdp"], type="offer")
        await pc.setRemoteDescription(offer)

        answer = await pc.createAnswer()
        await pc.setLocalDescription(answer)

        await sio.emit("answer", {"type": "answer", "sdp": answer.sdp})

    @sio.on("candidate")
    async def on_candidate(data):
        candidate = RTCIceCandidate(
            sdpMid=data["sdpMid"],
            sdpMLineIndex=data["sdpMLineIndex"],
            candidate=data["candidate"]
        )
        await pc.addIceCandidate(candidate)

    await sio.connect(f"{server_url}:5004")
    await sio.wait()


def main():
    server_url = "https://turn.yourdomain.net"
    username = "example_user"
    room = "example_room"
    asyncio.run(run_peer_connection(server_url, username, room))


if __name__ == "__main__":
    main()
