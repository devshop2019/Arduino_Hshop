#include "hshop_L293D.h"

AF_DCMotor motor4(4, MOTOR12_64KHZ); // tạo động cơ #2, 64KHz pwm
AF_DCMotor motor3(3, MOTOR12_64KHZ); // tạo động cơ #2, 64KHz pwm
AF_DCMotor motor1(1, MOTOR12_64KHZ); // tạo động cơ #2, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // tạo động cơ #2, 64KHz pwm
void setup() {

  Serial.begin(9600);           // mở cổng Serial monitor 9600 bps

  Serial.println("Hello my racing");

  motor1.setSpeed(255);     // chọn tốc độ maximum 255`/255
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
}

void loop() {

  Serial.print("tien");
  motor1.run(FORWARD);      // động cơ tiến
  motor2.run(FORWARD);      // động cơ tiến
  motor3.run(FORWARD);      // động cơ tiến  motor1.run(FORWARD);      // động cơ tiến
  motor4.run(FORWARD);
  delay(1000);

  Serial.print("lui");

  motor1.run(BACKWARD);     // động cơ lùi
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);      // động cơ tiến  motor1.run(FORWARD);      // động cơ tiến
  motor4.run(BACKWARD);

  delay(1000);

  Serial.print("tack");

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);      // động cơ tiến  motor1.run(FORWARD);      // động cơ tiến
  motor4.run(RELEASE);

  delay(1000);

}
