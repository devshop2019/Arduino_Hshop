#include "kxn_wifi_ap.h"

// Set these to your desired credentials.
String ssid_ap = "Hshop_ESP32_Camera_Test";
const char *password_ap = "123456789";

void AP_wifi_init(){
  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }
  String tempString = EEPROM.readString(ADDR_SSID);
  if(tempString.length() < ssid_ap.length()){
    tempString = ssid_ap;
  }else{
    ssid_ap = tempString;
  }
  char tempArrayChar[50];
  tempString.toCharArray(tempArrayChar, tempString.length());
  WiFi.softAP(tempArrayChar, password_ap);
//  IPAddress myIP = WiFi.softAPIP();
}

void ReadSerial(){
  if(Serial.available()){
    String tempString = Serial.readStringUntil('\n');
    if(tempString.indexOf("name=") == 0){
      tempString = tempString.substring(5, (tempString.length() -1));
      Serial.println("Your name: " + tempString);
      tempString = String(DEFAULT_SSID_AP) + "_" + (String)tempString.toInt();
      ssid_ap = tempString;
      EEPROM.writeString(ADDR_SSID, tempString);
      EEPROM.commit();
      Serial.println("Save Eeprom OK");

//      WiFi.softAP(tempString, password_ap);

//      char tempArrayChar[50];
//      tempString.toCharArray(tempArrayChar, tempString.length());
//      Serial.println("Init WIFI with new SSID " + String(tempArrayChar));
      
//      WiFi.softAP(tempArrayChar, password_ap);
      String tempString2 = EEPROM.readString(ADDR_SSID);
      Serial.println("Init WIFI with new SSID " + tempString2);
      ESP.restart();
    }
  }
}
