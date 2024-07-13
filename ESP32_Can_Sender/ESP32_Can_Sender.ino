#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32MultiArray.h>
#include <CAN.h>

#define TX_GPIO_NUM   19
#define RX_GPIO_NUM   18

#define freq 1000
#define resolution 8

ros::NodeHandle  nh;

int bufftosendcan[] = {0,0,0,0,0,0,0,0};
uint8_t uint8Value[8] = {0,0,0,0,0,0,0,0};

int arm_buf[5] = {0,0,0,0,0};
int arm_pwm[5] = {0,0,0,0,0};
int arm_dir[5] = {0,0,0,0,0};

volatile float enc_pos[3] = {0,0,0};
volatile int  lastEncoded[2] = {0,0};

float enc_position[7]={0,255,5,5,67,67,5};

int encA[2] = {22,32};
int encB[2] = {23,33};

int pwm[2] = {4,15};
int dir[2] = {16,2};

void rosmessageCb(const std_msgs::Int32MultiArray & arm_input)
{
  for(int i=0;i<5;i++)
  {
    arm_buf[i] = arm_input.data[i];
  }
  movearmcommands();
  pushtoCAN();
}

ros::Subscriber<std_msgs::Int32MultiArray> sub("stm_write", rosmessageCb);

std_msgs::Float32MultiArray enc_val;
std_msgs::MultiArrayDimension enc_dim;
std_msgs::MultiArrayLayout enc_layout;

ros::Publisher enc_drive("enc_drive", &enc_val);

void setup() 
{
  CANinit();
  pinmodeinit();
  
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(enc_drive);
  nh.subscribe(sub);

  enc_val.data_length = 7;
  enc_val.layout = enc_layout;
}

void loop() 
{
  nh.spinOnce();
  //update enc_position here for the encoder

  enc_val.data=enc_position;
  enc_drive.publish( &enc_val );

  delay(100);
}

void updateEncoder0()
{
  int MSB = digitalRead(encA[0]); //MSB = most significant bit
  int LSB = digitalRead(encB[0]); //LSB = least significant bit
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded[0] << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) enc_pos[0] --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) enc_pos[0] ++;
  
  lastEncoded[0] = encoded; //store this value for next time
}

void updateEncoder1()
{
  int MSB = digitalRead(encA[1]); //MSB = most significant bit
  int LSB = digitalRead(encB[1]); //LSB = least significant bit
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded[1] << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) enc_pos[1] --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) enc_pos[1] ++;
  
  lastEncoded[1] = encoded; //store this value for next time
}

void CANinit()
{
  CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void pinmodeinit()
{
  pinMode(dir[0],OUTPUT);
  pinMode(dir[1],OUTPUT);
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcAttachPin(pwm[0], 0);
  ledcAttachPin(pwm[1], 1);
  attachInterrupt(digitalPinToInterrupt(encA[0]), updateEncoder0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encA[1]), updateEncoder0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB[0]), updateEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB[1]), updateEncoder1, CHANGE);
}

void pushtoCAN()
{
  for(int count=0;count<8;count++)
  {
    uint8Value[count] = static_cast<uint8_t>(bufftosendcan[count]);
  }
  
  CAN.beginPacket(0x12);
  for(int i=0;i<8;i++)
  {
    CAN.write(uint8Value[i]);
  }
  CAN.endPacket();
}

void movearmcommands()
{
  for(int i=0;i<5;i++)
  {
    if(arm_buf[i]<=0)
    {
      arm_pwm[i] = abs(arm_buf[i]);
      arm_dir[i] = LOW;
    }
    else
    {
      arm_pwm[i] = abs(arm_buf[i]);
      arm_dir[i] = HIGH;
    }
  }
  digitalWrite(dir[0],arm_dir[0]);
  digitalWrite(dir[1],arm_dir[1]);
  ledcWrite(0,arm_pwm[0]);
  ledcWrite(1,arm_pwm[1]);

  bufftosendcan[0]=arm_pwm[2];
  bufftosendcan[1]=arm_pwm[3];
  bufftosendcan[2]=arm_pwm[4];

  bufftosendcan[3]=arm_dir[2];  
  bufftosendcan[4]=arm_dir[3];
  bufftosendcan[5]=arm_dir[4];
}
