import asyncio
import websockets
import pyautogui
import time

async def listen_to_esp32():
    uri = "ws://192.168.137.105:81"  # Replace <ESP32_IP> with the IP address of your ESP32
    
    async with websockets.connect(uri) as websocket:
        is_listening = False

        while True:
            message = await websocket.recv()

            if message == "Start Speech-to-Text" and not is_listening:
                print("Starting speech-to-text")
                pyautogui.hotkey('win', 'h')  # Trigger Windows speech-to-text
                is_listening = True
                
            elif message == "Stop Speech-to-Text" and is_listening:
                print("Stopping speech-to-text and hitting Enter")
                time.sleep(1)
                pyautogui.press('enter')  # Simulate hitting Enter key
                is_listening = False

# Run the WebSocket client
asyncio.get_event_loop().run_until_complete(listen_to_esp32())
