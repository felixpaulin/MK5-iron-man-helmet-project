#include <ESP32Servo.h>
#include <Arduino.h>

const int buttonPin = 12;
const int rightCheekPin = 18;
const int leftCheekPin = 19;
const int middleTopPin = 23;
const int bottomServoPin = 26;
const int leftTopPin = 17;
const int rightTopPin = 25;

Servo rightCheek;
Servo leftCheek;
Servo middleTop;
Servo bottomServo;
Servo leftTop;
Servo rightTop;

bool servoAt50 = false;
bool lastButtonState = HIGH;

const int smoothTurnMs = 6;
const int middleTopDelayMs = 300;
const int bottomDelayMs = 300;
const int topDelayMs = 300;

// Raw per-servo values so you can manually control each side.
const int rightCheekClosed = 117;
const int rightCheekOpen = 50;
const int leftCheekClosed = 50;
const int leftCheekOpen = 117;
const int middleTopClosed = 150;
const int middleTopOpen = 30;
const int bottomServoClosed = 38;
const int bottomServoOpen = 130;
const int leftTopClosed = 20;
const int leftTopOpen = 180;
const int rightTopClosed = 20;
const int rightTopOpen = 180;

int leftTopAngle = leftTopClosed;
int rightTopAngle = rightTopClosed;

void moveBothServosTo(int rightAngle, int leftAngle) {
  rightCheek.attach(rightCheekPin);
  leftCheek.attach(leftCheekPin);

  while (rightCheek.read() != rightAngle || leftCheek.read() != leftAngle) {
    int currentRight = rightCheek.read();
    int currentLeft = leftCheek.read();

    if (currentRight < rightAngle) {
      currentRight++;
    } else if (currentRight > rightAngle) {
      currentRight--;
    }

    if (currentLeft < leftAngle) {
      currentLeft++;
    } else if (currentLeft > leftAngle) {
      currentLeft--;
    }

    rightCheek.write(currentRight);
    leftCheek.write(currentLeft);
    delay(smoothTurnMs);
  }

  rightCheek.detach();
  leftCheek.detach();
}

void moveTopServosTo(int rightAngle, int leftAngle) {
  rightTop.attach(rightTopPin);
  leftTop.attach(leftTopPin);

  while (rightTopAngle != rightAngle || leftTopAngle != leftAngle) {
    if (rightTopAngle < rightAngle) {
      rightTopAngle++;
    } else if (rightTopAngle > rightAngle) {
      rightTopAngle--;
    }

    if (leftTopAngle < leftAngle) {
      leftTopAngle++;
    } else if (leftTopAngle > leftAngle) {
      leftTopAngle--;
    }

    rightTop.write(rightTopAngle);
    leftTop.write(leftTopAngle);
    delay(smoothTurnMs);
  }

  delay(250);
  rightTop.detach();
  leftTop.detach();
}

void moveMiddleTopTo(int angle) {
  middleTop.attach(middleTopPin);
  middleTop.write(angle);
  delay(250);
  middleTop.detach();
}

void moveBottomServoTo(int angle) {
  bottomServo.attach(bottomServoPin);
  bottomServo.write(angle);
  delay(250);
  bottomServo.detach();
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  // Start by moving once to the closed positions, then detach
  moveBothServosTo(rightCheekClosed, leftCheekClosed);
  moveMiddleTopTo(middleTopClosed);
  moveBottomServoTo(bottomServoClosed);
  moveTopServosTo(rightTopClosed, leftTopClosed);
  delay(500);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(20);
    if (digitalRead(buttonPin) == LOW) {
      servoAt50 = !servoAt50;
if (servoAt50) {
    moveBothServosTo(rightCheekOpen, leftCheekOpen);
    delay(middleTopDelayMs);
    moveMiddleTopTo(middleTopOpen);
    delay(bottomDelayMs);
    moveBottomServoTo(bottomServoOpen);
    delay(topDelayMs);
    moveTopServosTo(rightTopOpen, leftTopOpen);
  } else {
    moveTopServosTo(rightTopClosed, leftTopClosed);
    delay(topDelayMs);
    moveBottomServoTo(bottomServoClosed);
    delay(bottomDelayMs);
    moveMiddleTopTo(middleTopClosed);
    delay(middleTopDelayMs);
    moveBothServosTo(rightCheekClosed, leftCheekClosed);
  }
    }
  }

  lastButtonState = buttonState;
}
