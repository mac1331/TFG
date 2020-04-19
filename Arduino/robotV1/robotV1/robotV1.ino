//Library import
#include <PID_v1.h>

//Parameters definition
#define t 3        //size of encoder filter register

//Motors conections declaration
int motor1A = 4;          //speed
int motor1B = 22;         //dir
int motor1C = 23;
int motor1I = 3;          //encoder input
volatile int motor1Count = 0;
volatile int dir1 = 0;
int flag1 = 0;

int motor2A = 5;          //speed
int motor2B = 24;         //dir
int motor2C = 25;
int motor2I = 2;          //encoder input
volatile int motor2Count = 0;
volatile int dir2 = 0;
int flag2 = 0;

int motor3A = 6;          //speed
int motor3B = 26;         //dir
int motor3C = 27;
int motor3I = 18;          //encoder input
volatile int motor3Count = 0;
volatile int dir3 = 0;
int flag3 = 0;

//Speed PID's definition
double Kp = 30.00, Ki = 200.00, Kd = 00.00;
double Input1, Output1, Setpoint1, SetMove1;
PID pid1(&Input1, &Output1, &Setpoint1, Kp, Ki, Kd, DIRECT);
double Input2, Output2, Setpoint2, SetMove2;
PID pid2(&Input2, &Output2, &Setpoint2, Kp, Ki, Kd, DIRECT);
double Input3, Output3, Setpoint3, SetMove3;
PID pid3(&Input3, &Output3, &Setpoint3, Kp, Ki, Kd, DIRECT);

//Rotation PID definition
double SetPointRotate;
double targetRotate;
double InputR, OutputR, SetpointR;
double KpR = 0.01, KiR = 0.00, KdR = 0.00;
PID pidR(&InputR, &OutputR, &SetpointR, KpR, KiR, KdR, DIRECT);


float motorVectA;
float motorVectB;
float motorVectC;
float VectorX = 0.1;
float VectorY = 0.1;


unsigned long previousMicros;
int motorUpdateTime = 0;
int count = 0;

void setup() {

  Serial.begin(9600);

  pinMode(motor1I, INPUT);
  pinMode(motor2I, INPUT);
  pinMode(motor3I, INPUT);

  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1C, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2C, OUTPUT);
  pinMode(motor3A, OUTPUT);
  pinMode(motor3B, OUTPUT);
  pinMode(motor3C, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(motor1I), tick1, FALLING );
  attachInterrupt(digitalPinToInterrupt(motor2I), tick2, FALLING );
  attachInterrupt(digitalPinToInterrupt(motor3I), tick3, FALLING );

  cw1();
  cw2();
  cw3();

  pid1.SetMode(AUTOMATIC);
  pid1.SetOutputLimits(-255, 255);
  Setpoint1 = 0;
  SetMove1 = 0;


  pid2.SetMode(AUTOMATIC);
  pid2.SetOutputLimits(-255, 255);
  Setpoint2 = 0;
  SetMove2 = 0;


  pid3.SetMode(AUTOMATIC);
  pid3.SetOutputLimits(-255, 255);
  Setpoint3 = 0;
  SetMove3 = 0;

  pidR.SetMode(AUTOMATIC);
  pidR.SetOutputLimits(-1.5, 1.5);


  analogWrite(motor1A, 0);
  analogWrite(motor2A, 0);
  analogWrite(motor3A, 0);
  Serial.println("READY");
}


void loop() {

  unsigned long currentMicros = micros();
  float timeElapsed = currentMicros - previousMicros;
  previousMicros = currentMicros;

  motorUpdateTime += timeElapsed;


  if (motorUpdateTime > 10000)
  {
    updateVectors();
    count++;
    float secEllpased = motorUpdateTime / 1000000.f;
    float speedFactor = (secEllpased *  64.f * 43.7f);
    motorUpdateTime -= 10000;

    OutputR = 0;

    //
    // update motor1
    //

    Setpoint1 = SetMove1 + OutputR ;

    Input1  = (float)motor1Count /   speedFactor ;
    motor1Count = 0;

    pid1.Compute();
    int currentPwm1 = Output1;

    if (currentPwm1 < 0){
      ccw1();
      analogWrite(motor1A, -currentPwm1 );
    } 
    else{
      cw1();
      analogWrite(motor1A, currentPwm1 );
    }

    //
    // update motor2
    //
    Setpoint2 = SetMove2 + OutputR ;

    Input2  = (float)motor2Count /   speedFactor ;
    motor2Count = 0;

    pid2.Compute();
    int currentPwm2 = Output2;

    if (currentPwm2 < 0){
      ccw2();
      analogWrite(motor2A, -currentPwm2 );
    }
    else{
      cw2();
      analogWrite(motor2A, currentPwm2 );
    }


    //
    // update motor3
    //
    Setpoint3 = SetMove3 + OutputR ;

    Input3  = (float)motor3Count /   speedFactor ;
    motor3Count = 0;

    pid3.Compute();
    int currentPwm3 = Output3;

    if (currentPwm3 < 0){
      ccw3();
      analogWrite(motor3A, -currentPwm3 );
    }
    else{
      cw3();
      analogWrite(motor3A, currentPwm3 );
    }
    Serial.print(currentPwm1);
    Serial.print("    ");
    Serial.print(currentPwm2);
    Serial.print("    ");
    Serial.println(currentPwm3);
  }
}


void updateVectors(){
    motorVectA = VectorX;
    float rad120 = 2*3.1415/3;
    motorVectB = VectorX*cos(rad120) - VectorY*sin(rad120);
    motorVectC = VectorX*cos(-rad120) - VectorY*sin(-rad120);
    SetMove1 = motorVectA;
    SetMove2 = motorVectB;
    SetMove3 = motorVectC;
//    Serial.print(SetMove1);
//    Serial.print("  ");
//    Serial.print(SetMove2);
//    Serial.print("  ");
//    Serial.println(SetMove3);


}

//interruptions functions
void tick1() {
  flag1 = 1;
  if (dir1 == 1)
    motor1Count += 1;
  else
    motor1Count -= 1;
}
void tick2() {
  flag2 = 1;
  if (dir2 == 1)
    motor2Count += 1;
  else
    motor2Count -= 1;
}
void tick3() {
  flag3 = 1;
  if (dir3 == 1)
    motor3Count += 1;
  else
    motor3Count -= 1;
}


//direction controller function
void ccw1() {
  digitalWrite(motor1B, LOW);
  digitalWrite(motor1C, HIGH);
  dir1 = 0;
}
void cw1() {
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor1C, LOW);
  dir1 = 1;
}

void ccw2() {
  digitalWrite(motor2B, LOW);
  digitalWrite(motor2C, HIGH);
  dir2 = 0;
}
void cw2() {
  digitalWrite(motor2B, HIGH);
  digitalWrite(motor2C, LOW);
  dir2 = 1;
}

void ccw3() {
  digitalWrite(motor3B, LOW);
  digitalWrite(motor3C, HIGH);
  dir3 = 0;
}
void cw3() {  
  digitalWrite(motor3B, HIGH);
  digitalWrite(motor3C, LOW);
  dir3 = 1;
}
