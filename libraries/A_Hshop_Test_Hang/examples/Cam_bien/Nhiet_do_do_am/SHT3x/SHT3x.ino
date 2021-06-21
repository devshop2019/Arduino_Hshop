/*
VCC - Màu nâu - cấp nguồn 2.15~5.5VDC.
GND - Màu đen - cấp nguồn 0VDC (Mass).
DATA - Màu vàng.
CLK - Màu xanh dương.
 */


#include "SHT3x.h"
SHT3x Sensor;
void setup() {
  
  Serial.begin(9600);
  Sensor.Begin();
}

void loop() {
  Sensor.UpdateData();
  
  Serial.print(Sensor.GetTemperature()); //Celsius
  Serial.write("\xC2\xB0"); //The Degree symbol
  Serial.print("C");
  Serial.print(" | ");
  
  Serial.print(Sensor.GetRelHumidity());
  Serial.print("%");
  Serial.print(" | ");

  Serial.print(Sensor.GetAbsHumidity()); //Torr by default
  Serial.print(" Torr");
  Serial.print(" | ");

  Serial.print(Sensor.GetAbsHumidity(SHT3x::psi)); //Torr by default
  Serial.print(" psi");
  Serial.print(" | ");

  Serial.print(Sensor.GetAbsHumidity(SHT3x::Pa)); //Torr by default
  Serial.print(" Pa");

  //And other...

  Serial.print(" Tolerance: ±");
  Serial.print(Sensor.GetAbsHumTolerance(SHT3x::mH2O));
  Serial.print(" mH2O");
  

  Serial.println();
  delay(333);
}
