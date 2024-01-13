/*
  Reading Position, Velocity and Time (PVT) via UBX binary commands
  By: Paul Clark
  SparkFun Electronics
  Date: December 21st, 2022
  License: MIT. Please see LICENSE.md for more information.

  This example shows how to query a u-blox module for its position, velocity and time (PVT) data.
  We also turn off the NMEA output on the I2C port. This decreases the amount of I2C traffic dramatically.

  Note: Lat/Lon are large numbers because they are * 10^7. To convert lat/lon
  to something google maps understands simply divide the numbers by 10,000,000.

  Feel like supporting open source hardware?
  Buy a board from SparkFun!
  SparkFun GPS-RTK2 - ZED-F9P (GPS-15136)    https://www.sparkfun.com/products/15136
  SparkFun GPS-RTK-SMA - ZED-F9P (GPS-16481) https://www.sparkfun.com/products/16481
  SparkFun MAX-M10S Breakout (GPS-18037)     https://www.sparkfun.com/products/18037
  SparkFun ZED-F9K Breakout (GPS-18719)      https://www.sparkfun.com/products/18719
  SparkFun ZED-F9R Breakout (GPS-16344)      https://www.sparkfun.com/products/16344

  Hardware Connections:
  Plug a Qwiic cable into the GNSS and your microcontroller board
  If you don't have a platform with a Qwiic connection use the SparkFun Qwiic Breadboard Jumper (https://www.sparkfun.com/products/14425)
  Open the serial monitor at 115200 baud to see the output
*/
#include<ros.h>
#include<navigation/gps_data.h>
#include<std_msgs/Int8.h>
#include <Wire.h> //Needed for I2C to GNSS

#define encA 18
#define encB 19

#include <SparkFun_u-blox_GNSS_v3.h> //http://librarymanager/All#SparkFun_u-blox_GNSS_v3

SFE_UBLOX_GNSS myGNSS; // SFE_UBLOX_GNSS uses I2C. For Serial or SPI, see Example2 and Example3
ros::NodeHandle nh;
navigation::gps_data gps_pos;
ros::Publisher gps("gps_coordinates",&gps_pos);
std_msgs::Int8 enc_feed;
ros::Publisher enc_auto("enc_auto",&enc_feed);
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
unsigned long timer=0;

void setup()
{
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(gps);
  Wire.begin(); // Start I2C
  pinMode(encA,INPUT_PULLUP);
  pinMode(encB,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encA),callback,RISING);
  nh.advertise(enc_auto);
  //myGNSS.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  while (myGNSS.begin() == false) //Connect to the u-blox module using Wire port
  {
    delay (1000);
  }

  myGNSS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  
  //myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); //Optional: save (only) the communications port settings to flash and BBR
}

void loop()
{
  // Request (poll) the position, velocity and time (PVT) information.
  // The module only responds when a new position is available. Default is once per second.
  // getPVT() returns true when new data is received.
  if (millis()-timer > 100 && myGNSS.getPVT() == true)
  {
    int32_t latitude = myGNSS.getLatitude();
    
    int32_t longitude = myGNSS.getLongitude();
    double latitude_deg=static_cast<double>(latitude)/10000000.0;
    double longitude_deg=static_cast<double>(longitude)/10000000.0;
    gps_pos.latitude=latitude_deg;
    gps_pos.longitude=longitude_deg; 
    timer = millis();
   
  }
  gps.publish(&gps_pos);
  enc_feed.data = (enc_pos/100*180/25000);
  enc_auto.publish(&enc_feed);
  nh.spinOnce();
}
