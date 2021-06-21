#include "Vietduino_Waterproof_Ultrasonic.h"

Vietduino_Ultrasonic::Vietduino_Ultrasonic(uint8_t _Trig_RX_, uint8_t _Echo_TX_, uint8_t _mode_){
  trigRX = _Trig_RX_;
  echoTX = _Echo_TX_;
  mode = _mode_;
  if(mode == 1){
    pinMode(trigRX, OUTPUT);
    pinMode(echoTX, INPUT);
  }
}

void Vietduino_Ultrasonic::begin(){
  if((mode == 2) || (mode == 3)){
    db_sa("begin ultrasonic");
    if(!sieuam){
      sieuam = new SoftwareSerial(echoTX, trigRX);
      sieuam->begin(9600);
    }
  }
}

int Vietduino_Ultrasonic::ping_cm(){
  switch(mode){
    case 3:
      if(sieuam)sieuam->write(0x55);
    case 2:
      readSieuAm_available3();
      return lastvalue_mm/10;
      break;
    default:
    return readMode_1();
      break;
  }
}

int Vietduino_Ultrasonic::readMode_1(){
  long duration;
  int distance;
  digitalWrite(trigRX, LOW);
  
  delayMicroseconds(5);
 // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigRX, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigRX, LOW);
  
  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoTX, HIGH,36000);
  
  // Calculate the distance:
  distance = duration*0.034/2;

  db_sa_t("pulse");
  db_sa(duration);
  return distance;
}
