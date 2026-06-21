#include <ESP32Servo.h>

const int BUTTON_PIN = 12;
const int SERVO_PIN = 18;

Servo myServo;

bool servoAt90 = false;
bool lastButtonState = HIGH;
int currentAngle = 0;

// Smaller delay = faster movement
const int STEP_DELAY_MS = 2;
const int STEP_SIZE = 1;

void smoothMove(int targetAngle) {
  if (targetAngle > currentAngle) {
    for (int angle = currentAngle; angle <= targetAngle; angle += STEP_SIZE) {
      myServo.write(angle);
      delay(STEP_DELAY_MS);
    }
  } else {
    for (int angle = currentAngle; angle >= targetAngle; angle -= STEP_SIZE) {
      myServo.write(angle);
      delay(STEP_DELAY_MS);
    }
  }

  currentAngle = targetAngle;
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  myServo.attach(SERVO_PIN);
  smoothMove(0);   // start at 0
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(20);
    if (digitalRead(BUTTON_PIN) == LOW) {
      servoAt90 = !servoAt90;
      if (servoAt90) {
        smoothMove(90);
      } else {
        smoothMove(0);
      }
    }
  }

  lastButtonState = buttonState;
}
