#include <Wire.h>


#include "Adafruit_TCS34725softi2c.h"


#define SDApin1 47
#define SCLpin1 48

#define SDApin2 45
#define SCLpin2 46
 int suma1=0;
  int suma2=0;


uint16_t clear , red1, green1, blue1;
  uint16_t  red2, green2, blue2;
  
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
  
  delay(50);  // takes 50ms to read 
  tcs1.getRawData(&red1, &green1, &blue1, &clear);
  delay(50);  // takes 50ms to read
  tcs2.getRawData(&red2, &green2, &blue2, &clear);

  suma1=(red1+green1+blue1)*0.5;
  suma2=(red2+green2+blue2)*0.5;   
  /*
  if(suma1>290&&suma1<360)
  {
     Serial.print("verde1");
  }
  if(suma1>1430)
  { 
     Serial.print("blanco1");
  }
  if(suma1>107&&suma1<199)
  {
     Serial.print("negro1");
  }
if(suma1>364&&suma1<400)
  {
     Serial.print("rojo1");
  }

Serial.print("         ");

 
  if(suma2>290&&suma2<360)
  {
     Serial.print("verde2");
  }
  if(suma2>1430)
  {
     Serial.print("blanco2");
  }
  if(suma2>107&&suma2<199)
  {
     Serial.print("negro2");
  }
if(suma2>364&&suma2<400)
  {
     Serial.print("rojo2");
  }
Serial.println("  ");
*/  
  Serial.print("C1:"); Serial.print(suma1);
  Serial.print("  ");
  Serial.print("R1:"); Serial.print(red1);
  Serial.print("  ");
  Serial.print("G1:"); Serial.print(green1);
  Serial.print("  ");
  Serial.print("B1:"); Serial.print(blue1);
  
  Serial.print("    ");
  
  Serial.print("C2:"); Serial.print(suma2);
  Serial.print("  ");
  Serial.print("R2:"); Serial.print(red2);
  Serial.print("  ");
  Serial.print("G2:"); Serial.print(green2);
  Serial.print("  ");
  Serial.print("B2:"); Serial.println(blue2);

}
