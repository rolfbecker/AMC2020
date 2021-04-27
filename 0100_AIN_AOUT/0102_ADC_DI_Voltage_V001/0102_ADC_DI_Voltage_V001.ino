// ADC and Digital Input (DI): At which voltage levels does the DI toggle?

int dn  = 0; // digital number, used to store the ADC reading, i.e. dn = analogRead(A0)
int dn0 = 0; // memory of digital number 
int di  = 0; // digital pin state

float voltage = 0.0;
boolean hasChanged = true;

const int potPin = A0; // Potentiometer slider connected to A0
const int DIPin  =  2; // Digital input pin

void setup() {
  pinMode(DIPin,INPUT);  
  Serial.begin(115200);
  Serial.println("dn dn0 V D");
  dn = 0;
  for (int i = 0; i < 20; i++) 
    dn += analogRead(potPin);
  dn /= 20;

  di = digitalRead(DIPin);
}

void loop() {

  if (hasChanged) {
    hasChanged = false;
    
//    voltage = 5.0/1024 * dn;
//    voltage = 5000/1024 * dn;
    voltage = 5.0/1024 * dn * 1000;
    
    Serial.print(dn);
    Serial.print("   ");
    Serial.print(dn0);
    Serial.print("   ");
    Serial.print(voltage);
    Serial.print("   ");
    Serial.println(di*5000);

    dn0 = dn;    
  }

  dn = 0;
  for (int i = 0; i < 20; i++) dn += analogRead(potPin);
  dn /= 20;

  di = digitalRead(DIPin);

  if (dn != dn0) hasChanged = true;
  //if (abs(dn-dn0) > 1) hasChanged = true;

  delay(10);
}
