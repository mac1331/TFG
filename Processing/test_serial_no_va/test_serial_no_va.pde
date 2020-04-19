import processing.serial.*;
 
Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port
 
void setup() 
{
  size(200, 200);
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 9600);
}
 
void draw() {
  println("1");
  if (mouseOverRect() == true) {  // If mouse is over square,
    fill(204);                    // change color and
    myPort.write('H');              // send an H to indicate mouse is over square
    println("true");
  } 
  if (mouseOverRect() == false) {  // If mouse is over square,
                        // If mouse is not over square,
    fill(0);                      // change color and
    myPort.write('L');              // send an L otherwise
    println("out");
  }
  stroke(255,0,0);
  rect(50, 50, 100, 100);         // Draw a square
      //myPort.write('L');              // send an L otherwise

   ///redraw();
}
 
boolean mouseOverRect() { // Test if mouse is over square
  println("feasd");
  return ((mouseX >= 50) && (mouseX <= 150) && (mouseY >= 50) && (mouseY <= 150));
}
