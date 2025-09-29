const int relay1Pin = 2;
const int relay2Pin = 3;

void setup() {
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');  // e.g. "true,false"

    data.trim(); // Remove spaces or \r

    int commaIndex = data.indexOf(',');
    if (commaIndex > 0) {
      String r1 = data.substring(0, commaIndex);        // before comma
      String r2 = data.substring(commaIndex + 1);       // after comma

      bool relay1State = (r1 == "true");
      bool relay2State = (r2 == "true");

      digitalWrite(relay1Pin, relay1State);
      digitalWrite(relay2Pin, relay2State);
    }
  }
}
