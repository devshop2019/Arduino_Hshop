/*
       Vcc - 5V
       Trig - 7
       Echo - 8
       GND - GND
*/

#include "hshop_HCSR04.h"

UltraSonicDistanceSensor distanceSensor(7,8);  // Initialize sensor that uses digital pins 13 and 12.

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    Serial.println(distanceSensor.measureDistanceCm());
    delay(300);
}
