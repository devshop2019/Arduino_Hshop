/*
 (Đỏ)    Vcc - 5v
 (Đen)   GND - GND
 (Trắng) A0 - Tout
 (Vàng)  A1 - Hout
 (phai co tro 10k nhu tren web)
 */




int tempPins = A0; //T-out
int humidPins = A1; //T-out
int refPin     = A5; //Vcc

double tempMap[51] = {28267,27026,25847,24726,23661,22650,21686,20771
                    ,19901,19070,18371,17610,16885,16194,15535,14907
                    ,14308,13736,13190,12670,12172,11697,11244,10810,10369
                    ,10000,9621,9259,8912,8581,8263,7959,7668,7389,7122
                    ,6866,6621,6385,6160,5943,5736,5537,5345,5162,4986
                    ,4816,4654,4497,4347,4203,4101};

void setup() {
  // put your setup code here, to run oncei:
  Serial.begin(9600);
  analogReference(DEFAULT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  double temp = analogRead(tempPins)*5.0/1023;
  double humid = analogRead(humidPins)*5.0/1023;
  double tempValue = 50000.0/temp - 10000;
  double humidValue = 70*humid/2.1;
  if(tempValue > tempMap[0] || tempValue < tempMap[50]){
    Serial.println("Temperature: Out of range");
    return;
  }

  for(int i = 0; i<=50; i++){
    if(tempValue > tempMap[i]){
      Serial.println("Temperature: " + String(i-1) + "*C\tHumidnity: " + String(humidValue) + "%");
      break;
    }else if(tempValue == tempMap[50]){
      Serial.println("Temperature: " + String(50) + "*C\tHumidnity: " + String(humidValue) + "%");
      break;
    }
  }
  delay(500);
}
