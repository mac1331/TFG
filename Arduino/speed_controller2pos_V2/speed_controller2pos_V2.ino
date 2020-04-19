//Library import
#include <PID_v1.h>

//Parameters definition
#define t 2 //2        //size of encoder filter register

//encoder filter register variables declaration
float acum = 0;
float reg[t];

//speed calc variables
float microsec = 0;
float antmicrosec = 0;
float spe = 0;
float antspe = 0;
float filtratedspe = 0;

//PID's declaration
double Setpointv, Inputv, Outputv;
float vKp = 2; //2
float vKi = 0.7; //0.55
float vKd = 0.000001;
PID vPID(&Inputv, &Outputv, &Setpointv, vKp, vKi, vKd, DIRECT); //???2.3, 0.5, 0.01
double Setpointp, Inputp, Outputp;
float pKp = 2.5; //??
float pKi = 0.3; //??
float pKd = 0.000001;
float spKp = 2; //??
float spKi = 0.000001; //??
float spKd = 0.000001;
PID pPID(&Inputp, &Outputp, &Setpointp, pKp, pKi, pKd, DIRECT); 


//Motors conections declaration
int motor1A = 4;          //speed
int motor1B = 22;         //dir
int motor1C = 23;
int motor1I = 3;          //encoder input


//other variables
int dir;
int flag = 1;             //interruption flag
double rev = 0;           //rev counter



void setup() {
  //motor pins mode declaration
  pinMode(motor1I, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1C, OUTPUT);

  //register generation with all 0
  for (int i = 0; i < t; i++) {
    reg[i] = 0;
  }

  //interruption definition
  attachInterrupt(digitalPinToInterrupt(motor1I), tick, FALLING );

  //PID's configuration
  vPID.SetOutputLimits(-255, 255);     //V PID
  vPID.SetSampleTime(1);
  Inputv = filtratedspe;
  Setpointv = Outputp;
  Outputv = 0;
  vPID.SetMode(AUTOMATIC);
  
  pPID.SetOutputLimits(-255, 255);     //P PID
  pPID.SetSampleTime(1);
  Inputp = rev;
  Setpointp = 0;
  Outputp = 0;
  pPID.SetMode(AUTOMATIC);

  //serial comunication initialize
  Serial.begin(9600);

  //define a starting rotation direction
  ccw();

}

void loop() {
  //if the flag is activated, calculate de real speed and filter it to reduce the error
  if (flag) {
    flag = 0;
    antspe = spe;
    spe = pow(((microsec - antmicrosec) * 20 / 1000000), (-1)) * 60;          //speed calculation
    if (spe >= 1000) {                                                        //filtering with the register
      spe = antspe;
    }
    for (int i = 0; i < t - 1; i++) {
      reg[i] = reg[i + 1];
    }
    acum = 0;
    reg[t - 1] = spe;
    for (int i = 0; i < t - 1; i++) {
      acum += reg[i];
    }
    filtratedspe = acum / t;                                                  //register mean to get de filtered speed
  }
  else {
    if (micros() - antmicrosec > 200000) {
      spe = 0;
      for (int i = 0; i < t - 1; i++) {
        reg[i] = reg[i + 1];
      }
      acum = 0;
      reg[t - 1] = spe;
      for (int i = 0; i < t - 1; i++) {
        acum += reg[i];
      }
      filtratedspe = acum / t;
    }
  }

  Serial.print(map(analogRead(A0), 0, 1023, 0, 255));
  Serial.print(",");
  Serial.print(rev);
  Serial.print(",");
  Serial.print(Outputv);
  Serial.print(",");
  Serial.println(Outputp);
  Setpointp = map(analogRead(A0), 0, 1023, 0, 255);
  Inputp = rev;
  pPID.Compute();
  Inputv = filtratedspe;
  Setpointv = Outputp;
  vPID.Compute();
  
//  if(abs(Outputv)<40){
//    pPID.SetTunings(spKp, spKi, spKd);
//    if(abs(Outputv)<10){
//      Outputv = 0;  
//    }
//    else{
//      Outputv = 40; 
//    }
//  }
//  else{
//    pPID.SetTunings(pKp, pKi, pKd);
//  }
  
  if(Outputv >= 0){
    cw();
  }
  else{
    ccw();  
  }
  analogWrite(motor1A, abs(Outputv));
  
}


//interrution function
void tick() {
  flag = 1;
  antmicrosec = microsec;
  microsec = micros();
  if (dir == 1)
    rev += 1;
  else
    rev -= 1;
}

//direction controller function
void ccw()
{
  digitalWrite(motor1B, LOW);
  digitalWrite(motor1C, HIGH);
  dir = 0;
}

//direction controller function
void cw()
{
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor1C, LOW);
  dir = 1;
}
