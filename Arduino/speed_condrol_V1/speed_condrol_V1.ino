#include <PID_v1.h>
#define t 20
double Setpoint, Input, Output;

PID myPID(&Input, &Output, &Setpoint, 1, 1, 0.05, DIRECT);
float acum = 0;
float vel = 0;
float registre[t];
float mil = 0;
float antmil = 0;
int flag = 1;


void setup() {
  pinMode(2, OUTPUT);
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
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
}

void loop() {
  if (flag) {
    flag = 0;
    //Serial.print(antmil);
    myPID.Compute();
    //    Serial.print(micros() - antmil);
    //    Serial.print("    ");
    Serial.print(Input);
    Serial.print(",");
    Serial.print(Output);
    Serial.print(",");
    Serial.println(Setpoint);
  }
  analogWrite(2, Output);// map(analogRead(A0), 0, 1023, 0, 255)); //Output
  Setpoint = map(analogRead(A0), 0, 1023, 50, 255);

}

void tick() {
  flag = 1;
  antmil = mil;
  mil = micros();
  vel = pow(((micros() - antmil) * 20 / 1000000), (-1)) * 60; //(millis() - antmil)*20 //pow((millis() - antmil), (1)) * 2000000
  for (int i = 0; i < t-1; i++) {
    registre[i] = registre[i+1];
  }
  acum = 0;
  registre[t-1] = vel;
  for (int i = 0; i < t-1; i++) {
    acum = registre[i];
  }
  
  Input = acum/t;
}
