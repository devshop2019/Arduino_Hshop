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
#include "epd2in7b.h"
#include "imagedata.h"
#include "epdpaint.h"

#define COLORED     1
#define UNCOLORED   0

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	Epd epd;

	Serial.print("e-Paper init and clear\r\n");
	if (epd.Init() != 0) {
		Serial.print("e-Paper init failed\r\n");
	return;
	}

	/* This clears the SRAM of the e-paper display */
	epd.ClearFrame();

	/**
	* Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
	* In this case, a smaller image buffer is allocated and you have to 
	* update a partial display several times.
	* 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
	*/
	unsigned char image[1024];
	Paint paint(image, 176, 24);    //width should be the multiple of 8 

	paint.Clear(UNCOLORED);
	paint.DrawStringAt(0, 0, "e-Paper Demo", &Font16, COLORED);
	epd.TransmitPartialBlack(paint.GetImage(), 16, 32, paint.GetWidth(), paint.GetHeight());

	paint.Clear(COLORED);
	paint.DrawStringAt(2, 2, "Hello world!", &Font20, UNCOLORED);
	epd.TransmitPartialRed(paint.GetImage(), 0, 64, paint.GetWidth(), paint.GetHeight());

	paint.SetWidth(64);
	paint.SetHeight(64);

	paint.Clear(UNCOLORED);
	paint.DrawRectangle(0, 0, 40, 50, COLORED);
	paint.DrawLine(0, 0, 40, 50, COLORED);
	paint.DrawLine(40, 0, 0, 50, COLORED);
	epd.TransmitPartialBlack(paint.GetImage(), 10, 130, paint.GetWidth(), paint.GetHeight());

	paint.Clear(UNCOLORED);
	paint.DrawCircle(32, 32, 30, COLORED);
	epd.TransmitPartialBlack(paint.GetImage(), 90, 120, paint.GetWidth(), paint.GetHeight());

	paint.Clear(UNCOLORED);
	paint.DrawFilledRectangle(0, 0, 40, 50, COLORED);
	epd.TransmitPartialRed(paint.GetImage(), 10, 200, paint.GetWidth(), paint.GetHeight());

	paint.Clear(UNCOLORED);

	paint.DrawFilledCircle(32, 32, 30, COLORED);
	epd.TransmitPartialRed(paint.GetImage(), 90, 190, paint.GetWidth(), paint.GetHeight());

	/* This displays the data from the SRAM in e-Paper module */
	Serial.print("show paint.image\r\n");
	epd.DisplayFrame();

	/* This displays an image */
	Serial.print("show array\r\n");
	epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);
 
 paint.DrawFilledRectangle(0, 0, 40, 50, UNCOLORED);
 paint.Clear(UNCOLORED);

	/* Deep sleep */
	Serial.print("sleep\r\n");
	epd.Sleep();
}

void loop() {
  // put your main code here, to run repeatedly:

}
