
int LED = 10;

int timeunit = 150;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  morse_S();
  morse_O();
  morse_S();
  word_delay();
}

void morse_S() {
  for (int i = 0; i< 3; i++) {
    dot();
  }
  char_delay();
}

void morse_O() {
  for (int i = 0; i< 3; i++) {
    dash();
  }
  char_delay();
}

void dot() {
  digitalWrite(LED, true);
  delay(timeunit);
  digitalWrite(LED, false);
  delay(timeunit);
}

void dash() {
  digitalWrite(LED, true);
  delay(3*timeunit);
  digitalWrite(LED, false);
  delay(timeunit);  
}  

void word_delay() {
  delay(4*timeunit);
}

void char_delay() {
  delay(2*timeunit);  
}
