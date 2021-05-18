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
const int anaInPin =  A5;

const unsigned long msChargeDuration =  6000;
unsigned long       msChargeRef      =     0;
unsigned long       msChargeElapsed  =     0;

const unsigned long msSamplePeriod   =    20;
unsigned long       msSampleRef      =     0;
unsigned long       msSampleElapsed  =     0;

unsigned int adcValue = 0;
bool chargeState = LOW;
bool digInState  = LOW;

unsigned long chargeMV    = 0;  // charge pin, digital output, mV
unsigned long capacitorMV = 0;  // analog  input, capacitor voltage, mV
unsigned long digitalMV   = 0;  // digital input state mV

unsigned long ms = 0;


void setup() {
  pinMode(chargePin,OUTPUT);
  digitalWrite(chargePin,chargeState);

  pinMode(digInPin,INPUT);

  pinMode(anaInPin,INPUT);

  Serial.begin(115200);
  Serial.println("charge_voltage capacitor_voltage digital_input");

  ms = millis();
  msChargeRef = ms;
  msSampleRef = ms;
}


void loop() {
  
  ms = millis();
  
  msSampleElapsed = (ms - msSampleRef); 
   
  if ( msSampleElapsed >= msSamplePeriod) {
    msSampleRef = ms;
    adcValue    = analogRead(anaInPin);
    digInState  = digitalRead(digInPin);

    chargeMV = chargeState * 5010; // a bit more than 5V to distinguish the plotted curves
    capacitorMV = ( (unsigned long)adcValue * 5000 ) / 1024;
    digitalMV = digInState*5000;
    
    Serial.print(chargeMV);
    Serial.print(" ");
    Serial.print(capacitorMV);
    Serial.print(" ");
    Serial.println(digitalMV);
  }

  msChargeElapsed = (ms - msChargeRef);  
  
  if (msChargeElapsed >= msChargeDuration) {
    msChargeRef = ms;
    chargeState = toggle(chargePin);   
  }
}

bool toggle(int pin) {
  bool newPinState = !digitalRead(pin); 
  digitalWrite(pin, newPinState);
  return(newPinState);
}
