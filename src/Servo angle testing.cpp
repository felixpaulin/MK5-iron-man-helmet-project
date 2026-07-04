#include <ESP32Servo.h>
#include <Arduino.h>

const int sectionalPin = 13;
const int integralPin = 16;
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

bool helmetOpen = false;
bool topOpen = false;
bool lastSectionalState = HIGH;
bool lastIntegralState = HIGH;

const int smoothTurnMs = 3;
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
const int bottomServoOpen = 128;
const int leftTopClosed = 20;
const int leftTopOpen = 180;
const int rightTopClosed = 20;
const int rightTopOpen = 180;

int leftTopAngle = leftTopClosed;
int rightTopAngle = rightTopClosed;
int leftCheekAngle = leftCheekClosed;
int rightCheekAngle = rightCheekClosed;
int bottomServoAngle = bottomServoClosed;
int middleTopAngle = middleTopClosed;

void moveCheekServosTo(int rightAngle, int leftAngle) {
  rightCheek.attach(rightCheekPin);
  leftCheek.attach(leftCheekPin);

  while (rightCheekAngle != rightAngle || leftCheekAngle != leftAngle) {
    if (rightCheekAngle < rightAngle) {
      rightCheekAngle++;
    } else if (rightCheekAngle > rightAngle) {
      rightCheekAngle--;
    }

    if (leftCheekAngle < leftAngle) {
      leftCheekAngle++;
    } else if (leftCheekAngle > leftAngle) {
      leftCheekAngle--;
    }

    rightCheek.write(rightCheekAngle);
    leftCheek.write(leftCheekAngle);
    delay(smoothTurnMs);
  }

  delay(250);
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
    delay(7);
  }

  delay(250);
  rightTop.detach();
  leftTop.detach();
}

void moveMiddleTopTo(int angle) {
  middleTop.attach(middleTopPin);

  middleTop.write(middleTopAngle);

  delay(100);

  while (middleTopAngle != angle) {
    if (middleTopAngle < angle) {
      middleTopAngle ++;
    } else if (middleTopAngle > angle) {
      middleTopAngle --;
    }


    middleTop.write(middleTopAngle);
    delay(smoothTurnMs);
  }
  delay(250);
  middleTop.detach();
}

void moveBottomServoTo(int angle) {
  bottomServo.attach(bottomServoPin);

  while (bottomServoAngle != angle) {
    if (bottomServoAngle < angle) {
      bottomServoAngle ++;
    } else if (bottomServoAngle > angle) {
      bottomServoAngle --;
    }


    bottomServo.write(bottomServoAngle);
    delay(smoothTurnMs);
  }
  delay(250);

  //bottomServo.detach();
}

void setup() {
  pinMode(sectionalPin, INPUT_PULLUP);
  pinMode(integralPin, INPUT_PULLUP);
}

void sectionalOpen() {
  if (helmetOpen) {
    moveCheekServosTo(rightCheekOpen, leftCheekOpen);
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
    bottomServo.detach();
    delay(bottomDelayMs);
    moveMiddleTopTo(middleTopClosed);
    delay(middleTopDelayMs);
    moveCheekServosTo(rightCheekClosed, leftCheekClosed);
  }
}

void integralOpen() {
  if (topOpen) {
    moveTopServosTo(rightTopClosed, leftTopClosed);
    topOpen = false;
  } else {
    moveTopServosTo(rightTopOpen, leftTopOpen);
    topOpen = true;
  }
}

void loop() {
  bool sectionalState = digitalRead(sectionalPin);
  bool integralState = digitalRead(integralPin);

  if (sectionalState == LOW && lastSectionalState == HIGH) {
    delay(20);
    if (digitalRead(sectionalPin) == LOW) {
      helmetOpen = !helmetOpen;
      sectionalOpen();
    }
  }

  if (integralState == LOW && lastIntegralState == HIGH) {
    delay(20);
    if (digitalRead(integralPin) == LOW) {
      integralOpen();
    }
  }

  lastSectionalState = sectionalState;
  lastIntegralState = integralState;
}