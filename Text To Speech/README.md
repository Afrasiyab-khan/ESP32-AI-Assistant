# 🗣️ Text-to-Speech (TTS) + AI Chat Module

This module transforms your ESP32 into a **mini AI voice assistant** that:

1️⃣ Reads user input from the Serial Monitor
2️⃣ Sends it to **Groq’s API** for an AI-generated response
3️⃣ Converts the response into **natural-sounding speech** using **ElevenLabs API**
4️⃣ Plays the generated audio through an I2S speaker

---

## 📂 Folder Structure

```bash
text-to-speech/
├── esp32/
│   └── tts_esp32.ino       # ESP32 firmware (Groq + ElevenLabs integration)
└── README.md               # This documentation file
```

---

## 🧩 How It Works

### 🔧 ESP32 Firmware (`tts_esp32.ino`)

* Connects to Wi-Fi with your SSID & Password
* Waits for user input from Serial Monitor
* Sends input text to **Groq API** (model: `mixtral-8x7b-32768`)
* Receives AI-generated response (limited to \~20 words)
* Sends response to **ElevenLabs API** for TTS conversion
* Stores returned MP3 file in **SPIFFS**
* Plays audio using I2S DAC (works with MAX98357A or any I2S amplifier)

---

## 🛠 Hardware Setup

| Signal               | GPIO Pin |
| -------------------- | -------- |
| I2S Data (DIN)       | 25       |
| I2S Bit Clock (BCLK) | 27       |
| I2S LR Clock (LRC)   | 26       |

**Required Components:**

* ESP32 Dev Board
* I2S DAC module (e.g., MAX98357A)
* 4Ω or 8Ω speaker

---

## 📋 Software Requirements

### Arduino (ESP32)

**Required Libraries:**

* `WiFi.h`
* `HTTPClient.h`
* `ArduinoJson.h`
* `SPIFFS.h`
* `Audio.h`

**Configuration:**
Inside `tts_esp32.ino`, update:

```cpp
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";
const char* elevenlabs_api_key = "Your_ElevenLabs_API_Key";
const char* voice_id = "Your_Chosen_Voice_ID";
```

Inside `getChatGPTResponse()`, set your Groq API key:

```cpp
String token_key = String("Bearer ") + "your_groq_api_key";
```

---

## ⚙️ Setup Instructions

### 1️⃣ Flash ESP32

* Open `tts_esp32.ino`
* Update Wi-Fi credentials, API keys, and voice ID
* Select your ESP32 board in Arduino IDE
* Upload code and open Serial Monitor at **115200 baud**

---

### 2️⃣ Ask a Question

When prompted in Serial Monitor:

```
Ask your Question:
```

Type your question (e.g., `What is AI?`) and press Enter.

**ESP32 Workflow:**

1. Sends your question to **Groq API**
2. Receives AI response (short answer)
3. Converts response to speech via ElevenLabs
4. Plays audio through I2S speaker

---

## 🖥️ Example Serial Output

```
Connecting to WiFi...
...... connected
IP address: 192.168.0.101
Ask your Question: 
Sending payload: {...}
Answer: AI is intelligence by machines to mimic human learning and reasoning.
Playing audio...
```

---

## 🛠 Troubleshooting

| Issue               | Solution                                         |
| ------------------- | ------------------------------------------------ |
| 🔇 No Sound         | Verify I2S wiring & speaker polarity             |
| 🌐 API Error        | Ensure Groq & ElevenLabs API keys are valid      |
| ✂️ Response Cut Off | Increase SPIFFS size or limit AI response length |

---

## 💡 Customization

* **Change Voice:** Replace `voice_id` with any ElevenLabs-supported voice
* **Switch AI Model:** Use other Groq models (`gemma-7b-it`, `llama3-70b-8192`, etc.)
* **Control Response Size:** Adjust instruction in `loop()` to modify output length

```cpp
Question += "your overall response must be in 20 words (Strictly Follow).";
```

---

## 📜 License

This module is part of **[ESP32-AI-Assistant](../README.md)** and is licensed under the **MIT License**.


