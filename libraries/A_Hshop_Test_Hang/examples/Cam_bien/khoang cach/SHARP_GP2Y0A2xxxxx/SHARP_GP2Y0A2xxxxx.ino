/*
              ***  5V  ***
      Do - 5V
      DEN - GND
      VANG - A0  
        9600
*/


#include "hshop_GP2Y0A02YK0F.h"
#include "hshop_LCD_I2C.h"
#include <Wire.h> 

LiquidCrystal_I2C lcd(0x27,16,2);
GP2Y0A02YK0F irSensor;
int distance;

void setup()
{
  Serial.begin(9600);
  irSensor.begin(A0);  //  Assign A0 as sensor pin
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  /*lcd.setCursor(3,0);
  lcd.print("Hello, ^^!");
  lcd.setCursor(2,1);
  lcd.print("Good morning");
  */
}

void loop()
{
  distance = irSensor.getDistanceCentimeter();
  Serial.print("\nDistance in centimeters: ");
  Serial.print(distance);  
  lcd.setCursor(0,0);
  lcd.print(String(distance) + " cm");
  delay(500); 
}
