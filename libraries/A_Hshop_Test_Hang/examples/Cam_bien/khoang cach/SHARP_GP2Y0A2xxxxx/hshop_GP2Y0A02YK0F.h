#ifndef GP2Y0A02YK0F_h
#define GP2Y0A02YK0F_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

class GP2Y0A02YK0F
{
  public:
    GP2Y0A02YK0F();
    void begin();
    void begin(int sensorPin);
    int getDistanceRaw();
    int getDistanceVolt();
    int getDistanceCentimeter();

    boolean isCloser(int threshold);
    boolean isFarther(int threshold);

  private:
    int _sensorPin;
};
#endif
