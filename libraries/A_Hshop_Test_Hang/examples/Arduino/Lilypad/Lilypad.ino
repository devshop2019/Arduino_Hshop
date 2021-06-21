// Thứ tự chân GND                 -  B
// Thứ tự chân GND                 -  ..
// Thứ tự chân VCC                 -  ..
// Thứ tự chân RXD  - TXD CP1202   -  ..
// Thứ tự chân GND  - RXD CP2102   -  ..
// Thứ tự chân 6 nối vào Reset     -  G

void setup()
{
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);   
  delay(500);                   
  digitalWrite(13, LOW);   
  delay(1000);                     
}
