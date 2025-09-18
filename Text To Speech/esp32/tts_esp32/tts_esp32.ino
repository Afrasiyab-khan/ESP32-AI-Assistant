#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "SPIFFS.h"
#include "Audio.h"

const char* ssid = "It'sKhan";  // Replace with your SSID
const char* password = "itskhan321";  // Replace with your WiFi password
const char* elevenlabs_api_key = "sk_edb70ddeaab54b87a1e61f7df651a79d62d8060bd249f392";  // Your ElevenLabs API key
const char* voice_id = "pNInz6obpgDQGcFmaJgB";  // Replace with a valid voice_id from ElevenLabs

#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRC 26

Audio audio;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  SPIFFS.begin(true);  // Initialize SPIFFS

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println(" connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
}

void loop() {
  Serial.print("Ask your Question: ");
  
  String Question = "";
  while (!Serial.available()) {
    audio.loop();
  }

  while (Serial.available()) {
    char add = Serial.read();
    Question = Question + add;
    delay(1);
  }
  
  int len = Question.length();
  if (len > 0) {
    Question = Question.substring(0, len - 1);  // Remove the last character (newline)
  }

  // Append "Tell me the answer in 10 words only" to the question
  Question += "your overall response must be in 20 words(Strictly Follow).";
  
  String responseText = getChatGPTResponse(Question);
  if (responseText != "") {
    Serial.print("Answer: ");
    Serial.println(responseText);
    
    if (!convertTextToSpeech(responseText)) {
      Serial.println("Error converting text to speech");
    }
  } else {
    Serial.println("Error fetching ChatGPT response");
  }
}

// Function to get response from ChatGPT (Groq)
String getChatGPTResponse(String question) {
  HTTPClient https;

  if (https.begin("https://api.groq.com/openai/v1/chat/completions")) {  // HTTPS
    https.addHeader("Content-Type", "application/json");
    String token_key = String("Bearer ") + "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";
    https.addHeader("Authorization", token_key);

    String payload = "{\"messages\": [{\"role\": \"user\", \"content\": \"" + question + "\"}], \"model\": \"mixtral-8x7b-32768\"}";

    int httpCode = https.POST(payload);
    
    if (httpCode == HTTP_CODE_OK) {
      String response = https.getString();
      DynamicJsonDocument doc(2048);

      DeserializationError error = deserializeJson(doc, response);
      if (!error) {
        String content = doc["choices"][0]["message"]["content"].as<String>();
        return content;
      } else {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
      }
    } else {
      Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.println("[HTTPS] Unable to connect");
  }
  return "";
}

// Function to convert text to speech using ElevenLabs
bool convertTextToSpeech(String text) {
  HTTPClient http;
  
  String url = "https://api.elevenlabs.io/v1/text-to-speech/" + String(voice_id) + "/stream";

  if (http.begin(url)) {  // ElevenLabs API endpoint for TTS
    http.addHeader("Content-Type", "application/json");
    http.addHeader("xi-api-key", elevenlabs_api_key);

    // Create JSON payload
    String payload = "{\"text\": \"" + text + "\", \"model_id\": \"eleven_multilingual_v2\", \"voice_settings\": {\"stability\": 0.5, \"similarity_boost\": 0.8, \"style\": 0.0, \"use_speaker_boost\": true}}";

    Serial.println("Sending payload: " + payload);  // Debug: print the payload being sent

    // Send POST request
    int httpCode = http.POST(payload);

    // Check if the request was successful
    if (httpCode == HTTP_CODE_OK) {
      File audioFile = SPIFFS.open("/speech.mp3", FILE_WRITE);
      if (!audioFile) {
        Serial.println("Failed to open file for writing");
        http.end();
        return false;
      }

      // Write the audio stream to the file
      http.writeToStream(&audioFile);
      audioFile.close();

      // Play the audio file
      playAudio("/speech.mp3");
      http.end();
      return true;
    } else {
      Serial.printf("Error in POST: %s\n", http.errorToString(httpCode).c_str());
      String response = http.getString();
      Serial.println("Server response: " + response);
    }

    http.end();
  } else {
    Serial.println("Unable to connect to ElevenLabs API");
  }

  return false;
}

// Function to play audio file
void playAudio(const char* filePath) {
  audio.connecttoFS(SPIFFS, filePath);
}

void audio_info(const char* info) {
  Serial.print("audio_info: ");
  Serial.println(info);
}
