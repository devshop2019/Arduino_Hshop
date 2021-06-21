/*
e-Paper    -    Arduino

VCC        -     3v3
GND        -     GND
D/C / DC   -     D9
SDI / DIN  -     D11
CS         -     D10
CLK        -     D13
BUSY       -     D7
RST        -     D8
 */

#include <SPI.h>
#include "epd1in54b.h"
#include "imagedata.h"

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Epd epd;
    if (epd.Init() != 0) {
        Serial.print("e-Paper init failed");
        return;
    }
    epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);
}

void loop() {
  // put your main code here, to run repeatedly:

}
