#include "WiFi.h"

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 4, /* data=*/ 5, /* reset=*/ U8X8_PIN_NONE);   // ESP32 Thing, pure SW emulated I2C

void setup(void)
{
	Serial.begin(115200);

	// Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");

 	u8g2.begin();
 	u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
}

void loop(void)
{
	Serial.println("Scan start");
	////
	u8g2.clearBuffer();					// clear the internal memory
	u8g2.drawStr(0,10,"Scan start");	// write something to the internal memory
  	u8g2.sendBuffer();					// transfer internal memory to the display
	////

  	delay(1000);
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    ////
    u8g2.clearBuffer();					// clear the internal memory
	u8g2.drawStr(0,10,"Scan done");		// write something to the internal memory
  	u8g2.sendBuffer();					// transfer internal memory to the display
    ////
    delay(1000);

    if (n==0)
    {
        Serial.println("No networks found");
        ////
        u8g2.clearBuffer();
        u8g2.drawStr(0,10,"No networks found");
        u8g2.sendBuffer();
        ////
    }
    else
    {
        Serial.print(n);
        Serial.println(" Networks found");
        ////
        u8g2.clearBuffer();
        String s = String(n);
    	s = s + " Networks found";
    	char c[32];
    	s.toCharArray(c, 32);
    	u8g2.drawStr(0,10,c);
        u8g2.sendBuffer();
        ////
	    for(int i=0; i<5; ++i)	// limit display
	    {
	        // Print SSID and RSSI for each network found
	        Serial.print(i + 1); Serial.print(": "); Serial.println(WiFi.SSID(i));
	        ////
	        String wifi = String(i);
      		wifi = wifi + ": " + String(WiFi.SSID(i));
      		char WIFI[32];
      		wifi.toCharArray(WIFI, 32);
      		u8g2.drawStr(0,(i+2)*10,WIFI);
        	u8g2.sendBuffer();
	        ////
	        delay(10);
	    }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
}
