/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
// defines pins numbers
const int stepPin_1 = 2; 
const int dirPin_1 = 5; 

const int stepPin_2 = 3; 
const int dirPin_2 = 6;
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin_1,OUTPUT); 
  pinMode(dirPin_1,OUTPUT);

  pinMode(stepPin_2,OUTPUT); 
  pinMode(dirPin_2,OUTPUT);
}
void loop() {
  digitalWrite(dirPin_1,HIGH); // Enables the motor to move in a particular direction
  digitalWrite(dirPin_2,HIGH);
  // Makes 800 pulses for making one full cycle rotation
  for(int x = 0; x < 800; x++) {
    digitalWrite(stepPin_1,HIGH); 
    digitalWrite(stepPin_2,HIGH);
    delayMicroseconds(1000); 
    digitalWrite(stepPin_1,LOW);
    digitalWrite(stepPin_2,LOW);
    delayMicroseconds(1000); 
  }
  delay(2000);
  
  digitalWrite(dirPin_1,LOW); //Changes the rotations direction
  digitalWrite(dirPin_2,LOW);
  // Makes 800 pulses for making one full cycle rotation
  for(int x = 0; x < 800; x++) {
    digitalWrite(stepPin_1,HIGH);
    digitalWrite(stepPin_2,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin_1,LOW);
    digitalWrite(stepPin_2,LOW);
    delayMicroseconds(1000);
  }
  delay(2000);
}
