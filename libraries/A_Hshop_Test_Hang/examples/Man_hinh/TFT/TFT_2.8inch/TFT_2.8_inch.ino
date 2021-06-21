/*
            ***  5V  ***
  Nên dùng điện trở có giá trị 4K7 (Trong video là 10K) để nối tiếp với các chân tín hiệu!
*/

#include "Adafruit_GFX.h"     // Библиотека обработчика графики
#include "Adafruit_ILI9341.h" // Программные драйвера для дисплеев ILI9341
#include "URTouch.h"          // Библиотека для работы с сенсорным экраном

#define TFT_DC 11              // Пин подключения вывода D/C дисплея
#define TFT_CS 13             // Пин подключения вывода CS дисплея
#define TFT_RST 12              // Если вывод дисплея RESET подключен к питанию или через кнопку RESET на Arduino
#define TFT_MISO 8           // Пин подключения вывода дисплея SDO(MISO)
#define TFT_MOSI 10           // Пин подключения вывода дисплея SDI(MOSI)
#define TFT_CLK 9            // Пин подключения вывода дисплея SCK
/* 
//  Mega 2560 Hardware SPI
#define TFT_MOSI 51           // Пин подключения вывода дисплея SDI(MOSI)
#define TFT_CLK 52            // Пин подключения вывода дисплея SCK
#define TFT_MISO 50           // Пин подключения вывода дисплея SDO(MISO)
*/


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);  // Создаем объект дисплея и сообщаем библиотеке распиновку для работы с графикой

#define t_SCK 7               // Пин подключения вывода дисплея T_CLK
#define t_CS 6                // Пин подключения вывода дисплея T_CS
#define t_MOSI 5              // Пин подключения вывода дисплея T_DIN
#define t_MISO 4              // Пин подключения вывода дисплея T_DOUT
#define t_IRQ 3               // Пин подключения вывода дисплея T_IRQ

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ); // Создаем объект сенсорного модуля и сообщаем библиотеке распиновку для работы с ним

void setup(){
  tft.begin();                      // Инициализируем начало работы с графическим дисплеем
  tft.setRotation(1);               // Переводим дисплей в альбомную ориентацию
  Serial.begin(115200);
  ts.InitTouch();                   // Инициализируем сенсорный модуль дисплея 
  ts.setPrecision(PREC_EXTREME);    // Определяем необходимую точность обработки нажатий: PREC_LOW - низкая, PREC_MEDIUM - средняя, PREC_HI - высокая, PREC_EXTREME - максимальная

  tft.setTextColor(ILI9341_WHITE);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(2);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(55,5);              // Определяем координаты верхнего левого угла области вывода
  tft.print(utf8rus("Hshop.vn ") + "Test TouchTFT");  // Выводим текст; Функция utf8rus конвертирует текст в русский, если библиотека Adafruit_GFX оптимизирована для работы с кириллицей
  tft.setTextColor(ILI9341_GREEN);  // Определяем цвет текста для вывода на экран
  tft.setCursor(20,220);            // Определяем координаты верхнего левого угла области вывода
  tft.print("Hshop.vn TFT 2.8inch SPI");    // Выводим текст
}
 
void loop()
{
  int x, y;                         // Переменные для работы с координатами нажатий
 
  while(ts.dataAvailable())         // Пока имеются данные с сенсорного модуля
  {
    ts.read();                      // Считываем с него данные
    x = 320-ts.getX();                  // Считываем координату нажатия X
    y = 230-ts.getY();                  // Считываем координату нажатия Y
//      Serial.println("x=   "+String(x)+" --- y="+String(y));
    
    if((x!=-1) && (y!=-1))          // Если обе координаты в положительном диапазоне (т.е. если есть нажатие)
    {
      x += 13;                      // Корректируем координату с учетом калибровочных данных
      y += 4;                       // Корректируем координату с учетом калибровочных данных
      int radius = 4;               // Определяем радиус разрисовки
      tft.fillCircle(x, y, radius, ILI9341_YELLOW); // Рисуем окружность, закрашенную желтым 
    }
  }
}
// Начало функции обработки кириллических символов
String utf8rus(String source)  // Функция для конвертации русских символов из двубайтовой кодировки в однобайтовую
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };
  k = source.length(); i = 0;
  while (i < k) {
    n = source[i]; i++;
 
    if (n >= 0xBF){
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x2F;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB7; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x6F;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
  return target;
}
// Конец функции обработки кириллических символов
