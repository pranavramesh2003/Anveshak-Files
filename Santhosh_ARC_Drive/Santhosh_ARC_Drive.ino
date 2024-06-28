#include<ros.h>
#include<std_msgs/Float32MultiArray.h>
#include<std_msgs/Int32MultiArray.h>

#define NUM_ENC 7

int PWMpin[8] = {9,35,18,37,13,20,11,47};   //front two, followed by back two, LRLR
int dirpin[8] = {10,48,8,36,14,19,12,21};   //first four are drive. 
int defaultdir[8] = {1,1,0,0,0,0,1,1};  // mayhem, needs calib and documentaiton
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
ros::Publisher enc_pub("enc_auto", &enc_msg);

ros::Subscriber<std_msgs::Int32MultiArray> sub("motor_pwm", messageCb);

volatile long enc_pos[7]={0};
volatile int lastEncoded[7] ={0};

int encA[4] = {5,16,2,41};
int encB[4] = {6,17,42,40};

 
void updateEncoder0()
{
  int MSB = digitalRead(encA[0]); //MSB = most significant bit
  int LSB = digitalRead(encB[0]); //LSB = least significant bit
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded[0] << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) enc_pos[0] ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) enc_pos[0] --;
  
  lastEncoded[0] = encoded; //store this value for next time
}

void updateEncoder1()
{
  int MSB = digitalRead(encA[1]); //MSB = most significant bit
  int LSB = digitalRead(encB[1]); //LSB = least significant bit
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded[2] << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) enc_pos[2] --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) enc_pos[2] ++;
  
  lastEncoded[2] = encoded; //store this value for next time
}

void updateEncoder2()
{
  int MSB = digitalRead(encA[2]); //MSB = most significant bit
  int LSB = digitalRead(encB[2]); //LSB = least significant bit
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded[3] << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) enc_pos[3] ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) enc_pos[3] --;
  
  lastEncoded[3] = encoded; //store this value for next time
}

void updateEncoder3()
{
  int MSB = digitalRead(encA[3]); //MSB = most significant bit
  int LSB = digitalRead(encB[3]); //LSB = least significant bit
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded[5] << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) enc_pos[5] --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) enc_pos[5] ++;
  
  lastEncoded[5] = encoded; //store this value for next time
}



int max(int a, int b)
{
  if(a>b) return a;
  else return b;
}
void setup(){
  //Serial.begin(115200);
  for(int i=0;i<4;i++)
  {
    pinMode(encA[i],INPUT_PULLUP);
    pinMode(encB[i],INPUT_PULLUP);
  }
  for(int i=0;i<8;i++)
  {
    pinMode(PWMpin[i], OUTPUT);
    pinMode(dirpin[i], OUTPUT);
  }
  attachInterrupt(digitalPinToInterrupt(encA[0]),updateEncoder0,CHANGE);    
  attachInterrupt(digitalPinToInterrupt(encA[1]),updateEncoder1,CHANGE);    
  attachInterrupt(digitalPinToInterrupt(encA[2]),updateEncoder2,CHANGE);    
  attachInterrupt(digitalPinToInterrupt(encA[3]),updateEncoder3,CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB[0]),updateEncoder0,CHANGE);    
  attachInterrupt(digitalPinToInterrupt(encB[1]),updateEncoder1,CHANGE);    
  attachInterrupt(digitalPinToInterrupt(encB[2]),updateEncoder2,CHANGE);    
  attachInterrupt(digitalPinToInterrupt(encB[3]),updateEncoder3,CHANGE);

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
        analogWrite(PWMpin[i],min(255,drive_buf[i]));
        digitalWrite(dirpin[i], defaultdir[i]);
      }

      
    else if(drive_buf[i]<0)
      {
        analogWrite(PWMpin[i],min(255,-drive_buf[i]));
        digitalWrite(dirpin[i], 1-defaultdir[i]);
      }
  }
  for(int i=4;i<8;i++)
  {
    if(drive_buf[i]>=0)
      {
        analogWrite(PWMpin[i],min(255,drive_buf[i]));
        digitalWrite(dirpin[i], defaultdir[i]);
      }

      
    else if(drive_buf[i]<0)
      {
        analogWrite(PWMpin[i],min(255,-drive_buf[i]));
        digitalWrite(dirpin[i], 1-defaultdir[i]);
      }
  }
  for(int i=0;i<NUM_ENC;i++)
  {
    enc_feed[i] = (enc_pos[i]*360/560000);
  }
  enc_msg.data = enc_feed;
  enc_pub.publish(&enc_msg);
  //Serial.println(enc_pos[0]);
  delay(100);
 
}
