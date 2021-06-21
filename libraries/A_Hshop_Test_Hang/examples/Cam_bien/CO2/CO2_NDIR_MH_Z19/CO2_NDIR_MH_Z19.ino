/*
** SO do dau day:
* 
* ARDUINO UNO------------------CO2 SENSOR
*   5V----------------------V_in
*   Gnd---------------------Gnd
*   2-----------------------Tx(keo tro)
*   3-----------------------Rx(keo tro)
* --------------------------------------------
*/
#include <SoftwareSerial.h>;
 
SoftwareSerial mySerial(2, 3); // RX, TX
 
byte request[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 
unsigned char response[9];
 
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(5,INPUT);
}
 
void loop() 
{
  mySerial.write(request, 9);
  memset(response, 0, 9);
  mySerial.readBytes(response, 9);
  int i;
  byte crc = 0;
  for (i = 1; i < 8; i++) crc+=response[i];
  crc = 255 - crc;
  crc++;
 
  if ( !(response[0] == 0xFF && response[1] == 0x86 && response[8] == crc) ) {
    Serial.println("CRC error");
  } else {
    unsigned int HLconcentration = (unsigned int) response[2];
    unsigned int LLconcentration = (unsigned int) response[3];
    unsigned int co2 = (256*HLconcentration) + LLconcentration;
  
    Serial.println(co2);
    for (i = 0; i < 9; i++) {
      Serial.print("0x");
      Serial.print(response[i],HEX);
      Serial.print("  ");
    }
    Serial.println("  ");
 
  
  }
  delay(1000);
}
