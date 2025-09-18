

```markdown
# 🎤 Speech-to-Text (STT) Module  

This module uses **ESP32 + IR Sensor + WebSocket + Python** to control Windows Speech-to-Text automatically.  
When a hand is detected by the IR sensor, the ESP32 sends a WebSocket message to the Python client, which triggers the Windows Speech-to-Text tool.  
When the hand is removed, it stops listening and automatically presses **Enter**.

---

## 📂 Folder Structure
```

speech-to-text/
├── esp32/
│   └── stt\_esp32.ino      # ESP32 firmware (hand detection + WebSocket server)
├── python/
│   └── mic\_to\_text.py     # Python script to trigger Windows speech-to-text
└── README.md              # This documentation file

````

---

## 🧩 How It Works

### 🔧 ESP32 Code (`stt_esp32.ino`)
- Connects to Wi-Fi with your SSID & Password.
- Runs a WebSocket server on port **81**.
- Reads IR sensor state from GPIO 23:
  - **Hand Detected:**  
    - Turns **Green LED ON**, **Yellow LED OFF**  
    - Sends `Start Speech-to-Text` via WebSocket
  - **Hand Removed:**  
    - Turns **Green LED OFF**, **Yellow LED ON**  
    - Sends `Stop Speech-to-Text` via WebSocket

### 🖥️ Python Client (`mic_to_text.py`)
- Connects to ESP32 over WebSocket (`ws://<ESP32_IP>:81`)
- Listens for messages:
  - `Start Speech-to-Text` → Triggers `Win + H` to start Windows STT
  - `Stop Speech-to-Text` → Waits briefly then presses `Enter`

---

## 🛠 Hardware Setup

| Component     | GPIO Pin |
|--------------|---------|
| IR Sensor    | 23      |
| Yellow LED   | 2       |
| Green LED    | 15      |

---

## 📋 Software Requirements

### Arduino (ESP32)
- **Libraries Needed:**
  - `WiFi.h`
  - `WebSocketsServer.h`
- Configure `ssid` and `password` in `stt_esp32.ino`
- Upload to ESP32 using Arduino IDE / PlatformIO

### Python
Install dependencies:
```bash
pip install websockets pyautogui
````

---

## ⚙️ Setup Instructions

### 1️⃣ Flash ESP32

* Open `esp32/stt_esp32.ino`
* Update:

```cpp
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";
```

* Upload code to ESP32.
* Check Serial Monitor → Note the **ESP32 IP Address**.

### 2️⃣ Run Python Script

* Open `python/mic_to_text.py`
* Update:

```python
uri = "ws://<ESP32_IP>:81"
```

* Run:

```bash
python mic_to_text.py
```

### 3️⃣ Test

* Place your hand near the IR sensor → Windows Speech-to-Text should open.
* Remove your hand → STT stops and presses Enter.

---

## 📸 Example Output

ESP32 Serial:

```
Connecting to WiFi...
Connected to WiFi!
Start Speech-to-Text
Stop Speech-to-Text
```

Python Terminal:

```
Starting speech-to-text
Stopping speech-to-text and hitting Enter
```

---

## 🛠 Troubleshooting

* **No connection:** Ensure PC & ESP32 are on the same Wi-Fi.
* **Speech-to-Text not opening:** Manually press `Win + H` to confirm it works.
* **Unstable IR readings:** Add debounce or small delay in code.

---

## 📜 License

This module is part of [ESP32-AI-Assistant](../README.md) and is licensed under the MIT License.

```

---
