Science
*************
Never connect any sensor to input only pins, because they most likely will need the ESP to send Acknowledge messages.
We had to play with traces and jumpers on the PCB, because this happened with the DHT and the DS18B20. The DHT would throw an error message on the serial monitor that said GPIO error or something, but the DS18B20 would just give its wrong default value of -127.

The DS18B20 also has to have a pullup resistor, otherwise it will just give its wrong default value of -127.

DHT gives proper values without ROS, but when we just upload the ROS code, 'nan' values start coming (happens only with the DHT and not any other sensor).

If BMP does not begin, it will not let rosserial come, because it will constantly reset the ESP. So, it is adviced to have an ESP having code that does not include the BMP sensor (as a runner).

The Johnson motor worked with ROS, but did not work in the code having 'sensors+motors' with ROS. When the button (GUI) to move the Johnson motor was pressed, it would cause the rosserial to cut and the only way to get back rosserial was to re-upload the ESP code. So, I made a code having a button to fetch sensor data only when needed, mainly intended to make the Johnson motor work till they wanted the sensor data. This worked, but if sensor data was obtained and then the Johnson motor button was pressed, the same problem (rosserial getting cut) occured.
This however, randomly got solved (Johnson motor would work even after sensor data was obtained). This was mostly because we removed the DS18B20 from pin 35 (INPUT only pin) and attached it to pin 13 (GPIO) (we had already changed INPUT pin 34 to GPIO 21), maybe due to issues arising with the INPUT only pin when it was asked to send an ACK.

-Amogh
