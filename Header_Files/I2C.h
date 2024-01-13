#include<Wire.h>
#include<Arduino.h>
class I2C {

  protected:
    int baud_rate;
    byte address;
  public:
    I2C(int baud_rate, byte address) ;
    void init();
    ~I2C(){}

};
class I2CMaster : public I2C {
  public:
    I2CMaster(int baud_rate, byte address);
    void sendData(char sendChar='1')  ;
     ~I2CMaster(){}
  
};

class I2CSlave: public I2C{
  public:
    I2CSlave(int baud_rate, byte address);
    static void CallBackMethod(int howmany);
    ~I2CSlave(){};
      
};
