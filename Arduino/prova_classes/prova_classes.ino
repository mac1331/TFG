//Library import
#include <PID_v1.h>

//Parameters definition
#define t 3        //size of encoder filter register

//Motors conections declaration
int motor1A = 4;          //speed
int motor1B = 22;         //dir
int motor1C = 23;
int motor1I = 3;          //encoder input

int motor1A = 5;          //speed
int motor1B = 24;         //dir
int motor1C = 25;
int motor1I = 2;          //encoder input

int motor1A = 6;          //speed
int motor1B = 26;         //dir
int motor1C = 27;
int motor1I = 18;          //encoder input

void setup() {

}


class wheel(float a, int pwmpin, int dirpin1, int dirpin2, int intpin){
  private float angle = a;
  
  public void move2(x, y, w){
    ### maths fent servir x, y, a
  }
  public void ominbotcontrolerApp::updateVectors()
{
    moveVector.x*=-1;
    motorVectorA =moveVector;
    
    float rad120 = 2*3.1415/3;
    motorVectorB.x=moveVector.x* cos(-rad120)-moveVector.y* sin(-rad120);
    motorVectorB.y=moveVector.x* sin(-rad120) +moveVector.y*cos(-rad120);
    
    
    motorVectorC.x = moveVector.x *cos(rad120)-moveVector.y*sin(rad120);
    motorVectorC.y = moveVector.x *sin(rad120)+moveVector.y*cos(rad120);
}
