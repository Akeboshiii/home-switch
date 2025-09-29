#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h> 

const char* ssid = "YOUR_WIFI_SSID"; 
const char* password = "YOUR_WIFI_PASSWORD"; 
const char* apiUrl = "https://home-web-switch.vercel.app/data"; 

unsigned long lastRequest = 0;
const unsigned long interval = 10000;

void setup() {
  Serial.begin(9600);
  Serial.println("Init...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void loop() {
  if (millis() - lastRequest >= interval) {
    lastRequest = millis();

    if (WiFi.status() == WL_CONNECTED) {
      BearSSL::WiFiClientSecure client;
      client.setInsecure();   
      
      HTTPClient http;
      http.begin(client, apiUrl);
      int httpCode = http.GET();

      if (httpCode == 200) {
        String payload = http.getString();

        bool relay1 = payload.indexOf("\"relay1\":true") > 0;
        bool relay2 = payload.indexOf("\"relay2\":true") > 0;

        Serial.print(relay1 ? "true" : "false");
        Serial.print(",");
        Serial.println(relay2 ? "true" : "false");
      }

      http.end();
    }
  }
}
