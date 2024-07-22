#include <Arduino.h>
void setup()
{
    pinMode(PB_15, OUTPUT);
    pinMode(PB_14, OUTPUT);
    pinMode(PB_13, OUTPUT);
    digitalWrite(PB_15, 1);
    digitalWrite(PB_14, 1);
    digitalWrite(PB_13, 1);
}
int b = 255;
int g = 255;
int r = 255;
void loop()
{
    b--;
    if(b<0)b=255;
    analogWrite(PB_15, b); // B
    analogWrite(PB_14, 255); // G
    analogWrite(PB_13, 255); // R
    delay(5);
}
