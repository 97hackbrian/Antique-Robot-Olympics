#include <Wire.h>


#include "Adafruit_TCS34725softi2c.h"


#define SDApin1 47
#define SCLpin1 48

#define SDApin2 46
#define SCLpin2 45




Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin1, SCLpin1);

Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin2, SCLpin2);
void setup () {
  Serial.begin(9600);
if (tcs1.begin()) {
    Serial.println("Found sensor 1");
  } else {
    Serial.println("No TCS34725 found ... check your connections sensor 1");
    while (1); // halt!
  }
  if (tcs2.begin()) {
    Serial.println("Found sensor2");
  } else {
    Serial.println("No TCS34725 found ... check your connectionsc sensor 2");
    while (1); // halt!
  }
}

void loop (){
  uint16_t clear , red1, green1, blue1;
   uint16_t  red2, green2, blue2;

  

  delay(60);  // takes 50ms to read 

  
  tcs1.getRawData(&red1, &green1, &blue1, &clear);
  tcs2.getRawData(&red2, &green2, &blue2, &clear);


  
  Serial.print("C1:\t"); Serial.print(clear);
  Serial.print("\tR1:\t"); Serial.print(red1);
  Serial.print("\tG1:\t"); Serial.print(green1);
  Serial.print("\tB1:\t"); Serial.print(blue1);
  
  Serial.print("\t");
  
  Serial.print("C2:\t"); Serial.print(clear);
  Serial.print("\tR2:\t"); Serial.print(red2);
  Serial.print("\tG2:\t"); Serial.print(green2);
  Serial.print("\tB2:\t"); Serial.println(blue2);

  
}
