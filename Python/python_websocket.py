import asyncio
import websockets
import json  # Import the json module

async def send_command(uri, command, description="", count=0):
    # Construct the command as a dictionary and then convert it to a JSON string
    command_dict = {
        "command": command,
    }
    command_json = json.dumps(command_dict)

    async with websockets.connect(uri) as websocket:
        print(f"Sending: {command_json}")
        await websocket.send(command_json)  # Send the JSON string
        response = await websocket.recv()
        print(f"Received: {response}")

async def main():
    # await send_command("ws://192.168.12.214:8080", "snapshot")
    await send_command("ws://192.168.12.214:8080", "shutdown")

if __name__ == "__main__":
    asyncio.run(main())
