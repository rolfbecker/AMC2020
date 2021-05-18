/*
 * CC-BY, Rolf Becker, Rhine-Waal University, 2021-05-03
 * Charging and discharging a capacitor.
 * Schematic: 
 * GND - C - [Vcap] - R - D9
 * [Vcap] - A5
 * [Vcap] - D7
 * The node (potential) between R anc C is named [Vcap]. It is the capacitor voltage with respect to GND.
 * R: 100 k
 * C: 10 uF (electrolytic)
 * D9: controls charging and discharging of C.
 * A5: analog input, observes the capacitor voltage.
 * D7: digital input, to investigate at which voltage levels the digital input level changes. 
 */


const int chargePin =  9;
const int digInPin =   7;

const unsigned long msChargeDuration =  10;
unsigned long       msChargeRef      =   0;
unsigned long       msChargeElapsed  =   0;

bool chargeState = LOW;
bool digInState  = LOW;

unsigned long ms             = 0;
unsigned long t_charge_ms    = 0;
unsigned long t_discharge_ms = 0;
unsigned long t0             = 0;

void setup() {
  pinMode(chargePin,OUTPUT);
  digitalWrite(chargePin,chargeState);

  pinMode(digInPin,INPUT);

  Serial.begin(115200);
  Serial.println("charge_ms discharge_ms");

  ms = millis();
  msChargeRef = ms;
}


void loop() {
  
  ms = millis();
  
  msChargeElapsed = (ms - msChargeRef);  
  
  if (msChargeElapsed >= msChargeDuration) {
    msChargeRef = ms;
    
    if (chargeState == LOW) {   
      chargeState = toggle(chargePin);
      t0 = micros();
      while(!digitalRead(digInPin));
      t_charge_ms = micros() - t0;   
    }
    else {
      chargeState = toggle(chargePin);
      t0 = micros();
      while(digitalRead(digInPin)); 
      t_discharge_ms = micros() - t0;   
    }
    
    Serial.print(t_charge_ms);
    Serial.print("  ");
    Serial.println(t_discharge_ms); 
  }
}

bool toggle(int pin) {
  bool newPinState = !digitalRead(pin); 
  digitalWrite(pin, newPinState);
  return(newPinState);
}
