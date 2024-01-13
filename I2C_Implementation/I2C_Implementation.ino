/*
  Blink onboard LED at 0.1 second interval
*/
#include "I2C.h"
I2CSlave slave(9600,8);
void setup() {
  // initialize digital pin PB2 as an output.
  pinMode(PB2, OUTPUT); // LED connect to pin PB2
}
void loop() {
  if(slave.retChar == '1'){
      digitalWrite(PB2, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(100);               // wait for 100mS
      digitalWrite(PB2, LOW);    // turn the LED off by making the voltage LOW
      delay(100);      // wait for 100mS
  delay(200);
  }
}

  
