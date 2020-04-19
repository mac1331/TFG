#include <PID_v1.h>
#define t 20
double Setpointv, Inputv, Outputv;
double Setpointp, Inputp, Outputp;

PID vPID(&Inputv, &Outputv, &Setpointv, 1, 0.00003, 0.0001, DIRECT); //2.3, 0.5, 0.01
PID pPID(&Inputp, &Outputp, &Setpointp, 0.8, 0.3, 0.01, DIRECT);
float acum = 0;
float vel = 0;
float registre[t];
float mil = 0;
float antmil = 0;
int flag = 1;
int sentit;
double rev;
int motor1A = 4;
int motor1B = 22;
int motor1C = 23;
int motor1I = 3;
int incoming;
int stoped = 1;


void setup() {
  vPID.SetSampleTime(0.3);
  pPID.SetSampleTime(0.3);
  pinMode(motor1I, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1C, OUTPUT);
  for (int i = 0; i < t; i++) {
    registre[i] = 0;
  }
  vPID.SetOutputLimits(-155, 155);
  pPID.SetOutputLimits(-255, 255);

  Inputv = vel;
  Setpointv = 0;
  Outputv = 0;
  Setpointp = 10;
  vPID.SetMode(AUTOMATIC);
  pPID.SetMode(AUTOMATIC);
  attachInterrupt(digitalPinToInterrupt(motor1I), tick, FALLING );
  Serial.begin(9600);
  ccw();
}

void loop() {
  if (flag) {
    flag = 0;
    vel = pow(((micros() - antmil) * 20 / 1000000), (-1)) * 60;
    for (int i = 0; i < t - 1; i++) {
      registre[i] = registre[i + 1];
    }
    acum = 0;
    registre[t - 1] = vel;
    for (int i = 0; i < t - 1; i++) {
      acum += registre[i];
    }
    Inputv = acum / t;
  }
  Serial.print(Outputv);
  Serial.print(",");
  Serial.print(Outputp);
  Serial.print(",");  
  Serial.print(Setpointp);
  Serial.print(",");
  Serial.println(rev);

  Inputp = rev;
  vPID.Compute();
  pPID.Compute();
  analogWrite(motor1A, abs(Outputv));
  if (abs(Outputv) < 20){
    stoped = 1;
  }   
  if (abs(Outputv) > 60 and stoped == 1){
    analogWrite(motor1A, 255);
    delay(10);
    stoped = 0;
  }    
  
  analogWrite(motor1A, abs(Outputv));

  Setpointv = Outputp;
  if (Outputv > 0)
    cw();
  else if (Outputv < 0)
    ccw();

}



void tick() {
  flag = 1;
      antmil = mil;
    mil = micros();
  if (sentit == 1)
    rev += 1;
  else
    rev -= 1;
}




void ccw()
{
  digitalWrite(motor1B, LOW);
  digitalWrite(motor1C, HIGH);
  sentit = 0;
}

void cw()
{
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor1C, LOW);
  sentit = 1;
}
