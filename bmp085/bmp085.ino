#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
ros::NodeHandle nh;
 
char PRESSURESHOW[4];// initializing a character of size 4 for showing the result
char TEMPARATURESHOW[4];// initializing a character of size 4 for showing the temparature result
Adafruit_BMP085 bmp;
std_msgs::String str_msg;
ros::Publisher tp("tp",&str_msg);
 
void setup() {
  nh.initNode();
  nh.advertise(tp);
  Serial.begin(9600);
  if (!bmp.begin()){
    Serial.println("ERROR");///if there is an error in communication
    while (1) {}
  }
}
void loop(){
  nh.spinOnce();
  String PRESSUREVALUE = String(bmp.readPressure());
  // convert the reading to a char array
  PRESSUREVALUE.toCharArray(PRESSURESHOW, 4);
  //Serial.print(PRESSURESHOW);
  //Serial.println("hPa ");
   
  String TEMPARATUREVALUE = String(bmp.readTemperature());
  // convert the reading to a char array
  TEMPARATUREVALUE.toCharArray(TEMPARATURESHOW, 4);
  //Serial.print(TEMPARATURESHOW);
  //Serial.println("C ");
  str_msg.data=PRESSURESHOW;
  tp.publish(&str_msg);
  delay(500);
}
