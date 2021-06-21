
/*
            ***  5V  ***
               9600
               Echo(Tx)----12 (uno)
               Trig(Rx)----11 (uno)
*/

#include "HCSR04_simple_test.h"

UltraSonicDistanceSensor distanceSensor(11, 12);  
void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    Serial.println(distanceSensor.measureDistanceCm());
    delay(500);
}
