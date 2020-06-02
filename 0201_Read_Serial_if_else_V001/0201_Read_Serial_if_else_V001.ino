/*
 * Read a single chracter from the serial port and take actions conditioned by the character. 
 * if - else if - else structure
 */
char inChar = 0;      // 'empty' character
//char inChar = '\0'; // 'empty' character, same as above

void setup() {
  Serial.begin(115200);
  Serial.println("Send 'a', 'b' or any other character");
  Serial.flush();
}

void loop() {
  inChar = 0;  // initialize with 'empty'

  // Only the last character sent is taken into account.
  while(Serial.available() > 0) {
    inChar = Serial.read();
  }

  if (inChar==0) {
    // do nothing
  }
  else if (inChar=='a') {
    Serial.println("inChar == 'a'");
  }
  else if (inChar=='b') {
    Serial.println("inChar == 'b'");
  }
  else {
    Serial.println("inChar is neither 'a' nor 'b'");
  }
}
