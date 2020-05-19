void setup() {
  Serial.begin(9600);
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
      Serial.print(firstVal+secondVal);
      Serial.print("     ");
      Serial.println(secondVal);
    }
  }
}
