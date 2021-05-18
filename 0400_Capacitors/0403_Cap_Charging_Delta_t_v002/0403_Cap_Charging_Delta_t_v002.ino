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


const int chargePin =   9;
const int digInPin  =   7;
const int beepPin   =  13;

const unsigned long msChargeDuration =  10;
unsigned long       msChargeRef      =   0;
unsigned long       msChargeElapsed  =   0;

bool chargeState = LOW;
bool digInState  = LOW;

unsigned long ms             = 0;
unsigned long t_charge_us    = 0;
unsigned long t_discharge_us = 0;
unsigned long t_charge_avg    = 0;
unsigned long t_discharge_avg = 0;
unsigned long t0             = 0;

void setup() {
  pinMode(chargePin,OUTPUT);
  digitalWrite(chargePin,chargeState);

  pinMode(beepPin,OUTPUT);
  digitalWrite(beepPin,LOW);

  pinMode(digInPin,INPUT);

  Serial.begin(115200);
  Serial.println("charge_us charge_avg discharge_us discharge_avg");

  ms = millis();
  msChargeRef = ms;
}


void loop() {
  
  ms = millis();
  
  msChargeElapsed = ms - msChargeRef;  
  
  if (msChargeElapsed >= msChargeDuration) {
    msChargeRef = ms;
    
    if (chargeState == LOW) {   
      chargeState = toggle(chargePin);
      t0 = micros();
      while(!digitalRead(digInPin));
      t_charge_us = micros() - t0;
      t_charge_avg = (9*t_charge_avg + t_charge_us)/10;   
    }
    else {
      chargeState = toggle(chargePin);
      t0 = micros();
      while(digitalRead(digInPin)); 
      t_discharge_us = micros() - t0;   
      t_discharge_avg = (9*t_discharge_avg + t_discharge_us)/10;   
    }

    if (t_discharge_avg > 60) digitalWrite(beepPin,HIGH);
    else digitalWrite(beepPin,LOW);
    
    Serial.print(t_charge_us);
    Serial.print("  ");
    Serial.print(t_charge_avg); 
    Serial.print("  ");
    Serial.print(t_discharge_us);
    Serial.print("  ");
    Serial.print(t_discharge_avg);
    Serial.println(); 
  }
}

bool toggle(int pin) {
  bool newPinState = !digitalRead(pin); 
  digitalWrite(pin, newPinState);
  return(newPinState);
}
