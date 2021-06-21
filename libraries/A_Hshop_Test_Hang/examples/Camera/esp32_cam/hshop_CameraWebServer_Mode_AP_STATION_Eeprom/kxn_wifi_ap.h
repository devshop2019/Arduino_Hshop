#ifndef _kxn_wifi_ap_h
#define _kxn_wifi_ap_h

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "EEPROM.h"

#define EEPROM_SIZE 1000
#define ADDR_SSID   0
#define DEFAULT_SSID_AP   "Hshop_ESP32_Camera_Test"

// Set these to your desired credentials.
extern String ssid_ap;
extern const char *password_ap;
extern void AP_wifi_init();
extern void ReadSerial();
#endif
