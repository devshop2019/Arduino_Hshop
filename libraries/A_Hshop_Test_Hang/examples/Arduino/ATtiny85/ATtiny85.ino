
// Hướng dẫn: https://www.hackster.io/alaspuresujay/use-an-attiny85-with-arduino-ide-07740c
// File>preference> additional board manager url: https://raw.githubusercontent.com/digistump/arduino-boards-index/master/package_digistump_index.json
// Chọn board: Digispark (Default - 16.5Mhz)
// Bấm Nạp(KHÔNG kết nối mạch với máy tính)
// Chờ đến khi có thông báo "Plug in device now... (will timeout in 60 seconds)" -> cắm mạch vào

void setup() {                
  // initialize the digital pin as an output.
  pinMode(0, OUTPUT); //LED on Model B
  pinMode(1, OUTPUT); //LED on Model A   
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(1, HIGH);
  delay(5000);               // wait for a second
  digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(1, LOW); 
  delay(2000);               // wait for a second
}
