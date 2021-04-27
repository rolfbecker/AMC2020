/*
 * Reads potentiometer voltage. 
 * Change detection (noise reduction) of ADC value inspired by Jonas Zender: Memory > 1 (dn1, dn2).
 * Notice that the boolean variable hasChanged can be modified inside analogAvg().
 * In the argument list of analogAvg() not the value of hasChanged is passed but the reference to the variable.
 * 
 * The ADC output is stored in uint16_t, uint8_t and int8_t.
 * Open the serial plotter, turn the potentiometer and observe the curves. 
 * What do you observe? Why does it happen?
 */

const int potPin = A0;

uint16_t iu16 = 0; // unsigned, 16 bits
uint8_t   iu8 = 0; // unsigned, 8 bits
int8_t    is8 = 0; // signed, 8 bits

boolean hasChanged = true;

uint8_t numAvg = 20;

void setup() {
  Serial.begin(115200);
  hasChanged = true;
  Serial.println("unsigned_16  unsigned_8  signed_8");
}

void loop() {

  if (hasChanged) {
    hasChanged = false;
    Serial.print(iu16);
    Serial.print("   ");
    Serial.print(iu8);
    Serial.print("   ");
    Serial.println(is8);    
  }

  iu16 = avgAnalog(potPin, numAvg, &hasChanged);
  is8 = iu8 = iu16;
}

uint16_t avgAnalog(int potPin, int n, boolean* isNew) {
  // static conserves the values of dn1 and dn2, 
  // even if the program execution has returned from the function.
  static int dn1 = 0; // memory, the state of dn 1 step ago 
  static int dn2 = 0; // memory, the state of dn 2 steps ago

  int dn = 0;
  for (uint8_t i = 0; i < n; i++) dn += analogRead(potPin);
  dn /= n;

  if ((dn != dn1) and (dn != dn2)) {
    *isNew = true;
    dn2 = dn1; dn1 = dn;
  }
  else hasChanged = false;    
  return(dn);
}
