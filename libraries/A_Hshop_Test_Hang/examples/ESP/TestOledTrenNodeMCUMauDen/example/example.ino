// Example sketch for testing OLED display

// We need to include Wire.h for I2C communication
#include <Wire.h>
#include "OLED.h"

// Declare OLED display

// y20m09d05 kxn Test ok voi https://hshop.vn/products/kit-rf-thu-phat-wifi-esp8266-nodemcu-oled-0-96-inch
// link library https://github.com/klarsys/esp8266-OLED

OLED display(SCL, SDA);

void setup() {
  Serial.begin(9600);
  Serial.println("OLED test! SDA: " + String(SDA));
  Serial.println("OLED test! SCL: " + String(SCL));

  // Initialize display
  display.begin();

  // Test message
  display.print("Hello World");
  delay(3*1000);

  // Test long message
  display.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
  delay(3*1000);

  // Test display clear
  display.clear();
  delay(3*1000);

  // Test message postioning
  display.print("TOP-LEFT");
  display.print("4th row", 4);
  display.print("RIGHT-BOTTOM", 7, 4);
  delay(3*1000);

  // Test display OFF
  display.off();
  display.print("3rd row", 3, 8);
  delay(3*1000);

  // Test display ON
  display.on();
  delay(3*1000);
}

int r = 0, c = 0;

void loop() {
  r = r % 8;
  c = micros() % 6;

  if (r == 0)
    display.clear();

  display.print("Hello World", r++, c++);

  delay(500);
}
