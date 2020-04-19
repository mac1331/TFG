 
import processing.serial.*;
 Serial myPort;        // The serial port
 String[] list;
 float inByte = 10;  
 boolean fet = true;
 
 
 
void setup() {
 size(800, 700);        
 println(Serial.list());
 myPort = new Serial(this, Serial.list()[3], 9600);
 myPort.bufferUntil('\n');
 background(50);
 
 }
 void draw()
 { 
   if (fet){
   myPort.write('w');
   fet = false;
 }
 }
void serialEvent (Serial myPort) {
 String inString = myPort.readStringUntil('\n');
  println(inString);
}
