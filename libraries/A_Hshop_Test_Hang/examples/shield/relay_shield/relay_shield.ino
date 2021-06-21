byte rl[] = {2,3,4,5,6,7,8,9,10,11,12,13};

void setup() {
  for (byte i = 2; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
  }

}

// the loop function runs over and over again forever
void loop()
{
    for (byte i = 2; i <= 13; i++)
    {
      digitalWrite(i, HIGH);
      delay(50);
    }
    delay(1000);
    for (byte i = 13; i >= 2; i--)
    {
      digitalWrite(i, LOW);
      delay(50);
    }
    delay(1000);
}

void runled() {

}
