#include <ESP32Servo.h>
#include <Arduino.h>

const int BUTTON_PIN = 12;
const int SERVO_PIN = 18;

Servo myServo;

bool servoAt10 = false;
bool lastButtonState = HIGH;

// Helper function to move the servo and kill the buzzing/beeping sound
void moveServo(int targetAngle) {
  // 1. Attach the servo right before moving (with standard pulse widths)
  myServo.attach(SERVO_PIN, 500, 2400);
  
  // 2. Send the movement command
  myServo.write(targetAngle);
  
  // 3. Wait for the physical cheek mechanism to finish moving
  delay(600); 
  
  // 4. Detach to completely cut power pulses and silence the motor
  myServo.detach();
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // ESP32 Servo setup requirement
  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50);
  
  // Initial position movement safely silenced
  moveServo(120);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(20); // Debounce delay
    if (digitalRead(BUTTON_PIN) == LOW) {
      servoAt10 = !servoAt10;
      
      // Call the silence-optimized movement function
      if (servoAt10) {
        moveServo(10);
      } else {
        moveServo(120);
      }
    }
  }

  lastButtonState = buttonState;
}
