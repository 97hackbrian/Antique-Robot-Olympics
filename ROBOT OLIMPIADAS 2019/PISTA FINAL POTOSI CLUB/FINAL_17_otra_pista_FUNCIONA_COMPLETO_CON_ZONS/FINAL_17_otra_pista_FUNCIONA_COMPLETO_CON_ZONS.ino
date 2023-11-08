
#include <SharpIR.h>
#include <Wire.h>
#include "Adafruit_TCS34725softi2c.h"
#include <QTRSensors.h>

#define SDApin1 47
#define SCLpin1 48

#define SDApin2 45
#define SCLpin2 46

uint16_t clear , red1, green1, blue1;
uint16_t  red2, green2, blue2;
int suma1 = 0;
int suma2 = 0;
Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin1, SCLpin1);

Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin2, SCLpin2);





#define ir1 A15
#define ir2 A14
#define ir3 A13

#define model 1080
SharpIR SharpIR2(ir2, model);
int dis2 = 0;
int c = 0;

int b=0;



#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {
  A0, A1, A2, A3, A4, A5, A6, A7
},
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


#define MOTORLEFT_DIR_A  11
#define MOTORLEFT_DIR_B  13
#define MOTORLEFT_PWM    8

#define MOTORRIGH_DIR_A  9
#define MOTORRIGH_DIR_B  10
#define MOTORRIGH_PWM    6


#define BT1 28
int BT2 = PJ4;

#define Sx1 A8
#define Sx2 A9

int boton1, boton2;

int sx1, sx2;
int poslast;

float KP = 0.25; //0.25
float KD = 1.1; //2.4//2.1//1.1
float Ki = 0; //0

int Velmax = 82;//115

int error1 = 0;
int error2 = 0;
int error3 = 0;
int error4 = 0;
int error5 = 0;
int error6 = 0;

int e = 0;
void setup() {
  Serial.begin(9600);
  pinMode(BT1, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  while (true)
  {
    boton1 = digitalRead(BT1);
    if (boton1 == HIGH)
    {
      delay(500);
      e++;
    }

    if (analogRead(A0) <= 100 && analogRead(A1) <= 100 && analogRead(A2) <= 100 && analogRead(A3) <= 100 && analogRead(A4) <= 100 && analogRead(A5) <= 100 && analogRead(A6) <= 100 && analogRead(A7) <= 100 )
    {
      Serial.println(e);
      break;
    }
  }
  delay(99);
  digitalWrite(13, HIGH);
  delay(99);
  digitalWrite(13, LOW);
  delay(99);
  digitalWrite(13, HIGH);
  delay(99);
  digitalWrite(13, LOW);
  delay(705);

  for (int x = 0; x < e; x++)
  {
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
  }
  digitalWrite(13, LOW);

  delay(1100);
  digitalWrite(13, HIGH);
  delay(99);
  digitalWrite(13, LOW);
  delay(150);
  digitalWrite(13, HIGH);
  delay(99);
  digitalWrite(13, LOW);

  delay(1000);


  pinMode(MOTORRIGH_DIR_A , OUTPUT);
  pinMode(MOTORRIGH_DIR_B , OUTPUT);
  pinMode(MOTORRIGH_PWM   , OUTPUT);
  pinMode(MOTORLEFT_DIR_A , OUTPUT);
  pinMode(MOTORLEFT_DIR_B , OUTPUT);
  pinMode(MOTORLEFT_PWM   , OUTPUT);

  pinMode(Sx1, INPUT);
  pinMode(Sx2, INPUT);

  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);

  delay(500);

  while (true)
  {
    boton1 = digitalRead(BT1);
    if (boton1 == HIGH)
    {
      break;
    }
  }

  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  for (int i = 0; i < 350; i++)
  {
    qtra.calibrate();
  }
  digitalWrite(13, LOW);


  delay(300);
  while (true)
  {
    boton1 = digitalRead(BT1);
    if (boton1 == HIGH)
    {
      break;
    }
  }

  delay(0);
}
void setMotorLeft(int value)
{
  if ( value >= 0 )
  {
    digitalWrite(MOTORRIGH_DIR_A, HIGH);
    digitalWrite(MOTORRIGH_DIR_B, LOW);
  }
  else
  {
    digitalWrite(MOTORRIGH_DIR_A, LOW);
    digitalWrite(MOTORRIGH_DIR_B, HIGH);
    value *= -1;
  }
  analogWrite(MOTORRIGH_PWM, value);
}

