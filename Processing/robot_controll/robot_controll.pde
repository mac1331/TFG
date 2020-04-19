// libraries
import processing.serial.*;
// serial connection
Serial port;
 
int vectorX = 0;
int vectorY = 0;
int number = 0;


void setup() {
  port = new Serial(this, Serial.list()[2], 57600);
  size(600, 600);
  background(205);
}

 
void draw() {
  background(205);
  stroke(255, 0, 0);
  strokeWeight(3);
  line(250, 130, 350, 130);
  line(130, 375, 200, 450);
  line(400, 450, 470, 375);
  stroke(0, 255, 0);
  strokeWeight(5);
  vectorX = mouseX - 300;
  vectorY = mouseY - 300;
  line(300, 300, vectorX+300, vectorY+300);
  
  stroke(0, 0, 100);
  strokeWeight(2);
  line(300, 130, 300+vectorX, 130+vectorY);
  line(166, 413, 166+vectorX, 413+vectorY);
  line(434, 413, 434+vectorX, 413+vectorY);
  stroke(0, 200, 200);
  strokeWeight(3);
  line(300, 130, 300+vectorX, 130);
  line(166, 413, 166+vectorX, 413+vectorY);
  line(434, 413, 434+vectorX, 413+vectorY);
  //port.write(Integer.toString(number));
  //port.write('e');
  //port.write('\n');
  //delay(1000);
}
void mousePressed() {
  // create random number

  println("X"+vectorX+"    Y"+vectorY);
  // send number
  
  port.write(Integer.toString(vectorX));
  if(vectorX < 0){
    port.write(':');
  }
  port.write(',');
  port.write(Integer.toString(vectorY));
  if(vectorY < 0){
    port.write('n');
  }
  port.write('e');
}

void serialEvent(Serial p) {
  try {
    // get message till line break (ASCII > 13)
    String message = p.readStringUntil(13);
    // just if there is data
    if (message != null) {
      println("message received: "+trim(message));
    }
  }
  catch (Exception e) {
  }
}
