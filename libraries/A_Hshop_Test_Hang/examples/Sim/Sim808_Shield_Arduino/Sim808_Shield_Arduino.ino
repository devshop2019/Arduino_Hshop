#include "SoftwareSerial.h"
/*
Tac gia: To ky thuat Hshop.vn
link san pham: http://hshop.vn/products/mach-simgsmgprs-gps-bluetooth-sim808

-----So do day:----

sim808(780k)					arduino (uno)
Vcc(5v, >1A)
GND
Tx						3
Rx						2
link san pham: http://hshop.vn/products/mach-simgsmgprs-gps-bluetooth-sim808


sim900, sim800L, sim800DS		arduino (uno)
Vcc(5v: sim 900,800DS, >1A)	,	4.1V: sim800L(do chua co diod)
GND
Tx						2
Rx						3
link san pham:
	http://hshop.vn/products/module-sim800l
	http://hshop.vn/products/mach-gsm-gprs-sim900a-mini-v2
	http://hshop.vn/products/mach-gsmgprs-sim900a
______________________________________________________________________________________



Luu y:
	vi chuong trinh bat dau khi vua cap dien,
	luc nay sim808 co the chua khoi dong xong (led xanh la chop cham la khoi dong xong)
	nen khoan hay cam TX, RX vao Arduino.
	khi nao led xanh la tren sim808 chop cham lai, cac ban ket noi 2 day tin hieu lai roi
	nhan Reset Arduino de bat dau lai chuong trinh.
	
Chuc cac ban thanh cong!
*/

SoftwareSerial sim808(2,3);		

String SDT="0938200500";

void setup() {
  // put your setup code here, to run once:
  sim808.begin(9600);
  // Test call
  at("AT",1000);
  at("ATD"+SDT+";",15000);
  at("ATH",1000);
  
  //test sms
  at("AT",1000);
  at("AT+CMGF=1",1000);
  at("AT+CSCS=\"GSM\"",1000);
  at("AT+CMGS=\"" + SDT+"\"",2000);
  at("Hshop test sim",1000);
  sim808.write(26);     // ctlrZ
}

void loop() {
  // put your main code here, to run repeatedly:

}
void at(String _atcm,unsigned long _dl){
  sim808.print(_atcm+"\r\n");
  delay(_dl);
}
