
#include<ros.h>
#include<SoftwareSerial.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher chatter("bluetooth", &str_msg);


#define bt_power 7
#define bt_key_power 8
#define indication_led 13

SoftwareSerial BT(A0, A1); // RX | TX

void setup()
{
  // set the pins to OUTPUT
  pinMode(bt_power, OUTPUT);  
  pinMode(bt_key_power, OUTPUT);
  pinMode(indication_led, OUTPUT);
  
  // set the pins to LOW
  digitalWrite(bt_power, LOW);
  digitalWrite(bt_key_power, LOW);
  digitalWrite(indication_led, LOW);
  
  
  // make sure the key has been LOW for a bit
  delay(100);
  
  // set the power pin to High
  digitalWrite(bt_power, HIGH);
  
  // small delay
  delay(500);
  
  // now set the key pin to high
  digitalWrite(bt_key_power, HIGH);
  
  // start our serial so we can send and recieve
  // information from the BT module
  Serial.begin(9600);
  // initiate the BT serial at 38400 which is the default 
  // speed at which the BT AT mode operates at
  BT.begin(9600);
  
  // self explanatory
  Serial.write("For a list of commands, visit: \n");
  Serial.write("Type AT commands  \n\n");
  
  // process complete turn on led 13
  digitalWrite(indication_led, HIGH);
  
  // Send an "AT" command to the AT (without quotes)
  // if response is OK, then we are connected
  // and ready to program the BT module

  nh.initNode();
  nh.advertise(chatter);
 }
String ATResponse;
void sendAT(String Command){

  //Serial.print("Command:" ); Serial.println(Command);
  delay(10);
  BT.println(Command);
  delay(100);
    if(BT.available()>0){
      //Serial.print("Response: ");
      ATResponse = BT.readStringUntil('OK\r\n')+Command;
      str_msg.data = ATResponse.c_str();
      chatter.publish( &str_msg );
      //Serial.println(ATResponse);
      //Serial.println(" ");
      
      //delay(1000);
    }
}

void loop()
{

  // listen for a response from the HC-05 and write it to the serial monitor
  if (BT.available())
    //Serial.write(BT.read());
    {sendAT("AT+RNAME?F4D4,88,0C5A69");//IP ADDRESS 1
    }
  
  nh.spinOnce();

  //listen for user input and send it to the HC-05
  //if (Serial.available())
   //BT.write(Serial.read());
  delay(7000);
}
