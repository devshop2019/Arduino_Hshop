/*
Nếu thấy không chạy thì kiểm tra lại chân kết nối 
*/

int InA=12;
int InB=13;
int EA=10;
int EB=11;
int Buzzer_pin = 4;
void setup() {
  // put your setup code here, to run once:
pinMode(InA,OUTPUT);
pinMode(InB,OUTPUT);
pinMode(EA,OUTPUT);
pinMode(EB,OUTPUT);
pinMode(Buzzer_pin,OUTPUT);

digitalWrite(Buzzer_pin, 1);  // buzzer active HIGH
delay(700);
digitalWrite(Buzzer_pin, 0);
delay(700);

//set speed
analogWrite(EB,255);
analogWrite(EA,255);

}

void loop() {
  // put your main code here, to run repeatedly:
  
digitalWrite(InA,HIGH);
digitalWrite(InB,HIGH);
delay(1000);
digitalWrite(InA,LOW);
digitalWrite(InB,LOW);
delay(1000);
}
