
#include "I2C.h"
I2CMaster master(9600,8);
I2CSlave slave(9600,8);
void setup() {}
void loop() {
  master.sendData('1');
  delay(1000);
}
