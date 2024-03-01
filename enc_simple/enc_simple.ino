#include<ros.h>
#include<std_msgs/Float32.h>

#define encA 18
#define encB 19

ros::NodeHandle nh;
std_msgs::Float32 enc_feed;
ros::Publisher enc_auto("enc_auto",&enc_feed);



volatile long enc_pos=0;
volatile bool A_set=false;
volatile bool B_set=false;



 
void callback(){
  A_set=digitalRead(encA);
  B_set=digitalRead(encB);
  if(A_set==B_set){
    enc_pos++;
  }
  else{
    enc_pos--;
  }
}




void setup(){
  pinMode(encA,INPUT_PULLUP);
  pinMode(encB,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encA),callback,RISING);
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(enc_auto);
}

void loop(){
  nh.spinOnce();
  enc_feed.data = (enc_pos*360/4800);
  enc_auto.publish(&enc_feed);
  delay(100);
 
}