void setMotorRigh(int value)
{
  if ( value >= 0 )
  {
    digitalWrite(MOTORLEFT_DIR_A, HIGH);
    digitalWrite(MOTORLEFT_DIR_B, LOW);
  }
  else
  {
    digitalWrite(MOTORLEFT_DIR_A, LOW);
    digitalWrite(MOTORLEFT_DIR_B, HIGH);
    value *= -1;
  }
  analogWrite(MOTORLEFT_PWM, value);
}

void motores(int left, int righ)
{
  //digitalWrite(STANDBY,HIGH);
  setMotorLeft(left);
  setMotorRigh(righ);
}

void freno(boolean left, boolean righ, int value)
{
  //  digitalWrite(STANDBY,HIGH);

  if ( left )
  {
    digitalWrite(MOTORRIGH_DIR_A, HIGH);
    digitalWrite(MOTORRIGH_DIR_B, HIGH);
    analogWrite (MOTORRIGH_PWM, value);
  }

  if ( righ )
  {
    digitalWrite(MOTORLEFT_DIR_A, HIGH);
    digitalWrite(MOTORLEFT_DIR_B, HIGH);
    analogWrite (MOTORLEFT_PWM, value);
  }
}


unsigned int posicion = 0;

int proporcional = 0;
int integral = 0;
int derivativo = 0;

int diferencial = 0;
int last_prop;
int Target = 3500;




