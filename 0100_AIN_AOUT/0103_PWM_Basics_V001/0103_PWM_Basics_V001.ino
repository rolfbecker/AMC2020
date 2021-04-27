/*
 * analogWrite() to dimm an LED
 */
 
const int ledPin = 9;
const int d = 10; // delay in ms

// int i = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
//  int i = 0;
  
  for (int i=0; i<=255; i++) {
    analogWrite(ledPin,i);
    delay(d);
  }
  for (int i=255; i>=0; i--) {
    analogWrite(ledPin,i);
    delay(d);
  }
  
}
