#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/MultiArrayLayout.h>

ros::NodeHandle nh;
std_msgs::Float32MultiArray voltdisp_msg;
std_msgs::MultiArrayDimension voltdisp_dim;
std_msgs::MultiArrayLayout voltdisp_layout;
ros::Publisher voltpub("voltpubl", &voltdisp_msg);
//float C1=0.0;
//float C2=0.0;
//float C3=0.0;
//float C4=0.0;
//float C5=0.0;
//float C6=0.0;
float battery[12]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
void setup(){
  pinMode(16,INPUT);
  pinMode(4,INPUT);
  pinMode(13,INPUT);
  pinMode(12,INPUT);
  pinMode(14,INPUT);
  pinMode(27,INPUT);
  pinMode(26,INPUT);
  pinMode(25,INPUT);
  pinMode(33,INPUT);
  pinMode(32,INPUT);
  pinMode(35,INPUT);
  pinMode(34,INPUT);
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(voltpub);
  voltdisp_msg.data_length = 12;
  voltdisp_msg.layout = voltdisp_layout;
  
  }
void loop(){
  battery[0]=analogRead(16);
  battery[1]=analogRead(4);
  battery[2]=analogRead(13);
  battery[3]=analogRead(12);
  battery[4]=analogRead(14);
  battery[5]=analogRead(27);
  battery[6]=analogRead(26);
  battery[7]=analogRead(25);
  battery[8]=analogRead(33);
  battery[9]=analogRead(32);
  battery[10]=analogRead(35);
  battery[11]=analogRead(34);
  for (int i = 0; i < 12; i++) {
    battery[i] = battery[i]*3.3/4096*11;
  }
  voltdisp_msg.data=battery;
  nh.spinOnce();
  voltpub.publish(&voltdisp_msg);
  delay(1000);
  }
