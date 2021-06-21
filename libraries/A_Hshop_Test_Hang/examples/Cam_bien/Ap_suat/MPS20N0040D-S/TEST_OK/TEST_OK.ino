
// ***  5V  ***

#define PIN_SCK 3
#define PIN_OUT 2

#include "Q2HX711.h"
Q2HX711 hx711(PIN_OUT, PIN_SCK);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(hx711.read());
  delay(50);
}
