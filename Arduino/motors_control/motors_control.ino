#include <PID_v1.h>
#define t 20
double Setpointv, Inputv, Outputv;

PID vPID(&Inputv, &Outputv, &Setpointv, 3, 0.00003, 0.0001, DIRECT); //2.3, 0.5, 0.01
float acum = 0;
float vel = 0;
float registre[t];
float mil = 0;
float antmil = 0;
int flag = 1;
int sentit;
double rev;
double millisanterior = 0;

int motor1A = 4;
int motor1B = 22;
int motor1C = 23;
int motor1I = 3;

int stoped = 1;

void setup() {
  vPID.SetSampleTime(0.3);
  pinMode(motor1I, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1C, OUTPUT);
  for (int i = 0; i < t; i++) {
    registre[i] = 0;
  }
  vPID.SetOutputLimits(-255, 255);
  Inputv = vel;
  Setpointv = 0;
  Outputv = 0;
  vPID.SetMode(AUTOMATIC);
  attachInterrupt(digitalPinToInterrupt(motor1I), tick, FALLING );
  Serial.begin(9600);
  ccw();
}

void loop() {
  if (flag) {
    flag = 0;
    antmil = mil;
    mil = micros();
    vel = pow(((micros() - antmil) * 20 / 1000000), (-1)) * 60;
    for (int i = 0; i < t - 1; i++) {
      registre[i] = registre[i + 1];
    }
    acum = 0;
    registre[t - 1] = vel*3;
    for (int i = 0; i < t - 1; i++) {
      acum += registre[i];
    }
    Inputv = acum / t;
  }

  Serial.print(Outputv);
  Serial.print(",");
  Serial.print(Inputv);
  Serial.print(",");
  Serial.print(Setpointv);
  Serial.print(",");
  Serial.println(rev);

  vPID.Compute();
  analogWrite(motor1A, abs(Outputv));
  if (abs(Outputv) < 20) {
    stoped = 1;
  }
  if (abs(Outputv) > 60 and stoped == 1) {
    analogWrite(motor1A, 255);
    delay(10);
    stoped = 0;
  }
  
  if (Outputv > 0)
    cw();
  else if (Outputv < 0)
    ccw();
  if(millis()-millisanterior >= 200 and Setpointv < 255){
    millisanterior = millis();
    Setpointv += 1;
  }
}

void tick() {
  flag = 1;
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
