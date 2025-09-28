#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "YOUR_WIFI_SSID"; //name ng wifi
const char* password = "YOUR_WIFI_PASSWORD"; //pass niya
const char* apiUrl = "https://home-web-switch.vercel.app/data";  // {"relay1":true,"relay2":false}

unsigned long lastRequest = 0;
const unsigned long interval = 5000;

void setup() {
  Serial.begin(9600); // Esp TX to Arduino RX
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void loop() {
  if (millis() - lastRequest >= interval) {
    lastRequest = millis();

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(apiUrl);
      int httpCode = http.GET();

      if (httpCode == 200) {
        String payload = http.getString();
        payload.replace("'", "\""); // para sa double quote
        Serial.println(payload);
      }

      http.end();
    }
  }
}
