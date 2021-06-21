
/*
B1: Nap code vao arduino
B2: Gan sheild
B3: Mo serial monitor Baureat 9600 lam theo huong dan 
*/

#include "SoftwareSerial.h"
SoftwareSerial    sim(12,13);
#define mSerial   Serial
unsigned long time1 = 0;
bool b_en = false, sim_em = false;

void setup() {
  // put your setup code here, to run once:
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
digitalWrite(10, 0);digitalWrite(11, 1);
digitalWrite(10, 1);digitalWrite(11, 0);
sim.begin(9600);
mSerial.begin(9600);
mSerial.println("Test sim800ds Shield dung Software Serial 12-TxSim; 13-RxSim");
mSerial.println("bam ky tu \"%\" de blink relay 1s");
mSerial.println("bam ky tu \"!\" de test AT command cho Sim");

}

void loop() {
  // put your main code here, to run repeatedly:
  readSerial();
  blink_relay();
  TestSim();
}

void readSerial(){
  if(mSerial.available()){
    char temChar = mSerial.read();
    sim.write(temChar);
    if(temChar == '%'){
      b_en = !b_en;
    }else if(temChar == '!'){
      sim_em = true;
    }
  }
  if(sim.available()){
    mSerial.write(sim.read());
  }
}

void blink_relay(){
  if(b_en){
    if(millis() - time1 >= 1000){
      time1 = millis();
      digitalWrite(10, !digitalRead(10));
      digitalWrite(11, !digitalRead(11));
    }
  }
}

void SendCommand(String command_, unsigned long _timeDelay_ = 500){
  sim.println(command_);
  delay(_timeDelay_);
  while(sim.available()){
    mSerial.write(sim.read());
  }
}

void TestSim(){
  if(sim_em){
    SendCommand("AT");
    SendCommand("AT");
    SendCommand("AT+CUSD=1");
    SendCommand("AT+CLIP=1");
    SendCommand("AT+CNMI=2,2");
    SendCommand("AT+CMGF=1");
    SendCommand("AT+CSCS=\"GSM\"");
    SendCommand("ATD*101#;");
    sim_em = false;
  }
  
}
