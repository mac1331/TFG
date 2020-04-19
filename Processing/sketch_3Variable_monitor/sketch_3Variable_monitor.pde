import processing.serial.*;
 
 Serial myPort;        // The serial port
 int xPos = 1;         // horizontal position of the graph
 String[] list;
 float inByte = 10;
 
 void setup() {
 size(800, 700);        
 println(Serial.list());
 myPort = new Serial(this, Serial.list()[2], 9600);
 myPort.bufferUntil('\n');
 background(0);
 
 }
 
 void draw()
 { }
 
 void serialEvent (Serial myPort) {
 String inString = myPort.readStringUntil('\n');
  println(inString);

 if (inString != null) {
   String[] list = split(inString, ',');
   inString = trim(inString);
   float inByte = float(list[0]); 
    inByte = map(inByte, 0, 300, 0, height);
 }
   stroke(255,0,255);
   point(xPos, height - inByte);
   print("OKAH");
 
   inString = trim(inString);
   inByte = float(list[1]); 
   inByte = map(inByte, 0, 300, 0, height);
 
   stroke(0,255,0);
   point(xPos, height - inByte);
 
   inString = trim(inString);
   inByte = float(list[2]); 
   inByte = map(inByte, 0, 300, 0, height);
 
   stroke(255,0,0);
   point(xPos, height - inByte);
 
   if (xPos >= width) 
   {
     xPos = 0;
     //background (0);
   } 
   else 
   {
     xPos++;
   }
 
}
