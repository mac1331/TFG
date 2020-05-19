//RPI first test conection test


//Motors conections declaration
int motor1A = 4;          //speed
int motor1B = 22;         //dir
int motor1C = 24;
int motor1I = 2;          //encoder input
volatile int motor1Count = 0;
volatile int dir1 = 0;
int flag1 = 0;

int motor2A = 5;          //speed
int motor2B = 26;         //dir
int motor2C = 28;
int motor2I = 3;          //encoder input
volatile int motor2Count = 0;
volatile int dir2 = 0;
int flag2 = 0;

int motor3A = 6;          //speed
int motor3B = 30;         //dir
int motor3C = 32;
int motor3I = 18;          //encoder input
volatile int motor3Count = 0;
volatile int dir3 = 0;
int flag3 = 0;


int currentPwm1;
int currentPwm2;
int currentPwm3;



int val = 0;
int finishedX = 1;
int finishedY = 1;
int vectorX = 1;
int vectorY = 1;
int negX = 0;
int negY = 0;
float rad120 = 2 * 3.1415 / 3;


void setup() {
  Serial.begin(57600);            // Start serial communication at 9600 bps
  //  Serial.setTimeout(20);
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

  cw1();
  cw2();
  cw3();
}

void loop() {
  if (Serial.available() > 0) {
    String inSer = Serial.readStringUntil('\n');
    if (inSer.startsWith("vec,")) {
      String input = inSer;
      inSer = "";
      int auxX, auxY, auxi, firstVal, secondVal;
      bool nf = false;
      for (int i = 0; i < input.length(); i++) {
        if (input.substring(i, i + 1) == ",") {
          if (nf == true) {
            firstVal = input.substring(auxi + 1, i).toInt();
            secondVal = input.substring(i + 1).toInt();
            break;
          }
          auxi = i;
          nf = true;
        }
      }
      Serial.print(firstVal);
      Serial.print("     ");
      Serial.println(secondVal);
      vectorX = firstVal;
      vectorY = secondVal;
    }

  }
  //val = 100;

  currentPwm1 = vectorX;
  currentPwm2 = vectorX * cos(rad120) - vectorY * sin(rad120);
  currentPwm3 = vectorX * cos(-rad120) - vectorY * sin(-rad120);
  //Serial.println(val);
  if (currentPwm1 < 0) {
    ccw1();
    analogWrite(motor1A, -currentPwm1 );
  }
  else {
    cw1();
    analogWrite(motor1A, currentPwm1 );
  }
  if (currentPwm2 < 0) {
    ccw2();
    analogWrite(motor2A, -currentPwm2 );
  }
  else {
    cw2();
    analogWrite(motor2A, currentPwm2 );
  }
  if (currentPwm3 < 0) {
    ccw3();
    analogWrite(motor3A, -currentPwm3 );
  }
  else {
    cw3();
    analogWrite(motor3A, currentPwm3 );
  }

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
