
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

int BT1 = PJ3;
int BT2 = PJ4;

#define Sx1 A8
#define Sx2 A9

int boton1, boton2;

int sx1, sx2;
int poslast;

float KP = 0.25; //0.25
float KD = 2.4; //2.4
float Ki = 0; //0

int Velmax = 115;//115

int error1 = 0;
int error2 = 0;
int error3 = 0;
int error4 = 0;
int error5 = 0;
int error6 = 0;

void setup() {
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
    if (boton1 == LOW)
    {
      break;
    }
  }
  /*
    delay(800);
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    for (int i = 0; i < 350; i++)
    {
      qtra.calibrate();
    }
    digitalWrite(13, LOW);


  */
  while (true)
  {
    boton2 = digitalRead(BT2);
    if (boton2 == LOW)
    {
      break;
    }
  }

  delay(400);
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
    motores(-120, 70);//-140,130//-100,90//
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

    motores(70, -120);//130,-140//90,-100
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
