/* 
 * Program to demostrate differences between signed and unsigned integer data types. 
 */

#include <stdio.h>

/*
char        c=0;   // character
byte        b=0;   // byte

int        ii=0;   // standard Arduino notation. What precisely is this type?
int16_t  is16=0;   // signed interger, 16 bits wide 
uint16_t iu16=0;   // unsigned interger, 16 bits wide

long       il;   // standard Arduino notation. What precisely is this type?
int32_t  is32;   // signed interger, 32 bits wide 
uint32_t iu32;   // unsigned interger, 32 bits wide
*/

int8_t    is8=0;   // signed interger, 8 bits wide
uint8_t   iu8=0;   // unsigned integer, 8 bits wide

char sbuf[80];
char binstr[33];
void setup() {
  Serial.begin(115200);
  Serial.println("Same bin number leads to diffent behavior as int8_t and uint8_t");
  delay(2000);
}

void loop() {
  is8 = iu8;
  int2binstr(binstr, iu8, 8);  // implicit type cast: iu8 -> long
  sprintf(sbuf, "bin: %8s  uint8_t: %+4d  int8_t: %+4d", binstr, iu8, is8);
  Serial.println(sbuf);
  iu8++;
  delay(100);
}

void int2binstr(char* s, long d, int n) {
  const long mask = 1;
  for (int i=0; i<n; i++) {
    if ((d>>i & mask) == 0) s[n-i-1]='0';
    else s[n-i-1] = '1';
  }
  s[n] = '\0'; // end of string
}
