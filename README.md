# 🤖 ESP32 AI Assistant

A **cost-effective, dual-ESP32 voice assistant** designed to deliver a smooth **hands-free AI experience** using **affordable hardware** and **free APIs (where possible)**.

---

## 🏗️ Overview

This project demonstrates how to build a **modular, offline/online hybrid AI assistant** that can:

* 🗣 **Convert speech to text** (STT) triggered by hand detection
* 🔊 **Generate AI responses** using Groq API
* 🗨 **Speak answers naturally** with ElevenLabs TTS

📌 **Goal:** Make voice assistants more **affordable, extensible, and DIY-friendly** for makers & researchers.

---

## 🖼️ System Architecture

```mermaid
flowchart LR
    IR[IR Sensor + ESP32] -->|WebSocket| PYTHON[Python STT Client]
    PYTHON -->|Windows STT| TEXT[Recognized Text]
    TEXT -->|User Types Question| ESP_TTS[ESP32 + Groq API]
    ESP_TTS -->|AI Response| ELEVEN[ElevenLabs TTS]
    ELEVEN -->|MP3 Output| SPEAKER[(Speaker)]
```

📌 **Architecture Image:**

<img width="629" height="332" alt="image" src="https://github.com/user-attachments/assets/9c206732-01b8-404d-abdd-24748f6bda10" />
---

## 📂 Project Structure

```
ESP32-AI-Assistant/
├── Speech To Text/            
│   ├── esp32/                 # ESP32 firmware for hand detection + WebSocket
│   ├── python/                # Python script to trigger Windows STT
│   └── README.md              # Setup guide for STT module
│
└── Text To Speech/            
    ├── esp32/                 # ESP32 firmware for Groq + ElevenLabs TTS
    └── README.md              # Setup guide for TTS module
```

Each module contains **pin diagrams, setup steps, and dependencies** for quick onboarding.

---

## ✨ Features

| Feature                     | Description                                        |
| --------------------------- | -------------------------------------------------- |
| ✅ **Modular Design**        | Two ESP32 boards (STT & TTS) working independently |
| 🖐 **Hands-Free Input**     | IR sensor automatically triggers STT               |
| ⚡ **Fast AI Responses**     | Powered by **Groq API** (free tier available)      |
| 🎙 **Natural Voice Output** | ElevenLabs API provides realistic speech synthesis |
| 🔌 **Plug-and-Play Setup**  | Works with MAX98357A I2S module                    |
| 🛠 **Extensible**           | Swap APIs, add wake-word, or build offline mode    |

---

## 🛠 Hardware Requirements

| Component              | Qty | Notes                            |
| ---------------------- | --- | -------------------------------- |
| ESP32 Dev Board        | 2   | One for STT, one for TTS         |
| IR Sensor Module       | 1   | For hand detection (STT trigger) |
| I2S DAC Module         | 1   | MAX98357A recommended            |
| Speaker (4Ω or 8Ω)     | 1   | Connect to I2S output            |
| Computer with Python 3 | 1   | For running STT script           |

📌 **Wiring Diagram:**

<img width="602" height="341" alt="image" src="https://github.com/user-attachments/assets/9cc5c4cd-59d7-40b4-b735-a46684cff31c" />

---

## 📦 Software Requirements

* **Arduino IDE** with ESP32 board package
* **Python 3.x** with dependencies:

```bash
pip install websockets pyautogui
```

* **API Keys Needed:**

  * [Groq API Key](https://console.groq.com)
  * [ElevenLabs API Key](https://elevenlabs.io)

---

## 🚀 Setup & Usage

### 1️⃣ Speech-to-Text (STT)

1. Flash ESP32 with `Speech To Text/esp32/stt_esp32`
2. Run Python script `Speech To Text/python/mic_to_text.py`
3. Wave hand near IR sensor → Windows STT records speech

📖 Detailed Guide → [STT README](./Speech%20To%20Text/README.md)

---

### 2️⃣ Text-to-Speech (TTS)

1. Flash ESP32 with `Text To Speech/esp32/tts_esp32`
2. Open Serial Monitor → Type a question
3. ESP32 fetches AI reply → ElevenLabs converts to speech → Speaker plays output

📖 Detailed Guide → [TTS README](./Text%20To%20Speech/README.md)

---

## 🎥 Example Demo

```
> Hand Detected → STT Activated
> User Speaks: "What is AI?"
> AI Responds: "AI is machine intelligence that mimics human learning and reasoning."
> Speaker Plays Natural Voice 🎙️
```

📌 **Video:**

https://github.com/user-attachments/assets/5a6685ba-b317-4cf6-ac32-0f73383c1348

---

## 🏗 Roadmap

* [ ] GUI for STT start/stop (no terminal needed)
* [ ] Offline STT using **Vosk**
* [ ] Offline TTS using **EdgeTTS** or **Coqui TTS**
* [ ] Add **wake-word detection** (e.g., “Hey AI!”)

---

## 🤝 Contributing

Pull requests are welcome!
If you have suggestions, open an **issue** or submit a **PR** to improve this project.

---

## 📜 License

Licensed under **MIT License** – free to use, modify, and distribute.

---

## 🌟 Acknowledgments

* **Groq API** → Fast LLM inference
* **ElevenLabs** → High-quality TTS
* **Arduino & Python Community** → Open-source tools and libraries

**© By - Afrasiyab Khan (Software Engineer)**


