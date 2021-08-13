#include<wiringpi.h>

void setup(){
    pinmode(1,OUTPUT);
    pinmode(2,INPUT)
}
void loop(){
  while (digitalRead(2) == 1) {
    digitalWrite(1,HIGH);
    analogWrite(3,0);

  }

}
