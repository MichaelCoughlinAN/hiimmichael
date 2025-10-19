import asyncio
import websockets

clients = set()

async def register(websocket):
    clients.add(websocket)

async def unregister(websocket):
    clients.remove(websocket)

async def websockets_handler(websocket, path):
    await register(websocket)
    try:
        async for message in websocket:
            # Broadcast incoming message to all clients except the sender
            for client in clients:
                if client != websocket:
                    await client.send(message)
    finally:
        await unregister(websocket)

async def main():
    async with websockets.serve(websockets_handler, "0.0.0.0", 8765):
        await asyncio.Future()  # run forever

if __name__ == "__main__":
    asyncio.run(main())
