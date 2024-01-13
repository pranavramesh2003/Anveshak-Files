#include <WiFi.h>
#include<ros.h>
#include<std_msgs/Int8.h>

ros::NodeHandle nh;
std_msgs::Int8 RSS;
ros::Publisher RSS_pub("rssi",&RSS);

const char* ssid = "Galaxy M32205D";   /*Replace SSID of your network*/
const char* password = "itay3498"; /*Replace with Password of your Network*/
void initWiFi() {
  WiFi.mode(WIFI_STA);  /*Initialize ESP32 WiFi in station mode*/
  WiFi.begin(ssid, password); /*Begin WiFi connection*/
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());  /*Print local IP address of ESP32*/
}
unsigned long timer=0;

void setup() {
  Serial.begin(115200); /*Baud Rate for serial communication*/
  initWiFi();  /*Initialize WiFi*/
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(RSS_pub);
}
void loop() {
  nh.spinOnce();
  if(millis()-timer > 10)
  {
  RSS.data = WiFi.RSSI();
  RSS_pub.publish(&RSS);
  delay(50);
  timer = millis();
  }
}
