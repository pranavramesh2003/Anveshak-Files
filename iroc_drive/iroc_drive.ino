
int dirl[] = {16,2};
int pwml[] = {4,15};

int dirr[] = {13,14};
int pwmr[] = {12,27};


#include<ros.h>
#include<std_msgs/Float32MultiArray.h>
#include<std_msgs/Int32MultiArray.h>

#define NUM_ENC 3

int dirpin[4] = {14,16,13,2};   //front two, followed by back two, LRLR
int PWMpin[4] = {27,4,12,15};   //first four are drive. 
int defaultdir[4] = {0,1,0,1};
ros::NodeHandle nh;

int drive_buf[4] = {0};
float enc_feed[NUM_ENC] = {0};

void messageCb(const std_msgs::Int32MultiArray & drive_inp)
{
  for(int i=0;i<4;i++)
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

int encA[NUM_ENC]  = {2,5,38};
int encB[NUM_ENC]  = {42,6,39};
 
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
  for(int i=0;i<4;i++)
  {
    pinMode(PWMpin[i], OUTPUT);
    pinMode(dirpin[i], OUTPUT);
  }
  attachInterrupt(digitalPinToInterrupt(encA[0]),callback_0,RISING);    
  attachInterrupt(digitalPinToInterrupt(encA[1]),callback_1,RISING);    
  attachInterrupt(digitalPinToInterrupt(encA[2]),callback_2,RISING);    
 
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(enc_pub);
  nh.subscribe(sub);
  enc_msg.data_length = NUM_ENC;
  enc_msg.layout = enc_layout;
}

void loop(){
  nh.spinOnce();
  for(int i=0;i<4;i++)
  {
    if(drive_buf[i]>=0)
      {
        analogWrite(PWMpin[i],min(200,drive_buf[i]));
        digitalWrite(dirpin[i], defaultdir[i]);
      }

      
    else if(drive_buf[i]<0)
      {
        analogWrite(PWMpin[i],min(200,-drive_buf[i]));
        digitalWrite(dirpin[i], 1-defaultdir[i]);
      }
  }
  for(int i=0;i<NUM_ENC;i++)
  {
    enc_feed[i] = (enc_pos[i]*360/4800);
  }
  enc_msg.data = enc_feed;
  enc_pub.publish(&enc_msg);
  //Serial.println(enc_pos[0]);
  delay(100);
 
}
