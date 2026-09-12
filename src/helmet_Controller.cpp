#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("S3 BOOTED!");
}

void loop() {
  Serial.println("RUNNING");
  delay(1000);
}