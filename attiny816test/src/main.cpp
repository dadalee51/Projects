#include <Arduino.h>
#include <Wire.h>

#define TF_OFF
#define ACC_OFF

#ifdef ACC_ON
  #include "SparkFun_LIS2DH12.h"
  SPARKFUN_LIS2DH12 accel;
#endif
#ifdef TF_ON
  #include <VL53L0X.h>
  VL53L0X sensor; //0x29
#endif
#define FOR(A,I) for(int A=0;A<I;A++)
#define PA0 17 //UPDI
#define PA1 14 //MOSI
#define PA2 15 //MISO
#define PA3 16 //CLK
#define PA4 0  //SS
#define PA5 1  
#define PA6 2  //DAC
#define PA7 3

#define PB0 9 //SCL
#define PB1 8 //SDA
#define PB2 7 //TXD
#define PB3 6 //RXD
#define PB4 5
#define PB5 4

#define PC0 10
#define PC1 11
#define PC2 12
#define PC3 13

int LDR1 = PA6;
int LDR2 = PA7;

//pwm pins: pb3,4,5, pa3,4,5, pc0/1 : please choose correct settings.
int LEDR = PA3; //dryBot LEDR 1 = off
int LEDW = PA2; //dryBot LEDW 0 = off
//#define MY_ADDRESS 0x17 // address for this slave device
//#define SLAVE_ADDRESS 0x12
int ldr1=0;
int ldr2=0;
#ifdef TF_ON
  int head=0;
#endif
#ifdef ACC_ON
  float z_acc=0.0;
#endif
void setup() {
  pinMode(LEDR,OUTPUT);
  pinMode(LEDW,OUTPUT);
  pinMode(LDR1,INPUT);
  pinMode(LDR2,INPUT);
  delay(500);//current stable time.

  //Wire.begin(MY_ADDRESS); // join i2c bus as slave
  Wire.begin(); // join i2c bus as master
  //Wire.onReceive(receiveData); // callback for receiving data
  //Wire.onRequest(sendData); // callback for sending data
  digitalWrite(LEDR, 1); //off
  digitalWrite(LEDW, 0); // 1 on for light
  #ifdef TF_ON
  sensor.setTimeout(500);
  if (!sensor.init()) {
	FOR(3){
	signalling(30);
	delay(100);
	}
  }
  sensor.startContinuous();
  #endif
  #ifdef ACC_ON
  if (!accel.begin()) {
	signalling(30);
	delay(100);
  }
  #endif
}

//void sendData() { //not used.
  // Send data over I2C
//  Wire.write((byte*)&ldr1, 2);
//  Wire.write((byte*)&ldr2, 2);
//  Wire.write((byte*)&head, 2);
  //Wire.write((byte*)&z_acceleration, 4);
//}

void loop() {  
  ldr1 = analogRead(LDR1);
  ldr2 = analogRead(LDR2);
  #ifdef TF_ON
  head=sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred()) FOR(3)signalling(50);
  if(head > 100){
	digitalWrite(LEDW,1); //turn on
  }else{
	digitalWrite(LEDW,0);
  }
  #endif
  #ifdef ACC_ON
  z_acc = accel.getZ();
  if (z_acc < 0){
	digitalWrite(LEDW, 1); //on
  }else{
	digitalWrite(LEDW, 0);//Wled off
  }
  #endif
  delay(100);
 
}

void signalling(int delaytime) {
  // Blink the LED as a signal
  for (int i = 0; i < 3; i++) {
	digitalWrite(LEDR, HIGH);
	delay(delaytime);
	digitalWrite(LEDR, LOW);
	delay(delaytime);
  }
}
