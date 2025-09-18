# 🎤 Speech-to-Text (STT) Module

This module uses **ESP32 + IR Sensor + WebSocket + Python** to control **Windows Speech-to-Text (STT)** automatically.

📌 **Workflow:**
When a hand is detected by the IR sensor, the ESP32 sends a WebSocket message to the Python client, which triggers the Windows Speech-to-Text tool (`Win + H`).
When the hand is removed, it stops listening and automatically presses **Enter** to finalize transcription.

---

## 📂 Folder Structure

```bash
speech-to-text/
├── esp32/
│   └── stt_esp32.ino       # ESP32 firmware (hand detection + WebSocket server)
├── python/
│   └── mic_to_text.py      # Python script to trigger Windows STT
└── README.md               # This documentation file
```

---

## 🧩 How It Works

### 🔧 ESP32 Firmware (`stt_esp32.ino`)

* Connects to Wi-Fi with your SSID & Password.
* Starts a **WebSocket server** on port `81`.
* Monitors IR sensor on **GPIO 23**:

| Event             | LED Behavior                  | Action                                      |
| ----------------- | ----------------------------- | ------------------------------------------- |
| **Hand Detected** | ✅ Green ON <br> ⚠️ Yellow OFF | Sends `Start Speech-to-Text` over WebSocket |
| **Hand Removed**  | ❌ Green OFF <br> ⚠️ Yellow ON | Sends `Stop Speech-to-Text` over WebSocket  |

---

### 🖥️ Python Client (`mic_to_text.py`)

* Connects to `ws://<ESP32_IP>:81`
* Listens for messages:

  * **`Start Speech-to-Text`** → Triggers `Win + H` (opens Windows STT)
  * **`Stop Speech-to-Text`** → Waits briefly, then presses `Enter`

---

## 🛠 Hardware Setup

| Component  | GPIO Pin |
| ---------- | -------- |
| IR Sensor  | 23       |
| Yellow LED | 2        |
| Green LED  | 15       |

---

## 📋 Software Requirements

### 🖥 Arduino (ESP32)

**Required Libraries:**

* `WiFi.h`
* `WebSocketsServer.h`

**Steps:**

1. Open `esp32/stt_esp32.ino`
2. Configure your Wi-Fi:

   ```cpp
   const char* ssid = "YourWiFiName";
   const char* password = "YourWiFiPassword";
   ```
3. Upload to ESP32 using **Arduino IDE** or **PlatformIO**
4. Open Serial Monitor → Note the **ESP32 IP Address**

---

### 🐍 Python

Install dependencies:

```bash
pip install websockets pyautogui
```

---

## ⚙️ Setup Instructions

1️⃣ **Flash ESP32**

* Upload code from `esp32/stt_esp32.ino`
* Confirm ESP32 is connected to Wi-Fi (Serial Monitor output)

2️⃣ **Run Python Script**

* Open `python/mic_to_text.py`
* Update the URI:

  ```python
  uri = "ws://<ESP32_IP>:81"
  ```
* Run:

  ```bash
  python mic_to_text.py
  ```

3️⃣ **Test**

* Place your hand near the IR sensor → STT should activate
* Remove your hand → STT stops + presses Enter automatically

---

## 📸 Example Output

**ESP32 Serial Monitor:**

```
Connecting to WiFi...
Connected to WiFi!
Start Speech-to-Text
Stop Speech-to-Text
```

**Python Terminal:**

```
Starting speech-to-text
Stopping speech-to-text and hitting Enter
```
---

## 🛠 Troubleshooting

| Issue                 | Possible Fix                                           |
| --------------------- | ------------------------------------------------------ |
| ❌ No connection       | Ensure PC & ESP32 are on the **same Wi-Fi network**    |
| 🎙 STT not opening    | Manually press `Win + H` to confirm Windows STT works  |
| 🔄 IR sensor flickers | Add a **debounce delay** in code to stabilize readings |

---

## 📜 License

This module is part of **ESP32-AI-Assistant** and is licensed under the **MIT License**.
