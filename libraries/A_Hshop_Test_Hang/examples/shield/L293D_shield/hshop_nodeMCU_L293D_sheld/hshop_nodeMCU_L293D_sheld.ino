
/*
1.nap code Node MCU
2.cam vao L239D
3.cam jumper Vin-VM
4.cap nguon - do VOM 2 cho dong co
*/

#define PWMA  D1         // L298N in1 motors Right           
#define DIRA  D3          // L298N in2 motors Right          
#define PWMB  D2           // L298N in3 motors Left         
#define DIRB  D4          // L298N in4 motors Left 

void setup() {
   pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB, OUTPUT);
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
}

void loop() {
  goT();
  delay(2000);
  Stop();
  delay(1000);
  goL();
  delay(2000);

}

void goT() {
  Serial.println("Tiến");
  analogWrite(PWMA,1023);
  analogWrite(PWMB,1023);
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,HIGH);  
}
void Stop() {
  Serial.println("Stop");
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
}


void goL() {
  Serial.println("Lùi");
  analogWrite(PWMA,1023);
  analogWrite(PWMB,1023);
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,LOW);  
}
