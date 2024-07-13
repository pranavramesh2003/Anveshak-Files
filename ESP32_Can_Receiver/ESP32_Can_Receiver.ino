#include <CAN.h>

#define TX_GPIO_NUM   26
#define RX_GPIO_NUM   25

#define freq 1000
#define resolution 8

uint8_t number[8] = {0};
volatile float enc_pos = 0;
volatile int lastEncoded = 0;

#define AIN1 18
#define AIN2 19
#define BIN1 17
#define BIN2 16
#define PWMA 21
#define PWMB 4
#define PWMC 2
#define DIRC 15
#define SGNL 27
int checkprint = 0;
int counter = 0;
int movemotorsok = 0;

int encA[2] = {32,33};

void setup() 
{
  Serial.begin(115200);
  CANinit();
  pinmodeinit();
}

int other[2]={0,1};
int otherother[2] ={1,0};

void loop() 
{
  if(checkprint==1)
  {
    Serial.println("received");
    for(int i=0;i<8;i++)
    {
      Serial.print(number[i]);
      Serial.print("  ");
    }
    Serial.println();
    Serial.println(counter);
    counter++;
    checkprint=0;
  }
  if(movemotorsok == 1)
  {
    ledcWrite(0,number[0]);
    ledcWrite(1,number[1]);
    ledcWrite(2,number[2]);

    digitalWrite(15,number[5]);

    digitalWrite(18,other[number[3]]);
    digitalWrite(19,otherother[number[3]]);

    digitalWrite(16,other[number[4]]);
    digitalWrite(17,otherother[number[4]]);
    movemotorsok = 0;
  }
}

void onReceive(int packetSize)
{
  int f=0;
  while (CAN.available()) 
  {
    char k = (char) CAN.read();
    number[f] = static_cast<uint8_t>(k);
    f=f+1;      
  }
  checkprint = 1;
  movemotorsok = 1;
}

void CANinit()
{
  Serial.println ("CAN Receiver");

  CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  CAN.onReceive(onReceive);
}

void pinmodeinit()
{
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(DIRC,OUTPUT);
  pinMode(SGNL,INPUT);

  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcSetup(2, freq, resolution);
  ledcAttachPin(PWMA, 0);
  ledcAttachPin(PWMB, 1);
  ledcAttachPin(PWMC, 2);

  attachInterrupt(digitalPinToInterrupt(encA[0]), updateEncoder0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encA[1]), updateEncoder0, CHANGE);
  
}

void updateEncoder0()
{
  int MSB = digitalRead(encA[0]); //MSB = most significant bit
  int LSB = digitalRead(encA[1]); //LSB = least significant bit
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) enc_pos --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) enc_pos ++;
  
  lastEncoded = encoded; //store this value for next time
}
