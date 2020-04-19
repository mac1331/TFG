#include <PID_v1.h>
#define t 20
double Setpoint, Input, Output;

PID myPID(&Input, &Output, &Setpoint, 2, 0.00001, 0.1, DIRECT);
float acum = 0;
float vel = 0;
float registre[t];
float mil = 0;
float antmil = 0;
int flag = 1;
int sentit;
double rev;

void setup() {
  pinMode(4, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(51, INPUT);
  pinMode(A0, INPUT);
  for (int i = 0; i < t; i++) {
    registre[i] = 0;
  }
  myPID.SetOutputLimits(50, 255);

  Input = vel;
  Setpoint = 150;
  Output = 100;
  myPID.SetMode(AUTOMATIC);
  attachInterrupt(digitalPinToInterrupt(3), tick, FALLING );
  Serial.begin(9600);
  ccw();
}

void loop() {
  if (flag) {
    flag = 0;
    //Serial.print(antmil);
    //    Serial.print(micros() - antmil);
    //    Serial.print("    ");
    antmil = mil;
    mil = micros();
    vel = pow(((micros() - antmil) * 20 / 1000000), (-1)) * 60; //(millis() - antmil)*20 //pow((millis() - antmil), (1)) * 2000000
    for (int i = 0; i < t - 1; i++) {
      registre[i] = registre[i + 1];
    }
    acum = 0;
    registre[t - 1] = vel;
    for (int i = 0; i < t - 1; i++) {
      acum += registre[i];
      //    Serial.print(acum);
    }
    //  //    Serial.println(acum/t);

    Input = acum / t;
    Serial.print(Input);
    Serial.print(",");
    Serial.print(Output);
    Serial.print(",");
    Serial.println(rev);
  }
  myPID.Compute();
  analogWrite(4, Output);// map(analogRead(A0), 0, 1023, 0, 255)); //Output
  Setpoint = map(analogRead(A0), 0, 1023, 50, 255);
  if (rev < -200)
    cw();
  else if(rev > 0)
  ccw();




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
  digitalWrite(52, LOW);
  digitalWrite(53, HIGH);
  sentit = 0;
}

void cw()
{
  digitalWrite(52, HIGH);
  digitalWrite(53, LOW);
  sentit = 1;
}
