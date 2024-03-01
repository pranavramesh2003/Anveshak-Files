#include<ros.h>
#include<std_msgs/Float32.h>
#include<std_msgs/Int32MultiArray.h>

#define encA 34
#define encB 35

int PWMpin[8] = {15, 2, 4, 18, 19, 21, 22, 23};
int dirpin[8] = {13, 12, 14, 27, 26, 25, 33, 32};

ros::NodeHandle nh;
std_msgs::Float32 enc_feed;
ros::Publisher enc_auto("enc_auto",&enc_feed);

int drive_buf[8] = {0};
void messageCb(const std_msgs::Int32MultiArray & drive_inp)
{
  for(int i=0;i<8;i++)
  {
    drive_buf[i] = drive_inp.data[i];
  }
}

ros::Subscriber<std_msgs::Int32MultiArray> sub("motor_pwm", messageCb);




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



int max(int a, int b)
{
  if(a>b) return a;
  else return b;
}
void setup(){
  pinMode(encA,INPUT_PULLUP);
  pinMode(encB,INPUT_PULLUP);
  for(int i=0;i<8;i++)
  {
    pinMode(PWMpin[i], OUTPUT);
    pinMode(dirpin[i], OUTPUT);
  }
  
  attachInterrupt(digitalPinToInterrupt(encA),callback,RISING);
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(enc_auto);
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();
  for(int i=0;i<8;i++)
  {
    if(drive_buf[i]>=0)
      {
        analogWrite(PWMpin[i],min(25,drive_buf[i]));
        digitalWrite(dirpin[i], HIGH);
      }

      
    else if(drive_buf[i]<0)
      {
        analogWrite(PWMpin[i],min(25,-drive_buf[i]));
        digitalWrite(dirpin[i], LOW);
      }
  }
  enc_feed.data = (enc_pos*360/4800);
  //enc_auto.publish(&enc_feed);
  delay(100);
 
}
