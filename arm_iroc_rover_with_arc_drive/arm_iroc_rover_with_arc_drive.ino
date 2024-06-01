#include<ros.h>
#include<std_msgs/Float32MultiArray.h>
#include<std_msgs/Int32MultiArray.h>

#define NUM_ENC 7

int PWMpin[8] = {9,35,18,37,13,20,11,47};   //front two, followed by back two, LRLR
int dirpin[8] = {10,48,8,36,14,19,12,21};   //first four are drive. 
int defaultdir[8] = {1,1,1,1,1,1,0,1};
ros::NodeHandle nh;

int drive_buf[8] = {0};
float enc_feed[NUM_ENC] = {0};

void messageCb(const std_msgs::Int32MultiArray & drive_inp)
{
  for(int i=0;i<8;i++)
  {
    drive_buf[i] = drive_inp.data[i];
  }
}

std_msgs::Float32MultiArray enc_msg;
std_msgs::MultiArrayDimension enc_dim;
std_msgs::MultiArrayLayout enc_layout;
ros::Publisher enc_pub("enc_drive", &enc_msg);

ros::Subscriber<std_msgs::Int32MultiArray> sub("motor_pwm", messageCb);




volatile long enc_pos[NUM_ENC]={0};
volatile bool A_set[NUM_ENC]={false};
volatile bool B_set[NUM_ENC]={false};

int encA[NUM_ENC] = {5,7,16,42,40,38,4};
int encB[NUM_ENC] = {6,15,17,2,41,39,1};

 
void callback_0(){
    int i=0;
    A_set[i]=digitalRead(encA[i]);
    B_set[i]=digitalRead(encB[i]);
    if(A_set[i]==B_set[i]){
      enc_pos[i]++;
    }
    else{
      enc_pos[i]--;
    }
}
void callback_1(){
    int i=1;
    A_set[i]=digitalRead(encA[i]);
    B_set[i]=digitalRead(encB[i]);
    if(A_set[i]==B_set[i]){
      enc_pos[i]++;
    }
    else{
      enc_pos[i]--;
    }
}
 
void callback_2(){
    int i=2;
    A_set[i]=digitalRead(encA[i]);
    B_set[i]=digitalRead(encB[i]);
    if(A_set[i]==B_set[i]){
      enc_pos[i]++;
    }
    else{
      enc_pos[i]--;
    }
}
 
void callback_3(){
    int i=3;
    A_set[i]=digitalRead(encA[i]);
    B_set[i]=digitalRead(encB[i]);
    if(A_set[i]==B_set[i]){
      enc_pos[i]++;
    }
    else{
      enc_pos[i]--;
    }
}
 
void callback_4(){
    int i=4;
    A_set[i]=digitalRead(encA[i]);
    B_set[i]=digitalRead(encB[i]);
    if(A_set[i]==B_set[i]){
      enc_pos[i]++;
    }
    else{
      enc_pos[i]--;
    }
}
 
void callback_5(){
    int i=5;
    A_set[i]=digitalRead(encA[i]);
    B_set[i]=digitalRead(encB[i]);
    if(A_set[i]==B_set[i]){
      enc_pos[i]++;
    }
    else{
      enc_pos[i]--;
    }
}
 
void callback_6(){
    int i=6;
    A_set[i]=digitalRead(encA[i]);
    B_set[i]=digitalRead(encB[i]);
    if(A_set[i]==B_set[i]){
      enc_pos[i]++;
    }
    else{
      enc_pos[i]--;
    }
}
 

 


int max(int a, int b)
{
  if(a>b) return a;
  else return b;
}
void setup(){
  //Serial.begin(115200);
  for(int i=0;i<NUM_ENC;i++)
  {
    pinMode(encA[i],INPUT_PULLUP);
    pinMode(encB[i],INPUT_PULLUP);
  }
  for(int i=0;i<8;i++)
  {
    pinMode(PWMpin[i], OUTPUT);
    pinMode(dirpin[i], OUTPUT);
  }
  attachInterrupt(digitalPinToInterrupt(encA[0]),callback_0,RISING);    
  attachInterrupt(digitalPinToInterrupt(encA[1]),callback_1,RISING);    
  attachInterrupt(digitalPinToInterrupt(encA[2]),callback_2,RISING);    
  attachInterrupt(digitalPinToInterrupt(encA[3]),callback_3,RISING);    
  attachInterrupt(digitalPinToInterrupt(encA[4]),callback_4,RISING);    
  attachInterrupt(digitalPinToInterrupt(encA[5]),callback_5,RISING);    
  attachInterrupt(digitalPinToInterrupt(encA[6]),callback_6,RISING);    


  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(enc_pub);
  nh.subscribe(sub);
  enc_msg.data_length = NUM_ENC;
  enc_msg.layout = enc_layout;
}

void loop(){
  nh.spinOnce();
  for(int i=0;i<8;i++)
  {
    if(drive_buf[i]>=0)
      {
        analogWrite(PWMpin[i],min(80,drive_buf[i]));
        digitalWrite(dirpin[i], defaultdir[i]);
      }

      
    else if(drive_buf[i]<0)
      {
        analogWrite(PWMpin[i],min(80,-drive_buf[i]));
        digitalWrite(dirpin[i], 1-defaultdir[i]);
      }
  }
  enc_feed[2] = (enc_pos[2]*360/4800*90/2374*90/60); //Shoulder
  enc_feed[5] = (enc_pos[5]*360/4800*90/2374); // Elbow
  enc_feed[3] = (enc_pos[3]*360/4800*90/2374*90/60*75/106); //Base
  enc_feed[0] = (enc_pos[0]*360/4800*90.0/187.0); //roll
  //for(int i=0;i<NUM_ENC;i++)
  //{
    //enc_feed[i] = (enc_pos[i]*360/4800*90/2374*90/60);
  //}
  enc_msg.data = enc_feed;
  enc_pub.publish(&enc_msg);
  //Serial.println(enc_pos[0]);
  delay(100);
 
}
