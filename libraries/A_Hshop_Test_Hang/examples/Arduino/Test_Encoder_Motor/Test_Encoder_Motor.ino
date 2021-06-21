#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,16,2);

#define CLK 2 // Chân Encoder CLK (kênh A), có thể dùng Ngắt 0
#define DT 3  // Chân Encoder DT  (kênh B), có thể dùng Ngắt 1

volatile long counter = 0L;     // Số xung Encoder
volatile char currentDir = ' '; // ...
unsigned long timedelay = 0ul;  // Thời gian mỗi lần cập nhập LCD

void setup()
{
  // Khởi tạo LCD
  lcd.begin(); 
  lcd.backlight();

  // Cài đặt các chân Encoder là Input
  pinMode(CLK,INPUT_PULLUP);
  pinMode(DT,INPUT_PULLUP);

  // Cài đặt Serial Monitor
  // Serial.begin(9600);

  // Bật Ngắt 0, trên kênh A
  attachInterrupt(0, updateEncoder, FALLING);
}

void loop()
{
  if (millis()-timedelay >= 300ul)
  {       
    lcd.setCursor(0,0); 
    lcd.print("   ClockWise "); lcd.print(currentDir); lcd.print("  ");
    lcd.setCursor(0,1);
    lcd.print("Encoder: "); lcd.print(counter); lcd.print("  ");
    timedelay = millis();
  }
}

void updateEncoder()                          // Thực hiện mỗi khi kênh A có cạnh xuống (FALLING)
{
  detachInterrupt(0);                         // Tắt Ngắt tạm thời
  if(digitalRead(DT))                         // Kênh A false, kênh B high  --> A != B
  {
    counter ++;
    currentDir = '+';
  }
  else                                        // Kênh A false, kênh B false --> A = B
  {
    counter --;
    currentDir = '-';
  }
  // Serial.print(currentDir); Serial.print(" : "); Serial.println(counter);
  attachInterrupt(0, updateEncoder, FALLING); // Bật lại Ngắt
}
