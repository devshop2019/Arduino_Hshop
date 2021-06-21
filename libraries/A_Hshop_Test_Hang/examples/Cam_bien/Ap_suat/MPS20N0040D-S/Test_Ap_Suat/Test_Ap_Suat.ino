
// ***  5V  ***

#include "HX711.h" // libreria gestione convertitore analogico-digitale
HX711 scale;

void setup(){
  Serial.begin(9600);
//  Serial.println("HX711 Demo");
//
//  Serial.println("Inizializzazione della scala");
  scale.begin(A1, A0);
//
//  Serial.println("Prima si impostare la scala:");
//  Serial.print("Lettura: \t\t");
//  Serial.println(scale.read());      // stampa della lettura non elaborata dall'ADC
//
//  Serial.print("Lettura della media \t\t");
//  Serial.println(scale.read_average(20));   // stampa la media di 20 letture dall'ADC
//
//  Serial.print("Ottiene il valore: \t\t");
//  Serial.println(scale.get_value(5));
// // stampa la media di 5 letture dall'ADC meno il peso della tara (non ancora impostato)
//
//  Serial.print("get units: \t\t");
//  Serial.println(scale.get_units(5), 1);
//// print the average of 5 readings from the ADC minus tare weight (not set) divided
//// by the SCALE parameter (not set yet)
//
  scale.set_scale(5000.f);
//// this value is obtained by calibrating the scale with
//// known weights; see the README for details
  scale.tare(); // reset the scale to 0
//
//  Serial.println("After setting up the scale:");
//
//  Serial.print("read: \t\t");
//  Serial.println(scale.read());
//// print a raw reading from the ADC
//
//  Serial.print("read average: \t\t");
//  Serial.println(scale.read_average(20));
//// print the average of 20 readings from the ADC
//
//  Serial.print("get value: \t\t");
//  Serial.println(scale.get_value(5));
//// print the average of 5 readings from the ADC minus the tare weight, set with tare()
//
//  Serial.print("get units: \t\t");
//  Serial.println(scale.get_units(5), 1);
//// print the average of 5 readings from the ADC minus tare weight, divided
//  // by the SCALE parameter set with set_scale
//
//  Serial.println("Lettura:");
}

void loop(){
  Serial.println(scale.read());
  scale.power_down();  // mette l'ADC in modalità sleep
  delay(10);
  scale.power_up();
  
//  Serial.print("one reading:\t");
//  Serial.print(scale.get_units(), 1);
  scale.power_down();  // mette l'ADC in modalità sleep
  delay(500);
  scale.power_up();
}
