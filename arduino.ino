#include <ArduinoJson.h>

const int relay1Pin = 2;
const int relay2Pin = 3;

void setup() {
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String json = Serial.readStringUntil('\n');

    StaticJsonDocument<128> doc;
    if (deserializeJson(doc, json) == DeserializationError::Ok) {
      bool relay1State = doc["relay1"];
      bool relay2State = doc["relay2"];

      digitalWrite(relay1Pin, relay1State);
      digitalWrite(relay2Pin, relay2State);
    }
  }
}
