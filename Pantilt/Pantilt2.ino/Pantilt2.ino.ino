#include <ESP32Servo.h>
#include <ros.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle nh;

Servo servo1;  //pan motor
Servo servo2;  //tilt motor
#define servoPin1 4  //attach pan motor to pin4
#define servoPin2 16  //attach tilt motor to pin0

int ADC_Max=4096;
int init_pan=96;
int init_tilt=95;

int val1=init_pan;  //this is for pan motor so this is the value where it does not rotate
int val2=init_tilt; //this is the value for tilt motor so value is 0 initially

//feed is taken directly from the joy and val is calculated from feed (and eventually written to the servo)
float feed1=0;
float feed2=0;

void joyCallback(const sensor_msgs::Joy& msg){
  feed1=msg.axes[7];  //we will have to change these axes according to what we want to map them to
  feed2=msg.axes[6];
}

ros::Subscriber<sensor_msgs::Joy> sub("joy",&joyCallback);



void pantilt(){
  if(feed1!=0){
    servo1.attach(servoPin1);
    val1=int(feed1*10.0+init_pan);   //to keep speed between 96 and 110;
  }
  else{
    val1=init_pan;
    servo1.detach();  //better to detach continuous rotation servo when not in use
  }
  if(feed2!=0){
    servo2.attach(servoPin2);
    val1=int(feed1*10.0+init_tilt);   //to keep speed between 96 and 110;
  }
  else{
    val2=init_tilt;
    servo2.detach();  //better to detach continuous rotation servo when not in use
  }
}

void setup(){
  //Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();
  pantilt();
  servo1.write(val1);
  servo2.write(val2);
}
