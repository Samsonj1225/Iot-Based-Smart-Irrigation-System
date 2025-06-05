#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>

// Blynk credentials
char auth[] = "**********************"; // Your Blynk Auth Token
char ssid[] = "*********";             // Your WiFi SSID
char pass[] = "*********";             // Your WiFi Password

// IFTTT settings
const char* host = "maker.ifttt.com";
String IFTTT_KEY = "your_ifttt_key";     // <-- Replace with your actual IFTTT key
String eventName = "plant_alert";        // This should match your IFTTT event name
bool smsSent = false;                    // To prevent repeated alerts

BlynkTimer timer;
bool Relay = 0;

// Define component pins
#define sensor A0
#define waterPump D3

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH); // Pump OFF initially

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Call the function every 100 ms
  timer.setInterval(100L, soilMoistureSensor);
}

// Get the button value from Blynk (V1)
BLYNK_WRITE(V1) {
  Relay = param.asInt();
  if (Relay == 1) {
    digitalWrite(waterPump, LOW);  // Turn ON pump
  } else {
    digitalWrite(waterPump, HIGH); // Turn OFF pump
  }
}

// Soil moisture sensor logic
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1; // Convert to percentage (0 = dry, 100 = wet)

  Blynk.virtualWrite(V0, value); // Send to Blynk

  // If moisture is low and SMS hasn't been sent yet
  if (value < 30 && !smsSent) {
    sendIFTTTAlert();
    smsSent = true;
  }

  // Reset flag when soil moisture becomes normal
  if (value >= 30) {
    smsSent = false;
  }
}

// Trigger IFTTT Webhook
void sendIFTTTAlert() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://" + String(host) + "/trigger/" + eventName + "/with/key/" + IFTTT_KEY;
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("IFTTT Triggered Successfully");
    } else {
      Serial.println("Error Triggering IFTTT");
    }

    http.end();
  }
}

void loop() {
  Blynk.run();  // Run Blynk
  timer.run();  // Run Timer
}
