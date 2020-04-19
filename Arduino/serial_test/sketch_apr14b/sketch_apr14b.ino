char val;          // Data received from the serial port
int ledPin = 4; // Set the pin to digital I/O 4
 
 void setup() {
 pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
 Serial.begin(9600);            // Start serial communication at 9600 bps
 //Serial.setTimeout(10);
 }
 
 void loop() {

 }

 void serialEvent() {
    while (Serial.available()) { // If data is available to read,
    val = (char)Serial.read(); // read it and store it in val
    }
    if (val == 'H') { // If H was received
    digitalWrite(ledPin, HIGH); // turn the LED on
    Serial.println("ikvb");
    } else {
    digitalWrite(ledPin, LOW); // Otherwise turn it OFF
    }
    delay(100); // Wait 100 milliseconds for next reading
 }
