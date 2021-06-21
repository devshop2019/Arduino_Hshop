// Date and time functions using a DS3231 RTC connected via I2C and Wire lib

#include "Vietduino_Button.h"
#include "Vietduino_Led.h"
#include "Vietduino_Manager_Priority.h"
#include "Scheduler.h"
#include <dht_nonblocking.h>

#include "SoftwareSerial.h"

#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

static const int BUTTON_RESET_PIN   = D9;
static const int BUZZER_PIN         = D10;
static const int DHT_SENSOR_PIN     = 11;

DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_TYPE_11);
float temperature;
float humidity;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

Vietduino_Button btnReset;

Vietduino_Led myBuzzer(BUZZER_PIN, HIGH);

DateTime timeAlarm(0,0,0,15,2,0); // (y,m,d,h,m,s)

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

unsigned long lastTimeCheckRTC = 0;
unsigned long lastTimeDisplayDateAndSensor = 0;

bool b_alarmFlag = false;
bool b_showDate = true;

void buttonInit(){
  btnReset.begin(BUTTON_RESET_PIN, LOW); // btnReset.begin(PIN, Active LOW or HIGH)
}

void BuzzerInit(){
  myBuzzer.write(200,200,2); // Beep beep 2 times
}

void RTCInit(){
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Can't find RTC!");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
    // This line sets the RTC with an explicit date & time, for example to set
    // May 13, 2021 at 10:54am you would call:
//     rtc.adjust(DateTime(2021, 5, 13, 10, 54, 0));
  }
}

void lcdInit() {
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.setCursor(6, 0);
  lcd.print("BCIS");
  lcd.setCursor(2, 1);
  lcd.print("Weather Clock");
  delay(3000);
}

void setup () {
  buttonInit(); // INPUT must be declared first!!!
  Serial.begin(9600);
  SerialHelp();
  lcdInit();
  RTCInit();  
  BuzzerInit();
}

void loop () {
  VIETDUINO_UPDATE;  // Used for Vietduino Library
  checkSerial();
  checkButton();
  Check_DHT_Sensor();
  checkRTC();
  
}

void checkSerial(){
  if(Serial.available()){
    String tempDataString = Serial.readStringUntil('\n');
//    Serial.println("Your input String data: " + tempDataString);
//    Serial.println(tempDataString.length());

    if(tempDataString.indexOf("/") > -1){   // 26-05-2021/15:30:09  (DD-MM-YYYY/hh:mm:ss)      => Day = 20; Month = 5; Year = 2021; hour = 15; minute = 30; second = 9
      if(tempDataString.length() == 20){
        int tempDay = tempDataString.substring(0,2).toInt();
        Serial.println("Day: " + String(tempDay));
        
        int tempMonth = tempDataString.substring(3,5).toInt();
        Serial.println("Month: " + String(tempMonth));
        
        int tempYear = tempDataString.substring(6,10).toInt();
        Serial.println("Year: " + String(tempYear));
        
        int tempHour = tempDataString.substring(11,13).toInt();
        Serial.println("Hour: " + String(tempHour));
        
        int tempMinute = tempDataString.substring(14,16).toInt();
        Serial.println("Minute: " + String(tempMinute));
        
        int tempSecond = tempDataString.substring(17,19).toInt();
        Serial.println("Second: " + String(tempSecond));

        rtc.adjust(DateTime(tempYear, tempMonth, tempDay, tempHour, tempMinute, tempSecond));
        
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Set RTC!");
        lcd.setCursor(2, 1);
        lcd.print("Please wait!");
        Serial.println("Set time for RTC OK!");
        delay(2000);
        lcd.clear();
      }
    }else if(tempDataString.indexOf(">") > -1){   // >15:30:09  (DD-MM-YYYY/hh:mm:ss)      => Alarm when hour = 15; minute = 30; second = 9
      if(tempDataString.length() == 10){
        int tempHour = tempDataString.substring(1,3).toInt();
        Serial.println("Hour: " + String(tempHour));
        
        int tempMinute = tempDataString.substring(4,6).toInt();
        Serial.println("Minute: " + String(tempMinute));
        
        int tempSecond = tempDataString.substring(7,9).toInt();
        Serial.println("Second: " + String(tempSecond));

        timeAlarm = DateTime(0, 0, 0, tempHour, tempMinute, tempSecond);
        
        Serial.println("Set time Alarm OK!");
      }
    }else if((tempDataString.indexOf("help") > -1) || (tempDataString.indexOf("HELP") > -1)){
      SerialHelp();
    }
  }
}

