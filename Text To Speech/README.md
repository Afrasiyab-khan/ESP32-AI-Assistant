```markdown
# 🗣️ Text-to-Speech (TTS) + AI Chat Module  

This module turns ESP32 into a **mini AI assistant** that:
1. Reads your question from Serial input.
2. Sends it to **Groq’s ChatGPT API** for a short response.
3. Converts the answer to **natural-sounding speech** using **ElevenLabs API**.
4. Plays the audio back via I2S speakers.

---

## 📂 Folder Structure
```

text-to-speech/
├── esp32/
│   └── tts\_esp32.ino      # ESP32 firmware (Groq + ElevenLabs integration)
└── README.md              # This documentation file

````

---

## 🧩 How It Works

### 🔧 ESP32 Code (`tts_esp32.ino`)
- Connects to Wi-Fi.
- Waits for user input in Serial Monitor.
- Sends the text to Groq’s API (mixtral-8x7b-32768 model).
- Takes the AI response, sends it to ElevenLabs for TTS conversion.
- Saves the MP3 file to SPIFFS.
- Plays it through I2S DAC output (works with I2S speaker or MAX98357A module).

---

## 🛠 Hardware Setup

| Component       | GPIO Pin |
|----------------|---------|
| I2S Data (DIN) | 25      |
| I2S Bit Clock  | 27      |
| I2S LR Clock   | 26      |
| Speaker Module | Connect to I2S pins |

You will need:
- ESP32 Dev Board
- I2S-compatible amplifier (e.g., MAX98357A)
- Speaker (4Ω or 8Ω)

---

## 📋 Software Requirements

### Arduino (ESP32)
- **Libraries Needed:**
  - `WiFi.h`
  - `HTTPClient.h`
  - `ArduinoJson.h`
  - `SPIFFS.h`
  - `Audio.h`
- Configure `ssid`, `password`, `elevenlabs_api_key`, `voice_id`, and **Groq API key**.

---

## ⚙️ Setup Instructions

### 1️⃣ Flash ESP32
Open `tts_esp32.ino` and update:
```cpp
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";
const char* elevenlabs_api_key = "Your_ElevenLabs_API_Key";
const char* voice_id = "Your_Chosen_Voice_ID";
````

Update **Groq API key** inside `getChatGPTResponse()`:

```cpp
String token_key = String("Bearer ") + "your_groq_api_key";
```

Then:

* Select ESP32 board in Arduino IDE
* Upload code
* Open Serial Monitor at `115200 baud`

---

### 2️⃣ Ask a Question

In Serial Monitor:

```
Ask your Question: 
```

Type:

```
What is AI?
```

ESP32 will:

* Send request to Groq API
* Get short AI response
* Convert to audio via ElevenLabs
* Play it via speaker

---

## 🖼️ Example Serial Output

```
Connecting to It'sKhan
...... connected
IP address: 192.168.0.101
Ask your Question: 
Sending payload: {...}
Answer: AI is intelligence by machines to mimic human learning and reasoning.
Playing audio...
```

---

## 🛠 Troubleshooting

* **No sound:** Check I2S wiring & speaker connection.
* **Error connecting to API:** Ensure valid Groq & ElevenLabs API keys.
* **Large response cutoff:** You can increase SPIFFS size or limit response length (already set to \~20 words).

---

## 💡 Customization

* **Change Voice:** Replace `voice_id` with any ElevenLabs voice.
* **Change AI Model:** Use Groq-supported models (`gemma-7b-it`, `llama3-70b-8192`, etc.)
* **Control Response Size:** Modify this line in `loop()`:

```cpp
Question += "your overall response must be in 20 words(Strictly Follow).";
```

---

## 📜 License

This module is part of [ESP32-AI-Assistant](../README.md) and is licensed under the MIT License.