void loop() {
  //PID();
  // qtra.readLine(sensorValues);
  a:
  if (analogRead(A0) >= 400 && analogRead(A1) >= 400 && analogRead(A2) >= 400 && analogRead(A3) >= 400 && analogRead(A4) >= 400 && analogRead(A5) >= 400 && analogRead(A6) >= 400 && analogRead(A7) >= 400 )
  {
    c++;

if(c==1)
    {
     motores(70,70);
     delay(200);
    goto a; 
    }
    
    motores(-10 , -10);//-12,-19
    delay(75);
    motores(-5, -5);
    delay(390);

    motores(-25, -29);//-23,-39//////////-24,-30
    digitalWrite(13, HIGH);

    while (true)
    {
      motores(-29, -25);//38,44//33,39//30,36//    -28.-30
      leer_color();
      if (suma1 >= 142 && suma1 <= 245 && suma2 >= 1130)
      {
        motores(0, 0);
        delay(100);
        motores(-40, 70);
        delay(360);
        break;
      }
      else if (suma2 >= 145 && suma2 <= 245 && suma1 >= 1130)
      {
        motores(0, 0);
        delay(100);
        motores(80, -40);
        delay(400);
        break;
      }
      if (suma1 >= 1500 && suma2 >= 1500)
      {
        motores(0, 0);
        delay(140);
        motores(95, 95);
        delay(200);
        break;
      }
      else
      {
        motores(-27, -33);
      }
      digitalWrite(13, LOW);
    }
  }



  if (analogRead(A7) > 780 && analogRead(A6) > 780 && analogRead(A5) > 780 && analogRead(A4) > 780 && analogRead(A3) >780 && analogRead(A1) < 150 && analogRead(A0) < 150)
  {
    motores(-43, 55);
    delay(335);
  }

if (analogRead(A0) > 780 && analogRead(A1) > 780 && analogRead(A2) > 780 && analogRead(A3) > 780 && analogRead(A4) > 780 && analogRead(A6) < 150 && analogRead(A7) < 150)
  {
    motores(55, -43);
    delay(305);
  }





  while(c==5)
  {
    Velmax=70;
     if (analogRead(A7) > 790 && analogRead(A6) > 790 && analogRead(A5) > 790 && analogRead(A4) > 790 && analogRead(A3) >790 && analogRead(A1) < 150 && analogRead(A0) < 150)
  {
    motores(-53, 65);
    delay(335);
  }

if (analogRead(A0) > 790 && analogRead(A1) > 790 && analogRead(A2) > 790 && analogRead(A3) > 790 && analogRead(A4) > 790 && analogRead(A6) < 150 && analogRead(A7) < 150)
  {
    motores(65, -53);
    delay(305);
  }
 
    PID();
    
  if (analogRead(A0) >= 400 && analogRead(A1) >= 400 && analogRead(A2) >= 400 && analogRead(A3) >= 400 && analogRead(A4) >= 400 && analogRead(A5) >= 400 && analogRead(A6) >= 400 && analogRead(A7) >= 400 )
  {
    break;
  }
  }

  
  if (c == 1)//8
  {
    dis2 = SharpIR2.distance();
  }
  if (dis2 <= 9 && c == 1)
  {
    motores(0, 0);
    delay(100);
    motores(-50, -50);
    delay(50);
    
    motores(50, -60);
    delay(400);
    motores(0, 0);
    delay(200);
    motores(50, 50);
    delay(280);
    motores(32, 59);
    delay(300);
    while (true)
    {
      motores(32, 59);
      if (analogRead(A3) > 600)
      {
        motores(80, -43);
        delay(250);
        break;
      }
    }
    
  }



  

  
  if (c == 6)//8
  {
    dis2 = SharpIR2.distance();
  }
  if (dis2 <= 8 && c == 6)
  {
    motores(0, 0);
    delay(100);
    motores(-60, 50);
    delay(340);
    motores(0, 0);
    delay(200);
    motores(50, 50);
    delay(240);
    motores(59, 32);
    while (true)
    {
      motores(59, 32);
      if (analogRead(A4) > 600)
      {
        motores(-43, 80);
        delay(250);
        break;
      }
    }
  }





  

  if (c == 3) {
    Velmax =80;
  }

  if (c == 2) {
    Velmax =50;
  }

  while (c == 10)
  {
   /////x:
   KP=0.68;
   KD=0.8;
    Velmax=40;
    PID();
    
    
  if (analogRead(A7) > 600 && analogRead(A6) > 600 && analogRead(A5) > 600 && analogRead(A4) > 600 && analogRead(A3) >600 && analogRead(A1) < 150 && analogRead(A0) < 150)
  {
    motores(-43, 55);
    delay(335);
  }

if (analogRead(A0) > 600 && analogRead(A1) > 600 && analogRead(A2) > 600 && analogRead(A3) > 600 && analogRead(A4) > 600 && analogRead(A6) < 150 && analogRead(A7) < 150)
  {
    motores(55, -43);
    delay(305);
  }
    //frenos_contorno();
    //leer_color();
    //unsigned int position = qtra.readLine(sensorValues);

/*
      if (analogRead(A0) <= 150 && analogRead(A1) <= 150 && analogRead(A2) <= 150 && analogRead(A3) <= 150 && analogRead(A4) <= 150 && analogRead(A5) <= 150 && analogRead(A6) <= 150 && analogRead(A7) <= 150 )
    {
      b++;
      motores(40,40);
      delay(50);
      while(true)
      {
        motores(40,40);
        if(analogRead(A4)>700||analogRead(A5)>700)
        {
          b++;
          goto x; 
        }
      }
    } 
    if (analogRead(A0) <= 150 && analogRead(A1) <= 150 && analogRead(A2) <= 150 && analogRead(A3) <= 150 && analogRead(A4) <= 150 && analogRead(A5) <= 150 && analogRead(A6) <= 150 && analogRead(A7) <= 150 && b==3)
    {
*/
leer_color();
if((suma2>364&&suma2<400)||(suma1>364&&suma1<400))
{
   
      while (e == 1)
      {
#define model 1080
        SharpIR SharpIR1(ir1, model);
        SharpIR SharpIR2(ir2, model);
        SharpIR SharpIR3(ir3, model);
        int dis1 = 0;
        int dis2 = 0;
        int dis3 = 0;



        motores(35, 35);
        delay(790);
        motores(15, 40);
        delay(1299);
        motores(35, 35);
        delay(800);
        while (true)
        {

          dis1 = SharpIR1.distance();
          if (dis1 == 9)
          {
            motores(40, 40);
            delay(1);
          }
          else if (dis1 > 9)
          {
            motores(40, 30);
            delay(0);
          }
          else if (dis1 < 9)
          {
            motores(30, 40);
            delay(0);
          }
          dis2 = SharpIR2.distance();
          if (dis2 <= 8)
          {

            motores(0, 0);
            delay(30);

            motores(40, -40);
            delay(690);
            while (true)
            {

              dis1 = SharpIR1.distance();
              if (dis1 == 9)
              {
                motores(40, 40);
                delay(1);
              }
              else if (dis1 > 9)
              {
                motores(40, 30);
                delay(0);
              }
              else if (dis1 < 9)
              {
                motores(30, 40);
                delay(0);
              }

              if (analogRead(A0) > 600 && analogRead(A1) > 600 && analogRead(A2) > 600 && analogRead(A3) > 600 & analogRead(A4) > 600 & analogRead(A5) > 600 && analogRead(A6) > 600 && analogRead(A7) > 600)
              {
                while (true)
                {
                  motores(0, 0);
                }
              }
            }
          }
        }
      }



      while (e == 2)
      {
#define model 1080
        SharpIR SharpIR1(ir1, model);
        SharpIR SharpIR2(ir2, model);
        SharpIR SharpIR3(ir3, model);


        SharpIR SharpIR3D(ir3, 20150);
        SharpIR SharpIR1D(ir1, 20150);
        int dis1 = 0;
        int dis2 = 0;
        int dis3 = 0;


        int dis3D = 0;
        int dis1D = 0;
        while (true)
        {

          dis3 = SharpIR3.distance();
          if (dis3 == 12)
          {
            motores(40, 40);
            delay(1);
          }
          else if (dis3 < 12)
          {
            motores(40, 35);
            delay(0);
          }
          else if (dis3 > 12)
          {
            motores(35, 40);
            delay(0);
          }
          dis2 = SharpIR2.distance();
          if (dis2 <= 81)
          {

            motores(0, 0);
            delay(30);

            motores(-40, 40);
            delay(532);

            motores(0, 0);
            delay(30);

            motores(40, 40);
            delay(999);

            while (true)
            {

              dis1D = SharpIR1D.distance();
              if (dis1D == 38)
              {
                motores(40, 40);
                delay(1);
              }
              else if (dis1D < 38)
              {
                motores(40, 25);
                delay(1);
              }
              else if (dis1D > 38)
              {
                motores(25, 40);
                delay(1);
              }
              dis2 = SharpIR2.distance();
              if (dis2 <= 11)
              {
                motores(40, -40);
                delay(780);
                motores(0, 0);
                delay(300);
                motores(40, 40);
                delay(1200);
              }

              if (analogRead(A0) > 600 && analogRead(A1) > 600 && analogRead(A2) > 600 && analogRead(A3) > 600 & analogRead(A4) > 600 & analogRead(A5) > 600 && analogRead(A6) > 600 && analogRead(A7) > 600)
              {
                while (true)
                {
                  motores(0, 0);
                }
              }
            }
          }
        }
      }



      while (e == 3)
      {


#define ir1 A15
#define ir2 A14
#define ir3 A13

#define model 1080
        SharpIR SharpIR1(ir1, model);
        SharpIR SharpIR2(ir2, model);
        SharpIR SharpIR3(ir3, model);


        SharpIR SharpIR3D(ir3, 20150);
        SharpIR SharpIR1D(ir1, 20150);
        int dis1 = 0;
        int dis2 = 0;
        int dis3 = 0;


        int dis3D = 0;
        int dis1D = 0;

        while (true)
        {

          dis3 = SharpIR3.distance();
          if (dis3 == 12)
          {
            motores(40, 40);
            delay(1);
          }
          else if (dis3 < 12)
          {
            motores(40, 35);
            delay(0);
          }
          else if (dis3 > 12)
          {
            motores(35, 40);
            delay(0);
          }
          dis2 = SharpIR2.distance();
          if (dis2 <= 65)
          {

            motores(0, 0);
            delay(30);

            motores(-40, 40);
            delay(610);
            while (true)
            {

              dis3D = SharpIR3D.distance();
              if (dis3D == 62)
              {
                motores(40, 40);
                delay(1);
              }
              else if (dis3D > 62)
              {
                motores(40, 35);
                delay(1);
              }
              else if (dis3D < 62)
              {
                motores(35, 40);
                delay(1);
              }
              dis2 = SharpIR2.distance();
              if (dis2 <= 11)
              {
                motores(40, -40);
                delay(700);
                motores(0, 0);
                delay(300);
                motores(40, 40);
                delay(1200);
              }

              if (analogRead(A0) > 600 && analogRead(A1) > 600 && analogRead(A2) > 600 && analogRead(A3) > 600 & analogRead(A4) > 600 & analogRead(A5) > 600 && analogRead(A6) > 600 && analogRead(A7) > 600)
              {
                while (true)
                {
                  motores(0, 0);
                }
              }
            }
          }
        }
      }

      while (e == 4)
      {

#define ir1 A15
#define ir2 A14
#define ir3 A13

#define model 1080
        SharpIR SharpIR1(ir1, model);
        SharpIR SharpIR2(ir2, model);
        SharpIR SharpIR3(ir3, model);


        SharpIR SharpIR3D(ir3, 20150);
        SharpIR SharpIR1D(ir1, 20150);
        int dis1 = 0;
        int dis2 = 0;
        int dis3 = 0;


        int dis3D = 0;
        int dis1D = 0;




        while (true)
        {

          dis3 = SharpIR3.distance();
          if (dis3 == 12)
          {
            motores(40, 40);
            delay(1);
          }
          else if (dis3 < 12)
          {
            motores(40, 35);
            delay(0);
          }
          else if (dis3 > 12)
          {
            motores(35, 40);
            delay(0);
          }
          dis2 = SharpIR2.distance();
          if (dis2 <= 35)
          {

            motores(0, 0);
            delay(30);

            motores(-40, 40);
            delay(580);
            while (true)
            {

              dis3D = SharpIR3D.distance();
              if (dis3D == 32)
              {
                motores(40, 40);
                delay(1);
              }
              else if (dis3D > 32)
              {
                motores(40, 35);
                delay(1);
              }
              else if (dis3D < 32)
              {
                motores(35, 40);
                delay(1);
              }

              if (analogRead(A0) > 600 && analogRead(A1) > 600 && analogRead(A2) > 600 && analogRead(A3) > 600 & analogRead(A4) > 600 & analogRead(A5) > 600 && analogRead(A6) > 600 && analogRead(A7) > 600)
              {
                while (true)
                {
                  motores(0, 0);
                }
              }
            }
          }
        }
      }


      while (e == 5)
      {


#define ir1 A15
#define ir2 A14
#define ir3 A13

#define model 1080
        SharpIR SharpIR1(ir1, model);
        SharpIR SharpIR2(ir2, model);
        SharpIR SharpIR3(ir3, model);
        int dis1 = 0;
        int dis2 = 0;
        int dis3 = 0;


        while (true)
        {

          dis3 = SharpIR3.distance();
          if (dis3 == 12)
          {
            motores(40, 40);
            delay(1);
          }
          else if (dis3 < 12)
          {
            motores(40, 35);
            delay(0);
          }
          else if (dis3 > 12)
          {
            motores(35, 40);
            delay(0);
          }
          dis2 = SharpIR2.distance();
          if (dis2 <= 8)
          {

            motores(0, 0);
            delay(30);

            motores(-40, 40);
            delay(580);
            while (true)
            {

              dis3 = SharpIR3.distance();
              if (dis3 == 12)
              {
                motores(40, 40);
                delay(1);
              }
              else if (dis3 < 12)
              {
                motores(40, 35);
                delay(1);
              }
              else if (dis3 > 12)
              {
                motores(35, 40);
                delay(1);
              }

              if (analogRead(A0) > 600 && analogRead(A1) > 600 && analogRead(A2) > 600 && analogRead(A3) > 600 & analogRead(A4) > 600 & analogRead(A5) > 600 && analogRead(A6) > 600 && analogRead(A7) > 600)
              {
                while (true)
                {
                  motores(0, 0);
                }
              }
            }
          }
        }
      }
    }
  }
  PID();

  frenos_contorno();
 
}
void PID() {
  unsigned int position = qtra.readLine(sensorValues);
  proporcional =  3500 - ((int)position);

  derivativo = proporcional - last_prop;
  integral = error1 + error2 + error3 + error4 + error5 + error6;
  last_prop = proporcional;

  error6 = error5;
  error5 = error4;
  error4 = error3;
  error3 = error2;
  error2 = error1;
  error1 = proporcional;

  int diferencial = ( proporcional * KP ) + ( derivativo * KD ) + (integral * Ki) ;

  if ( diferencial > Velmax ) diferencial = Velmax;
  else if ( diferencial < -Velmax ) diferencial = -Velmax;

  ( diferencial < 0 ) ? motores(Velmax + diferencial, Velmax) : motores(Velmax, Velmax - diferencial);
}




