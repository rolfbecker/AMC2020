
const int LED1pin = 9;
const int LED2pin = 10;

const int timeunit = 2;

bool LED1state = HIGH;
bool LED2state = HIGH;

void setup() {
  Serial.begin(9600);
  
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);  

  digitalWrite(LED1pin, LED1state);
  digitalWrite(LED2pin, LED2state);  
}

void loop() {
  static int k1 = 0;
  static int k2 = 0;

  k1++;
  k2++;

  if (k1 == 200) {
    k1 = 0;
    LED1state = !LED1state;
    digitalWrite(LED1pin, LED1state);  
    Serial.print("LED1state: ");
    Serial.println(LED1state);
  }
  
  if (k2  == 500) {
    k2 = 0;
    LED2state = !LED2state;
    digitalWrite(LED2pin, LED2state);  
    Serial.print("LED2state: ");
    Serial.println(LED2state);
  }
  
  delay(timeunit);
}
