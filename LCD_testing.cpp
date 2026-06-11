#ifdef ARDUINO
#include <Arduino.h>
#include <Wire.h>
#endif

#if !defined(ARDUINO)
#include <cstdint>
#include <cstdio>

using byte = uint8_t;
const int HEX = 16;

class HardwareSerial {
public:
  void begin(int) {}
  bool operator!() const { return false; }
  void println(const char* s) { std::puts(s); }
  void print(const char* s) { std::fputs(s, stdout); }
  void print(unsigned int value, int base) {
    if (base == HEX)
      std::printf("%X", value);
    else
      std::printf("%u", value);
  }
};

class TwoWire {
public:
  void begin(int, int) {}
  void beginTransmission(uint8_t) {}
  uint8_t endTransmission() { return 0; }
};

HardwareSerial Serial;
TwoWire Wire;

inline void delay(unsigned long) {}
#endif

void setup() {
  // Use Keyestudio ESP32 Plus hardware I2C pins
  Wire.begin(21, 22);
  Serial.begin(115200);
  while (!Serial);
  Serial.println("\n--- I2C Scanner Ready ---");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Scanning for I2C devices...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Found I2C device at address: 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    }
  }
 
  if (nDevices == 0) {
    Serial.println("No I2C devices found. Check your wiring!\n");
  } else {
    Serial.println("Scan complete.\n");
  }

  delay(3000); // Scan every 3 seconds
}