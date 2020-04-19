#define t 5

int motor1A = 4;
int motor1B = 22;
int motor1C = 23;
int motor1I = 3;
int vel = 250;
int accel = 1;
int sentit;
float mil = 0;
float antmil = 0;
float velocitat = 0;
float velocitatanterior = 0;
float acum = 0;
float registre[t];
int flag = 1;
double rev = 0;

float velocitatfil = 0;


void setup() {
  pinMode(motor1I, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1C, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motor1I), tick, FALLING );

  Serial.begin(9600);
  ccw();

}
void loop() {
  if (flag) {
    flag = 0;
    velocitatanterior = velocitat;
    velocitat = pow(((mil - antmil) * 20 / 1000000), (-1))*60;
    if(velocitat >= 2000){
      velocitat = velocitatanterior;
    }
    for (int i = 0; i < t - 1; i++) {
      registre[i] = registre[i + 1];
    }
    acum = 0;
    registre[t - 1] = velocitat;
    for (int i = 0; i < t - 1; i++) {
      acum += registre[i];
    }
    velocitatfil = acum / t;
  }

  //  if (millis() % 50 == 0) {
  //    if (vel == 255) {
  //      accel = 0;
  //    }
  //    if (vel == 40) {
  //      accel = 1;
  //    }
  //    if (accel) {
  //      vel ++;
  //    }
  //    else {
  //      vel --;
  //    }
  //  }
  Serial.print(map(analogRead(A0), 0, 1023, 0, 255));
  Serial.print(",");
  Serial.print(velocitatfil);
  Serial.print(",");
  Serial.print(velocitat);
  Serial.print(",");
  Serial.println(rev);
  analogWrite(motor1A, map(analogRead(A0), 0, 1023, 0, 255));
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
