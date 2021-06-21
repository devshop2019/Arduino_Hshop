#include <Wire.h>
#include "OLED.h"
#include <ESP8266WiFi.h>

OLED display(SCL, SDA);

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");

  // Initialize display
  display.begin();
}

void loop(){
  display.clear();
  Serial.println("Scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0)
  {
    Serial.println("No networks found");
    //// --- ////
    display.print("No networks found", 0);
    //// --- ////
  }
  else
  {
    Serial.print(n); Serial.println(" networks found");
    //// --- ////
    String s = String(n);
    s = s + " networks found";
    char c[32];
    s.toCharArray(c, 32);
    display.print(c, 0);
    //// --- ////
    for (int i=1; i<=5 ; ++i) // Actully i<n, but Oled has limit row, therefore we need set i<5
    {
      // Print SSID and RSSI for each network found
      Serial.print(i); Serial.print(": "); Serial.println(WiFi.SSID(i));
      //// --- ////
      String wifi = String(i);
      wifi = wifi + ": " + String(WiFi.SSID(i));
      char WIFI[32];
      wifi.toCharArray(WIFI, 32);
      display.print(WIFI, i+1);
      //// --- ////
      delay(10);
    }
  }
  delay(5000);

  display.clear();
  uint32_t realSize = ESP.getFlashChipRealSize();
  //// --- ////
  String z = "Flash real size: ";
  z = z + String(realSize);
  z = z + " bytes";
  char C[32];
  z.toCharArray(C, 32);
  display.print(C, 0);
  delay(5000);
}
