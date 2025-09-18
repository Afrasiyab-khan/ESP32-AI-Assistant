````markdown
# 🤖 ESP32 AI Assistant  

A **cost-effective, dual-ESP32 voice assistant** that combines:
- 🗣 **Speech-to-Text (STT):** Hand-detection triggered transcription using ESP32 + Python.
- 🔊 **Text-to-Speech (TTS):** AI-powered response generation using Groq API + natural voice synthesis with ElevenLabs API.

This project demonstrates how to build a modular, offline/online hybrid AI assistant that uses affordable hardware and free APIs (where possible).

---

## 🖼️ System Architecture

```mermaid
flowchart LR
    IR[IR Sensor + ESP32] -->|WebSocket| PYTHON[Python STT Client]
    PYTHON -->|Windows STT| TEXT[Recognized Text]
    TEXT -->|User Types Question| ESP_TTS[ESP32 + Groq API]
    ESP_TTS -->|AI Response| ELEVEN[ElevenLabs TTS]
    ELEVEN -->|MP3 Output| SPEAKER[(Speaker)]
````

---

## 📂 Project Structure

```
ESP32-AI-Assistant/
├── Speech To Text/            # Module 1: Hand-detection + Speech-to-Text
│   ├── esp32/                 # ESP32 firmware for hand detection + WebSocket
│   ├── python/                # Python script to trigger Windows STT
│   └── README.md              # Detailed setup guide for STT module
│
└── Text To Speech/            # Module 2: AI Chat + Text-to-Speech
    ├── esp32/                 # ESP32 firmware for Groq + ElevenLabs TTS
    └── README.md              # Detailed setup guide for TTS module
```

Each module contains its own `README.md` with **pin diagrams, setup steps, and dependencies**.

---

## ✨ Features

✅ **Modular Design:** Two ESP32 boards (STT & TTS) working independently.
✅ **Hands-Free Input:** IR sensor automatically triggers speech-to-text mode.
✅ **AI-Generated Response:** Uses Groq API (fast & free tier available).
✅ **Natural-Sounding Voice:** ElevenLabs API for realistic speech synthesis.
✅ **Plug-and-Play Setup:** Minimal wiring, works with MAX98357A I2S audio module.
✅ **Open-Source & Extensible:** Easy to add new features or swap APIs.

---

## 🛠 Hardware Requirements

| Component              | Quantity | Notes                            |
| ---------------------- | -------- | -------------------------------- |
| ESP32 Dev Board        | 2        | One for STT, one for TTS         |
| IR Sensor Module       | 1        | For hand detection (STT trigger) |
| I2S DAC Module         | 1        | MAX98357A recommended            |
| Speaker (4Ω or 8Ω)     | 1        | Connect to I2S output            |
| Computer with Python 3 | 1        | For running STT script           |

---

## 📦 Software Requirements

* **Arduino IDE** with ESP32 board package
* **Python 3.x** with dependencies:

  ```bash
  pip install websockets pyautogui
  ```
* **API Keys:**

  * Groq API Key ([Get Here](https://console.groq.com))
  * ElevenLabs API Key ([Get Here](https://elevenlabs.io))

---

## 🚀 Setup & Usage

### 1️⃣ Speech-to-Text Module

1. Flash ESP32 with code in `Speech To Text/esp32/stt_esp32`
2. Run Python script in `Speech To Text/python/mic_to_text.py`
3. Wave your hand near the IR sensor → Windows Speech-to-Text will start recording.

Detailed guide → [Speech-to-Text README](./Speech%20To%20Text/README.md)

---

### 2️⃣ Text-to-Speech Module

1. Flash ESP32 with code in `Text To Speech/esp32/tts_esp32`
2. Open Serial Monitor → Type a question → ESP32 fetches AI reply.
3. Response is converted to audio and played on the speaker.

Detailed guide → [Text-to-Speech README](./Text%20To%20Speech/README.md)

---

## 🖼️ Example Demo

```
> Hand Detected → STT Activated
> User Speaks: "What is AI?"
> AI Responds: "AI is machine intelligence that mimics human learning and reasoning."
> Speaker Plays Natural Voice 🎙️
```

---

## 🏗 Roadmap

* [ ] GUI for starting/stopping STT without Python terminal
* [ ] Offline Speech-to-Text using Vosk
* [ ] Offline TTS using EdgeTTS or Coqui TTS
* [ ] Add wake-word detection (e.g., "Hey AI!")

---

## 🤝 Contributing

Pull requests are welcome!
If you have suggestions, open an issue or submit a PR to improve this project.

---

## 📜 License

This project is licensed under the **MIT License** – free to use, modify, and distribute.

---

## 🌟 Acknowledgments

* **Groq API** for blazing-fast LLM inference
* **ElevenLabs** for high-quality TTS voices
* Open-source Arduino libraries & Python tools

```

---

## 🔑 Why This is Professional:
✅ **Mermaid diagram** → instantly explains architecture visually  
✅ **Project structure** → shows folder layout clearly  
✅ **Links to sub-readmes** → professional repo navigation  
✅ **Features + Hardware + Software sections** → like a real open-source project  
✅ **Roadmap + License + Acknowledgments** → makes repo look active & polished  

