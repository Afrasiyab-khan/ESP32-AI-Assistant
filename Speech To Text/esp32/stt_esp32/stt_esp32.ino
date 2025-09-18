#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "afrasiyab";  // Replace with your Wi-Fi SSID
const char* password = "afra";  // Replace with your Wi-Fi password

WebSocketsServer webSocket = WebSocketsServer(81);  // WebSocket server on port 81

int irSensorPin = 23;
int yellowLED = 2;
int greenLED = 15;
bool isHandDetected = false;

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  Serial.begin(115200);
  
  // Initialize Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  // Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, LOW);
}

void loop() {
  int sensorState = digitalRead(irSensorPin);
  webSocket.loop();  // Check for WebSocket events

  if (sensorState == LOW && !isHandDetected) {
    // Hand detected, start speech-to-text
    Serial.println("Start Speech-to-Text");
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    
    webSocket.broadcastTXT("Start Speech-to-Text");
    isHandDetected = true;
    delay(100);
  } else if (sensorState == HIGH && isHandDetected) {
    // Hand no longer detected, stop speech-to-text
    Serial.println("Stop Speech-to-Text");
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    
    webSocket.broadcastTXT("Stop Speech-to-Text");
    isHandDetected = false;
    delay(100);
  }
}

// WebSocket event handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  // Handle WebSocket events (optional)
}

