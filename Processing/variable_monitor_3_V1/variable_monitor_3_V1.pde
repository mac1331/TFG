import processing.serial.*;
 
 Serial myPort;        // The serial port
 int xPos = 1;         // horizontal position of the graph
 String[] list;
 float inByte = 10;
 
 void setup() {
 size(800, 700);        
 println(Serial.list());
 myPort = new Serial(this, "COM5", 9600);
 myPort.bufferUntil('\n');
 background(50);
 
 }
 
 void draw()
 {     
   stroke(255,0,0);
   line(0,height/2,width,height/2);
   inByte = float(list[0]); 
   inByte = map(inByte, 0, 255, 0, height);
   stroke(255,255,255);
   point(xPos, height - inByte);
   inByte = float(list[1]); 
   inByte = map(inByte, 0, 255, 0, height);
   stroke(0,255,0);
   point(xPos, height - inByte);   
   inByte = float(list[2]); 
   inByte = map(inByte, -255, 255, 0, height);
   stroke(255,0,255);
   point(xPos, height - inByte); 
   inByte = float(list[3]); 
   inByte = map(inByte, -255, 255, 0, height);
   stroke(255,255,0);
   point(xPos, inByte); 
   
   if (xPos >= width) 
   {
     xPos = 0;
     background (50);
     
   } 
   else 
   {
     xPos++;
   }
 }
 
void serialEvent (Serial myPort) {
 String inString = myPort.readStringUntil('\n');
  println(inString);

 if (inString != null) {
   inString = trim(inString);
   list = split(inString, ',');
   inByte = float(list[0]);
   inByte = map(inByte, 0, 300, 0, height);

 }
   redraw();
 
}