void checkButton(){
  if(btnReset.available(_CLICKED_)){
    b_alarmFlag = false;
    myBuzzer.stop();
  }else if(btnReset.available(_DOUBLE_CLICKED_)){
    Serial.println("The timeAlarm was set + 10 seconds!");
    timeAlarm = rtc.now() + TimeSpan(10);
  }
}

void checkRTC() {
  if (millis() - lastTimeCheckRTC >= 1000) { // 
    lastTimeCheckRTC = millis();
    checkAlarmPerSecond();
    LCD_Display();
  }
}

void checkAlarmPerSecond(){
  DateTime now = rtc.now();
  if((now.hour() == timeAlarm.hour()) && (now.minute() == timeAlarm.minute()) && (now.second() == timeAlarm.second())) {
    b_alarmFlag = true;
    myBuzzer.write(100,100,5,1000); // .....          .....          .....          .....          
  }
}

static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 1000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

void Check_DHT_Sensor(){
  if( measure_environment( &temperature, &humidity ) == true )
  {
//    Serial.print( "T = " );
//    Serial.print( temperature, 1 );
//    Serial.print( " deg. C, H = " );
//    Serial.print( humidity, 1 );
//    Serial.println( "%" );
  }
}

String GetStringDate() {
  char buffer[25]; // large enough for any DateTime, including invalid ones
  DateTime now = rtc.now();
  sprintf(buffer, "%02d-%02d-%u", now.day(), now.month(), now.year());
  return String(buffer);
}

String GetStringTime() {
  char buffer[25]; // large enough for any DateTime, including invalid ones
  DateTime now = rtc.now();
  sprintf(buffer, "%u:%02d:%02d", now.hour(), now.minute(), now.second());
  return String(buffer);
}

String GetString_DHT_Value(){
  String tempString = String(temperature) + char(223) + "C " + String(humidity) + "%    ";
  
  return tempString;
}

void LCD_Display() {
  DateTime now = rtc.now();
  lcd.setCursor(4, 0);
  lcd.print(GetStringTime());

  if(b_alarmFlag){
    lcd.setCursor(0, 1);
    lcd.print("      ALarm     ");
  }else{
    if(millis() - lastTimeDisplayDateAndSensor >= 3000){
      lastTimeDisplayDateAndSensor = millis();
      lcd.setCursor(1, 1);
      if(b_showDate == true){
        lcd.print("  ");  // Add 2 space
        lcd.print(GetStringDate());
        lcd.print("     "); // Add 4 space
      }else{
        lcd.print(GetString_DHT_Value());
      }
      
      b_showDate = !b_showDate;
    }
  }
}

void SerialHelp(){
  Serial.println(F("  Welcome to BCIS Weather Clock"));
  Serial.println(F("========================"));
  Serial.println(F("  To adjust Date and Time, please using command: \"DD-MM-YYYY/hh:mm:ss\". Example:"));
  Serial.println(F("Day = 26; Month = 5; Year = 2021; hour = 15; minute = 30; second = 4"));
  Serial.println();
  Serial.print(F("26-05-2021/15:30:04\n"));
  Serial.println();
  Serial.println(F("------------"));
  Serial.println(F("  To setup Time Alarm, please using command: \">hh:mm:ss\". Example: Setup Alarm when"));
  Serial.println(F("hour = 15; minute = 30; second = 9"));
  Serial.println();
  Serial.print(F(">15:30:09\n"));
  Serial.println();
  Serial.println(F("------------"));
  Serial.println(F("  \"help\" to show this message again. Example:"));
  Serial.println();
  Serial.println(F("help"));
  Serial.println();
}
