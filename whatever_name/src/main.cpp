#include <Arduino.h>
HardwareSerial hs = HardwareSerial(PC11,PC10);
void setup() {
    pinMode(PC13,OUTPUT_OPEN_DRAIN);
    pinMode(PB14,INPUT_ANALOG);
    pinMode(PB12,INPUT_ANALOG);
    pinMode(PB11,INPUT_ANALOG);
    pinMode(PB1,INPUT_ANALOG);
    pinMode(PA4,OUTPUT);
    digitalWrite(PA4, 1);
    hs.begin(115200);
}
void loop() {
    // digitalWrite(PC13, 0);
    // delay(100);
    // digitalWrite(PC13, 1);
    // delay(100);
    int a1=analogRead(PB14);
    int a2=analogRead(PB12);
    int a3=analogRead(PB11);
    int a4=analogRead(PB1);
    hs.printf("%d\t%d\t%d\t%d\r\n", a1,a2,a3,a4);
    analogWrite(PC13, a1);
}
