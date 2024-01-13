#include"I2C.h"

I2C::I2C(int baud_rate, byte address) {
      this->baud_rate = baud_rate;
      this->address= address;
      init();
    };

void I2C::init() {
      Wire.begin(address);
    };

I2CMaster::I2CMaster(int baud_rate=9600, byte address=8):I2C(baud_rate, address){};
void I2CMaster::sendData(char sendChar) {
       Wire.beginTransmission(address);
       Serial.println("Character Sent :");
       Serial.println(sendChar);
       Wire.write(sendChar);
       Wire.endTransmission();
      };
int retChar;
I2CSlave::I2CSlave(int baud_rate=9600, byte address=8):I2C(baud_rate, address){
    Wire.onReceive(CallBackMethod); // register event
}
static void I2CSlave::CallBackMethod(int arg2) {
    while (1 <= Wire.available()) { // loop through all including the last
    retChar = Wire.read();// receive byte as a characte
       }
};
 
