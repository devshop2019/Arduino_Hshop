/*

            ***  5V  ***
                9600

GND Black / Đen: chân nguồn 0VDC Mass
VCC Red / Đỏ: chân nguồn 3~5VDC VCC
RXD Yellow / Vàng: chân nhận tín hiệu UART
TXD White / Trắng: chân truyền tín hiệu UART

*/
#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
char Res;
char usart_rxcmd_flag;
char USART_RX_BUF[16];
char usart_rxcmd_cnt;
char usart_rx_timeout;

unsigned char dcalib_flag=0;
unsigned short lenth_buf[10];
unsigned short lenth_cnt=0;
unsigned short lenth,avelenth;
unsigned char calib_cnt;
unsigned char ok_flag;
unsigned char fail_flag;

int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}
void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}

void CalAveLenth(void)
{  
  unsigned char i;
  unsigned short sum,max,min;
  
  max=0;
  min=9999;
  sum=0;
  for(i=0;i<10;i++)
  {
    if(lenth_buf[i]>max)
      max=lenth_buf[i];
    else if(lenth_buf[i]<min)
      min=lenth_buf[i];
    
    sum+=lenth_buf[i];
  };
  if((max-min)>10)
  {
    if(lenth_cnt>0)
      avelenth=lenth_buf[lenth_cnt-1] ;
    else
      avelenth=lenth_buf[9] ;
  }
  else
    avelenth=(sum-max-min)/8 ;
}
void CalDisplay_Length(void)
{
  unsigned char i,j;
  unsigned short tmp;
  unsigned char dispbuf[18]={"L=               "};
  
  for(i=0;i<16;i++)
  {
    dispbuf[i+2]=USART_RX_BUF[i];
    if(USART_RX_BUF[i]=='m')
    {
      if(USART_RX_BUF[i+1]=='m')
      {
        dispbuf[i+3]=USART_RX_BUF[i];
        dispbuf[i+4]=0;
        dispbuf[i+5]=0;
        dispbuf[i+6]=0;
        if(i>0)
          tmp=USART_RX_BUF[i-1]-0x30;
        if(i>1)
          tmp+=(USART_RX_BUF[i-2]-0x30)*10;
        if(i>2)
          tmp+=(USART_RX_BUF[i-3]-0x30)*100;
        if(i>3)
          tmp+=(USART_RX_BUF[i-4]-0x30)*1000;
        lenth=tmp;
        lenth_buf[lenth_cnt]=tmp;
        lenth_cnt++;
        if(lenth_cnt>=10)
          lenth_cnt=0;
        break;
      }
    }
  } 
  if(dcalib_flag==0)
  {
    CalAveLenth();
    if(avelenth>=1000)
    {
      dispbuf[2]=avelenth/1000+0x30;
      dispbuf[3]=avelenth/100%10+0x30;
      dispbuf[4]=avelenth/10%10+0x30;
      dispbuf[5]=avelenth%10+0x30;
      dispbuf[6]='m';
      dispbuf[7]='m';
    }
    else if(avelenth>=100)
    {
      dispbuf[2]=avelenth/100%10+0x30;
      dispbuf[3]=avelenth/10%10+0x30;
      dispbuf[4]=avelenth%10+0x30;
      dispbuf[5]='m';
      dispbuf[6]='m';
      dispbuf[7]=0x00;
    }
    else if(avelenth>=10)
    {
      dispbuf[2]=avelenth/10%10+0x30;
      dispbuf[3]=avelenth%10+0x30;
      dispbuf[4]='m';
      dispbuf[5]='m';
      dispbuf[6]=0x00;
      dispbuf[7]=0x00;
    }
    else 
    {
      dispbuf[2]=avelenth%10+0x30;
      dispbuf[3]='m';
      dispbuf[4]='m';
      dispbuf[5]=0x00;
      dispbuf[6]=0x00;
      dispbuf[7]=0x00;
    }
    printf("uart=%s\n",dispbuf);
    //delay(300);
  } 
  for(i=0;i<16;i++)
  {
    USART_RX_BUF[i]=0;
    dispbuf[i+2]=0;
  }
}
ISR(TIMER1_COMPA_vect)
{
   digitalWrite(7, !digitalRead(7)); 
  if(usart_rx_timeout>0)
  {
    usart_rx_timeout--;
    if(usart_rx_timeout==0)
    {
      if((USART_RX_BUF[0]=='o')&&(USART_RX_BUF[0]=='k'))
      {
        ok_flag=1;  
        fail_flag=0;   
        digitalWrite(6,LOW);
      }
      else if((USART_RX_BUF[0]=='f')&&(USART_RX_BUF[0]=='a')&&(USART_RX_BUF[0]=='i')&&(USART_RX_BUF[0]=='l'))
      {
        ok_flag=0;
        fail_flag=1;
        digitalWrite(6,LOW);
      }
      else
      {
        usart_rxcmd_flag=1;
        usart_rxcmd_cnt=0;
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  Serial.begin(9600,SERIAL_8N1); 
  printf_begin();
  printf("start\n\r");
  // 初始化timer1
  cli();          // 进制全局中断
  TCCR1A = 0;     //设置TCCR1A全为0
  TCCR1B = 0;     // [size=1em]设置TCCR1B全为0

  //设置比较的值得大小
  OCR1A = 15;
  // 开启CTC模式
  TCCR1B |= (1 << WGM12);
  // 设置 CS10和CS12位
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // 允许比较中断
  TIMSK1 |= (1 << OCIE1A);
  sei();          // 允许全局中断
}
void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0){
    Res =Serial.read();
    if(usart_rxcmd_flag==0)
    {
      USART_RX_BUF[usart_rxcmd_cnt]=Res;
      usart_rx_timeout=5;
      usart_rxcmd_cnt++;
      if(usart_rxcmd_cnt>(16-1))
        usart_rxcmd_cnt=0;
    }        
  }   
  if(usart_rxcmd_flag==1)
  { 
    CalDisplay_Length();
    usart_rxcmd_flag=0;
  }   
}
