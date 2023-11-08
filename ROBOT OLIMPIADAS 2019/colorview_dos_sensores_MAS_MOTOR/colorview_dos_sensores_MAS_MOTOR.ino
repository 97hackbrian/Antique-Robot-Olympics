#include <Wire.h>
#include "Adafruit_TCS34725softi2c.h"

// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 3
#define greenpin 5
#define bluepin 6



int IN1=9;
int IN2=10;
int pwma=6;


int IN3=11;
int IN4=13;
int pwmb=8;

// You can use any digital pin for emulate SDA / SCL
#define SDApin1 47
#define SCLpin1 48

#define SDApin2 46
#define SCLpin2 45

// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable1[256];
byte gammatable2[256];


Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin1, SCLpin1);

Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin2, SCLpin2);
void setup() {
  Serial.begin(9600);
  Serial.println("Color View Test!");

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
  
  // use these three pins to drive an LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
   pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
      pinMode(pwma, OUTPUT); 
        pinMode(IN3, OUTPUT);
          pinMode(IN4, OUTPUT);
            pinMode(pwmb, OUTPUT);
 
}


void loop() {
  uint16_t clear , red1, green1, blue1;
   uint16_t  red2, green2, blue2;

  

  delay(60);  // takes 50ms to read 
  delay(60);
  
  tcs1.getRawData(&red1, &green1, &blue1, &clear);
  tcs2.getRawData(&red2, &green2, &blue2, &clear);


  
  Serial.print("C1:\t"); Serial.print(clear);
  Serial.print("\tR1:\t"); Serial.print(red1);
  Serial.print("\tG1:\t"); Serial.print(green1);
  Serial.print("\tB1:\t"); Serial.print(blue1);

    Serial.print("C2:\t"); Serial.print(clear);
  Serial.print("\tR2:\t"); Serial.print(red2);
  Serial.print("\tG2:\t"); Serial.print(green2);
  Serial.print("\tB2:\t"); Serial.print(blue2);

  // Figure out some basic hex code for visualization
  uint32_t sum1 = clear;
  float r1, g1, b1;
  r1 = red1; r1 /= sum1;
  g1 = green1; g1 /= sum1;
  b1 = blue1; b1 /= sum1;
  r1 *= 256; g1 *= 256; b1 *= 256;
  Serial.print("\t");
  Serial.print((int)r1, HEX); Serial.print((int)g1, HEX); Serial.print((int)b1, HEX);
  Serial.println();

  //Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );









  uint32_t sum2 = clear;
  float r2, g2, b2;
  r2 = red2; r2 /= sum2;
  g2 = green2; g2 /= sum2;
  b2 = blue2; b2 /= sum2;
  r2 *= 256; g2 *= 256; b2 *= 256;
  Serial.print("\t");
  Serial.print((int)r2, HEX); Serial.print((int)g2, HEX); Serial.print((int)b2, HEX);
  Serial.println();

  //Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );




digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(pwma, 100);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);             // wait for a second
  analogWrite(pwmb, 100);    // turn the LED off by making the voltage LOW
  delay(1300);  
  
  
  
  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(pwma, 100);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);             // wait for a second
  analogWrite(pwmb, 100);    // turn the LED off by making the voltage LOW
  delay(1300);    
 }
