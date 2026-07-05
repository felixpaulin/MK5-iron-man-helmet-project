Feature: Custom ESP32 AutoKing MK5 Helmet Controller

  Background:
    Given the helmet controller is powered
    
    And all servos are initialized
    
    And the helmet starts in the closed position


  Scenario: Sectional opening

    Given the helmet is closed

    When the sectional touch pad is pressed

    Then both cheek servos should open

    And the middle top section should open

    And the bottom faceplate should lift

    And the top assembly should move upward

    And the helmet state should become open


  Scenario: Sectional closing

    Given the helmet is open

    When the sectional touchpad is pressed again

    Then the top assembly should lower

    And the bottom faceplate should lower

    And the middle top section should close

    And both cheek servos should close

    And the helmet state should become closed


  Scenario: Integral opening

    Given the top assembly is closed

    When the integral touch pad is pressed

    Then both top servos should move upward

    And the integral state should become open


  Scenario: Integral closing

    Given the top assembly is open

    When the integral touch pad is pressed again

    Then both top servos should move downward

    And the integral state should become closed


  Scenario: TinyML voice sectional opening

    Given the esp32 s3 is installed 
    
    And tinyML is enabled

    And the helmet is closed

    When the user says "Section Helmet"

    Then the sectional opening sequence should execute


  Scenario: TinyML voice sectional closing

    Given the esp32 s3 is installed 
    
    And tinyML is enabled

    And the helmet is open

    When the user says "Lock Helmet"

    Then the sectional closing sequence should execute

  Scenario: TinyML voice intergal opening

    Given TinyML is enabled

    And the helmet is closed

    When the user says "Open Helmet"

    Then the integral opening should begin


  Scenario: TinyML voice intergal closing

    Given TinyML is enabled

    And the helmet is open

    When the user says "Close Helmet"

    Then the integral closing should begin


  Scenario: Servo anti-buzz logic

    Given a servo reaches its target position

    When movement has completed

    Then the servo should detach

    And buzzing should stop


  Scenario: Bottom servo dynamic hold

    Given the bottom servo is moving

    When the servo reaches the closed position

    Then the servo should remain attached

    And the helmet should stabilize

    And the servo should detach afterwards


  Scenario: LED eyes red

    Given the ESP32-S3 is installed

    When the user requests red eyes via tinyML

    Then the eye LEDs should become red


  Scenario: LED eyes blue/white-ish

    Given the ESP32-S3 is installed

    When the user requests blue eyes via tinyML

    Then the eye LEDs should become a blue/white-ish colour


  Scenario: Future LLM interaction

    Given WiFi is available

    And the LLM service is reachable

    When the user asks a question

    Then the question should be processed

    And a response should be generated

    And the speaker should play the response


  Scenario: Emergency recovery

    Given custom firmware fails

    When the original controller PCB is reinstalled

    Then the helmet should behave like stock firmware
