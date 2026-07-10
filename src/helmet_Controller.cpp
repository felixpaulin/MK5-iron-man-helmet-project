#include <ESP32Servo.h>
#include <Arduino.h>

// Note: you can also use INPUT_PULLUP buttons instead of capitive touch sensors, which is what I did for testing before switching to the helemts touch sensors.

const int sectionalPin = 13; // pin for secitonal opening touch pad
const int integralPin = 16; // pin for integral opening touch pad

// pins for all the servos. rightTop and leftTop are the two top piece servos
// bottomServo is the servo for the bottom part and same situation with middleTop and cheek servos
const int rightCheekPin = 18;
const int leftCheekPin = 19;
const int middleTopPin = 23;
const int bottomServoPin = 26;
const int leftTopPin = 17;
const int rightTopPin = 25;

// servo names
Servo rightCheek;
Servo leftCheek;
Servo middleTop;
Servo bottomServo;
Servo leftTop;
Servo rightTop;

// define states
bool helmetOpen = false;
bool topOpen = false;
bool lastSectionalState = HIGH;
bool lastIntegralState = HIGH;

// smooth turn for servo speed and delay for time inbtween different servos moving
const int smoothTurnMs = 2;
const int middleTopDelayMs = 100;
const int bottomDelayMs = 150;
const int topDelayMs = 150;

// Raw per-servo values so you can manually control each servo.
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

// define angle names for in code
int leftTopAngle = leftTopClosed;
int rightTopAngle = rightTopClosed;
int leftCheekAngle = leftCheekClosed;
int rightCheekAngle = rightCheekClosed;
int bottomServoAngle = bottomServoClosed;
int middleTopAngle = middleTopClosed;

// below are the functions for moving each servo/servo pair this one is for the cheek servos
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

  delay(150);
  rightCheek.detach();
  leftCheek.detach();
}

// this is for the two top assembly servos
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
    delay(6);
  }

  delay(150);
  rightTop.detach();
  leftTop.detach();
}

// this is for the middle top piece servo
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
  delay(150);
  middleTop.detach();
}

// move cheek servos and middle top in sync, while keeping separate control of middle top speed via a calculation based off how much it has to travel
void moveCheeksAndMiddleTopTo(int rightAngle, int leftAngle, int middleAngle) {
  rightCheek.attach(rightCheekPin);
  leftCheek.attach(leftCheekPin);
  middleTop.attach(middleTopPin);

  // calculate how many steps the cheeks need to move
  // abs() returns the positive distance regardless of direction
  int cheekSteps = max(abs(rightAngle - rightCheekAngle), abs(leftAngle - leftCheekAngle));
  // calculate how many steps the middle top needs to move
  int middleSteps = abs(middleAngle - middleTopAngle);

  // if the middle top has to travel farther, increase its per-loop step size
  // so it can finish around the same time as the cheeks
  int middleStep = 1;
  if (cheekSteps > 0) {
    middleStep = max(1, (middleSteps + cheekSteps - 1) / cheekSteps);
  }

  while (rightCheekAngle != rightAngle || leftCheekAngle != leftAngle || middleTopAngle != middleAngle) {
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

    if (middleTopAngle < middleAngle) {
      middleTopAngle = min(middleTopAngle + middleStep, middleAngle);
    } else if (middleTopAngle > middleAngle) {
      middleTopAngle = max(middleTopAngle - middleStep, middleAngle);
    }

    // write the updated angles to the servos and wait one loop interval
    rightCheek.write(rightCheekAngle);
    leftCheek.write(leftCheekAngle);
    middleTop.write(middleTopAngle);
    delay(4);
  }

  delay(150);
  rightCheek.detach();
  leftCheek.detach();
  middleTop.detach();
}

// this is for the bottom assembly servo
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
  delay(150);
}

// setup for the touch pads
void setup() {
  pinMode(sectionalPin, INPUT_PULLUP);
  pinMode(integralPin, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("MK5 Controller Ready!");
}

// function for opening the helmet in sections.
// It moves the cheek servos and the middle top servo in sync, while keeping those motions in separate helper functions.
void sectionalOpen() {
  if (helmetOpen) {
    moveCheekServosTo(rightCheekOpen, leftCheekOpen);
    delay(middleTopDelayMs);
    moveMiddleTopTo(middleTopOpen);    delay(bottomDelayMs);
    moveBottomServoTo(bottomServoOpen);
    delay(topDelayMs);
    moveTopServosTo(rightTopOpen, leftTopOpen);
  } else {
    moveTopServosTo(rightTopClosed, leftTopClosed);
    delay(topDelayMs);
    moveBottomServoTo(bottomServoClosed);
    bottomServo.detach();
    delay(bottomDelayMs);
    moveCheeksAndMiddleTopTo(rightCheekClosed, leftCheekClosed, middleTopClosed);
  }
}

// function for opening the helemt integrally, so as one piece
void integralOpen() {
  if (topOpen) {
    moveTopServosTo(rightTopClosed, leftTopClosed);
    topOpen = false;
  } else {
    moveTopServosTo(rightTopOpen, leftTopOpen);
    topOpen = true;
  }
}

// the loop that actually calls the functions if a touch pad is touched in order to open or close the helemt in the two different ways.
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

if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    Serial.print("Received: ");
    Serial.println(cmd);
}

  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "SECTION_HELMET") {
        if (!helmetOpen) {
            helmetOpen = true;
            sectionalOpen();
        }
    }

    else if (command == "LOCK_HELMET") {
        if (helmetOpen) {
            helmetOpen = false;
            sectionalOpen();
        }
    }

    else if (command == "OPEN_HELMET") {
        if (!topOpen) {
            integralOpen();
        }
    }

    else if (command == "CLOSE_HELMET") {
        if (topOpen) {
            integralOpen();
        }
    }
}
}
