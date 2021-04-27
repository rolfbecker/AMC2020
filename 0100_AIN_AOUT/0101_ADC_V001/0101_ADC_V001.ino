
int k = 0;
int val = 0; // define (int) and initialize (=0)! 

const int potPin = A0; // Potentiometer slider connected to A0
const int LEDPin = 13; 

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPin,OUTPUT);
  Serial.begin(115200);
  Serial.println("val   2*val");
//  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(potPin);
  Serial.print(val);
  Serial.print("   ");
  Serial.println(2 * val);
  
  //k = k+1;
  delay(200);
  digitalWrite(LEDPin, !digitalRead(LEDPin));
}
