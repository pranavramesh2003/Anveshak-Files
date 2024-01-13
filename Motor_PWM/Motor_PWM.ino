#define E1 27  // Enable Pin for motor 1
#define E2 22  // Enable Pin for motor 2
#define E3 21
#define E4 18 
#define E5 19  
#define E6 20  //PWMs

#define I1 16
#define I2 12
#define I3 2  // Direction pin for motor 3
#define I4 13  // // Direction pin for motor 4
#define I5 14  // Direction pin for motor 5
#define I6 15  // Direction pin for motor 6
#define I7 11
#define I8 10
#define I9 9 //
#define I10 4 
#define I11 5
#define I12 6 //


const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup() {
    ledcSetup(0, freq, resolution);
    ledcSetup(1, freq, resolution);
    ledcSetup(2, freq, resolution);
    ledcSetup(3, freq, resolution);
    ledcSetup(4, freq, resolution);
    ledcSetup(5, freq, resolution);
    
    ledcAttachPin(E1, 0);
    ledcAttachPin(E2, 1);
    ledcAttachPin(E3, 2);
    ledcAttachPin(E4, 3);
    ledcAttachPin(E5, 4);
    ledcAttachPin(E6, 5);





 
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
 
void loop() {
 
   
  ledcWrite(0, 255);
  ledcWrite(1, 127.5);
  ledcWrite(2, 255);
  ledcWrite(3, 127.5);
  ledcWrite(4, 255);
  ledcWrite(5, 127.5);




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
