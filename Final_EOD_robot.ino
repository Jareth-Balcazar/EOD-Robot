#include<SoftwareSerial.h>
#include <Servo.h>
#define TxD 10
#define RxD 9


Servo Shoulder;
Servo Elbow;
Servo Claw;

SoftwareSerial bluetoothSerial(TxD, RxD);
char c ;
int pos1 = 90;
int pos2 = 90;
int pos3 = 90;

//Motor 1 Left

int in1 = 22;
int in2 = 23;


//Motor 2 Left

int in3 = 24;
int in4 = 25;

//Motor 1 Right

int in5 = 32;
int in6 = 33;


//Motor 2 Right

int in7 = 34;
int in8 = 35;




//Timers
unsigned long Timer_For_Arm_angle = 0;


void setup()
{
  bluetoothSerial.begin(9600);
  Serial.begin(9600);

  //Arm
  Shoulder.attach(13);
  Elbow.attach(12);
  Claw.attach(11);


  //Tank Wheels

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
}

void loop()
{

  c = bluetoothSerial.read();
  Arm();
  Tank();

  timers();
    
  if (Timer_For_Arm_angle > 20)
  {
    Serial.println("Position (angle in degree) For the Sholder is = ");
    Serial.println(pos1);

    Serial.println("Position (angle in degree) For the Elbow is = ");
    Serial.println(pos2);

    Serial.println("Position (angle in degree) For the Claw is = ");
    Serial.println(pos3);

    Timer_For_Arm_angle = 0;
  }

}

void Tank()
{

  if (c == 'F')
  {
    //Left Motors

    digitalWrite(in2, HIGH);
    digitalWrite(in4, HIGH);

    //Right Motors

    digitalWrite(in5, HIGH);
    digitalWrite(in7, HIGH);
  }

  if (c == 'B')
  {
    //Left Motors

    digitalWrite(in1, HIGH);
    digitalWrite(in3, HIGH);

    //Right Motors

    digitalWrite(in6, HIGH);
    digitalWrite(in8, HIGH);
  }



  //Spin Left
  if (c == 'L')
  {
    //Left Motors

    digitalWrite(in1, HIGH);
    digitalWrite(in3, HIGH);

    //Right Motors

    digitalWrite(in5, HIGH);
    digitalWrite(in7, HIGH);
  }


  //Spin Right

  if (c == 'R')
  {
    //Left Motors

    digitalWrite(in2, HIGH);
    digitalWrite(in4, HIGH);

    //Right Motors
   
    digitalWrite(in6, HIGH);
    digitalWrite(in8, HIGH);
  }


  if (c == '0')
  {
    //Left Motors
    digitalWrite(in1, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);

    //Right Motors
    digitalWrite(in5, LOW);
    digitalWrite(in6, LOW);
    digitalWrite(in7, LOW);
    digitalWrite(in8, LOW);
  }

}




void Arm()
{

  //Servo Shoulder
  if (c == 'U')
  {
    pos1 = pos1 + 20;

    if (pos1 >= 180)
      pos1 = 180;
    Shoulder.write(pos1);
  }

  if (c == 'D')
  {
    pos1 = pos1 - 20;
    if (pos1 <= 0)
      pos1 = 0;
    Shoulder.write(pos1);
  }

  //Servo 2 Elbow
  if (c == 'W')
  {
    pos2 = pos2 + 20;

    if (pos2 >= 180)
      pos2 = 180;
    Elbow.write(pos2);
  }

  if (c == 'E')
  {
    pos2 = pos2 - 20;
    if (pos2 <= 0)
      pos2 = 0;
    Elbow.write(pos2);
  }

  //Servo 3 Claw
  if (c == 'X')
  {
    pos3 = pos3 + 20;

    if (pos3 >= 180)
      pos3 = 180;
    Claw.write(pos3);
  }

  if (c == 'Y')
  {
    pos3 = pos3 - 20;
    if (pos3 <= 0)
      pos3 = 0;
    Claw.write(pos3);
  }
}





void timers()
{
  static unsigned long ms_runtime = 0;
  static int one_ms_timer = 0;
  int i;
  if (millis() > ms_runtime)
  {
    ms_runtime = ms_runtime + 1;
    one_ms_timer++;
  }

  else if (ms_runtime > millis())
  {
    ms_runtime = millis();
  }

  if (one_ms_timer > 99)
  {
    Timer_For_Arm_angle++;
    one_ms_timer = 0;
  }

}
