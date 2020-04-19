int pinSensor = A0;   // Pin entrada potenciometre 
void setup() {
  Serial.begin(9600);         // Iniciem la comunicacio serie per veure els valors de l'arduino al ordinador
  pinMode(pinSensor, INPUT);  // Declarem els ports com a entrades i sortides

}

void loop() {

    Serial.println(analogRead(pinSensor));                        

}