void frenos_contorno() {
  unsigned int position = qtra.readLine(sensorValues);
  if (position > 6500)
  {
    if (analogRead(A0) >= 400 && analogRead(A1) >= 400 && analogRead(A2) >= 400 && analogRead(A3) >= 400 && analogRead(A4) >= 400 && analogRead(A5) >= 400 && analogRead(A6) >= 400 && analogRead(A7) >= 400 )
    {


      motores(-19, -19);
      delay(75);
      motores(0, 0);
      delay(100);

      motores(-26, -44);//-23,-39
      digitalWrite(13, HIGH);

      while (true)
      {
        motores(-27, -33);//38,44//33,39//30,36//
        leer_color();
        if (suma1 >= 290 && suma1 <= 360 && suma2 >= 1430)
        {
          motores(0, 0);
          delay(100);
          motores(-40, 70);
          delay(360);
          break;
        }
        else if (suma2 >= 200 && suma2 <= 380 && suma1 >= 1330)
        {
          motores(0, 0);
          delay(100);
          motores(80, -40);
          delay(400);
          break;
        }
        else if (suma1 >= 1600 && suma2 >= 1600)
        {
          motores(0, 0);
          delay(140);
          motores(115, 115);
          delay(200);
          break;
        }
        else
        {
          motores(-27, -33);
        }
        digitalWrite(13, LOW);
      }
    }
    motores(-100, 50);//-140,130//-100,90//
    delay(9);
  }
  else if (position < 500)
  {
    if (analogRead(A0) >= 400 && analogRead(A1) >= 400 && analogRead(A2) >= 400 && analogRead(A3) >= 400 && analogRead(A4) >= 400 && analogRead(A5) >= 400 && analogRead(A6) >= 400 && analogRead(A7) >= 400 )
    {


      motores(-19, -19);
      delay(75);
      motores(0, 0);
      delay(100);

      motores(-26, -44);//-23,-39
      digitalWrite(13, HIGH);

      while (true)
      {
        motores(-27, -33);//38,44//33,39//30,36//
        leer_color();
        if (suma1 >= 290 && suma1 <= 360 && suma2 >= 1430)
        {
          motores(0, 0);
          delay(100);
          motores(-40, 70);
          delay(360);
          break;
        }
        else if (suma2 >= 200 && suma2 <= 380 && suma1 >= 1330)
        {
          motores(0, 0);
          delay(100);
          motores(80, -40);
          delay(400);
          break;
        }
        else if (suma1 >= 1600 && suma2 >= 1600)
        {
          motores(0, 0);
          delay(140);
          motores(115, 115);
          delay(200);
          break;
        }
        else
        {
          motores(-27, -33);
        }
        digitalWrite(13, LOW);
      }
    }

    motores(50, -100);//130,-140//90,-100////70,-120
    delay(9);
  }
}

void leer_color()
{
  //delay(50);
  tcs1.getRawData(&red1, &green1, &blue1, &clear);
  //delay(50);
  tcs2.getRawData(&red2, &green2, &blue2, &clear);

  suma1 = (red1 + green1 + blue1) * 0.5;
  suma2 = (red2 + green2 + blue2) * 0.5;

  return red1, green1, blue1, red2, green2, blue2  , suma1, suma2;
}
void QTR1A ()
{
  sx1 = analogRead(Sx1);
  sx2 = analogRead(Sx2);
}
