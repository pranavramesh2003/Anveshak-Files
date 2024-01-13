// the number of the LED pin
const int ledPin0 = 16;  // 16 corresponds to GPIO16
const int ledPin1 = 17; 
const int ledPin2 = 18; 
const int ledPin3 = 21; 
const int ledPin4 = 5; 
const int ledPin5 = 19; 

#define I1 2
#define I2 4
#define I3 23 // Direction pin for motor 3
#define I4 12  // // Direction pin for motor 4
#define I5 13  // Direction pin for motor 5
#define I6 14  // Direction pin for motor 6
#define I7 25
#define I8 26
#define I9 27 //
#define I10 32 
#define I11 33
#define I12 22 //



// setting PWM properties
const int freq = 5000;
const int ledChannel0 = 0;
const int ledChannel1 = 1;
const int ledChannel2 = 2;
const int ledChannel3 = 3;
const int ledChannel4 = 4;
const int ledChannel5 = 5;


const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel0, freq, resolution);
    ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcSetup(ledChannel4, freq, resolution);
    ledcSetup(ledChannel5, freq, resolution);


  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin0, ledChannel0);
    ledcAttachPin(ledPin1, ledChannel1);
  ledcAttachPin(ledPin2, ledChannel2);
  ledcAttachPin(ledPin3, ledChannel3);
  ledcAttachPin(ledPin4, ledChannel4);
    ledcAttachPin(ledPin5, ledChannel5);



    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);
    pinMode(I5, OUTPUT);
    pinMode(I6, OUTPUT);
    pinMode(I7, OUTPUT);
    pinMode(I8, OUTPUT);
    pinMode(I9, OUTPUT);
    pinMode(I10, OUTPUT);
    pinMode(I11, OUTPUT);
    pinMode(I12, OUTPUT);

}
 
void loop(){
  
    ledcWrite(ledChannel0, 125);
    ledcWrite(ledChannel1, 125);
    ledcWrite(ledChannel2, 125);
    ledcWrite(ledChannel3, 125);
    ledcWrite(ledChannel4, 125);
    ledcWrite(ledChannel5, 125);

     digitalWrite(I1, LOW);
    digitalWrite(I2, LOW);
    digitalWrite(I3, LOW);
    digitalWrite(I4, LOW);
    digitalWrite(I5, LOW);
    digitalWrite(I6, LOW);
    digitalWrite(I7, HIGH);
    digitalWrite(I8, HIGH);
    digitalWrite(I9, HIGH);
    digitalWrite(I10, HIGH);
    digitalWrite(I11, HIGH);
    digitalWrite(I12, HIGH);


  
}
