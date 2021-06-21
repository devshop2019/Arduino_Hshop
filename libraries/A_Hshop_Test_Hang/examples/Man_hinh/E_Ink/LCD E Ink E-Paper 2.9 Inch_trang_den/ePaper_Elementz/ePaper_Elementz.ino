/*
 e-Paper    -    Arduino

VCC        -     3V3
GND        -     GND
D/C        -     D9
SDI        -     D11
CS         -     D10
CLK        -     D13
BUSY       -     D7
*/
#include <SPI.h>
#include "epd2in9.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED     1
#define UNCOLORED   0

unsigned char image[1024];
Paint paint(image, 0, 0); 
Epd epd;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (epd.Init(lut_full_update) != 0) {
      Serial.print("e-Paper init failed");
      return;
  }
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();

  epd.SetFrameMemory(IMAGE_DATA);
  epd.DisplayFrame();
  epd.SetFrameMemory(IMAGE_DATA);
  epd.DisplayFrame();  

  paint.SetRotate(ROTATE_90);
  paint.SetWidth(20);
  paint.SetHeight(30);

  paint.Clear(COLORED);
  paint.DrawStringAt(0, 0, "^^", &Font12, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 80, 135, paint.GetWidth(), paint.GetHeight());// do cao , trai - phai cua chu Hshop
  epd.DisplayFrame();
}
void loop() {
  // put your main code here, to run repeatedly:

}
