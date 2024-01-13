#include <dht11.h>
#include<ros.h>
#define DHT11PIN 4
#include<std_msgs/String.h>
#include <string.h>

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
ros::NodeHandle  nh;


dht11 DHT11;

void  setup()
{
  Serial.begin(9600);
  nh.initNode();
  nh.advertise(chatter);
 
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);
  Serial.println(chk);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);
  //String str=String("Humidity: ")+String(DHT11.humidity)+String("\n")+String("Temperature: ")+String(DHT11.temperature)+String("\n");
  //str_msg.data=str.c_str();
  //chatter.publish( &str_msg );

  delay(2000);

}
