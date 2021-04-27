
int LED = 10;

int timeunit = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  dot();
  dot();
  dot();
  delay(10*timeunit);
}

void morse_S() {
// send <dot><dot><dot>
}

void morse_O() {
// send <dash><dash><dash>
}

void dot() {
  digitalWrite(LED, true);
  delay(timeunit);
  digitalWrite(LED, false);
  delay(timeunit);   
}

void dash() {
}  
