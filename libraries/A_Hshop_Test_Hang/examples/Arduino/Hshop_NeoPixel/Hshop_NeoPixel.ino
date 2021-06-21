// DI - 6 (ARDUINO)
// 5V - 5V(ARDUINO)
// GND - GND(ARDUINO);
// LUU Y TREN 16 BONG THI PHAI DUNG VIN KHOANG 6V , LAY VIN CAP CHO NEOPIXEL 
// VIETUNO - NAP ROI CAP NGUON RIENG

#include "Hshop_Adafruit_NeoPixel.h"
#define PIN            6
#define NUMPIXELS      144 // so led muon sang
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second

void setup() {

  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  for(int k=10;k<255;k++)
  { 
    k=k+50;
    Serial.println(k);
    for(int i=0;i<NUMPIXELS;i++){

    pixels.setPixelColor(i, pixels.Color(k+5,k+10,k)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
  } 
  }


}
