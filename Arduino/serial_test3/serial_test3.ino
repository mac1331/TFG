int c;
int v=0;
 
void setup() {
  Serial.begin(57600);
}
 
void loop() {
  // read serial-data, if available
  while (Serial.available()) {
    c = Serial.read();
    // handle digits
    if ((c >= '0') && (c <= '9')) {
      v = 10 * v + c - '0';
    }
    // handle delimiter
    else if (c == 'e') {
      Serial.println(v);
      v = 0;
    }
  }
}
