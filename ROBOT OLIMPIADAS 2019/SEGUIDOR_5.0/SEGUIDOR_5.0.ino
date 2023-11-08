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


Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin1, SCLpin1);

Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin2, SCLpin2);



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

int BT1 =PJ3;
int BT2 =PJ4;

#define Sx1 A8
#define Sx2 A9

int boton1, boton2;

int sx1, sx2;
int poslast;


float KP = 0.25; //0.25    0.55         1.81                    0.55              0.54
float KD = 2.4; //5.56    55             90      77              5.56           17.56
float Ki = 0.00; //0                 0.0037                   0.009v             0.008

int Velmax = 115;//180

int error1 = 0;
int error2 = 0;
int error3 = 0;
int error4 = 0;
int error5 = 0;
int error6 = 0;

void setup() {
  //Serial.begin(9600);
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

  delay(800);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  for (int i = 0; i < 350; i++)
  {
    qtra.calibrate();
  }
  digitalWrite(13, LOW);



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
  //PID();
  
  // qtra.readLine(sensorValues);

  if (analogRead(A1) >= 500 && analogRead(A2) >= 500 && analogRead(A3) >= 500 && analogRead(A4) >= 500 && analogRead(A5) >= 500 && analogRead(A6) >= 500)
  { motores(-9, -9);
  delay(60);
    motores(0, 0);
    delay(1000);

    motores(-23, -38);

    while (true)
    {
      digitalWrite(13, HIGH);
      leer_color();
      if (green1 <= 390 && green1 >= 115)
      {
        motores(0, 0);
        delay(500);
        motores(-40, 80);
        delay(400);
        break;
      }
      else if (green2 <= 390 && green2 >= 115)
      {
        motores(0, 0);
        delay(500);
        motores(80, -40);
        delay(400);
        break;
      }
      digitalWrite(13, LOW);
    }
  }

  frenos_contorno();

  PID();
}
void PID() {
  unsigned int position = qtra.readLine(sensorValues);
  proporcional =  3500 - ((int)position);
  /*if ( proporcional <= -Target )
    {
    setMotorLeft(0);
    freno(false,true,255);
    }
    else if ( proporcional >= Target )
    {
    setMotorRigh(0);
    freno(true,false,255);
    }*/

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
  if (position>6500)
  {
    motores(-120, 100);
    delay(9);
  }
  else if (position<500)
  {
    motores(100, -120);
    delay(9);
  }
}

void leer_color()
{
  delay(50);
  tcs1.getRawData(&red1, &green1, &blue1, &clear);
  delay(50);
  tcs2.getRawData(&red2, &green2, &blue2, &clear);
  return red1, green1, blue1, red2, green2, blue2;
}
void QTR1A ()
{
  sx1 = analogRead(Sx1);
  sx2 = analogRead(Sx2);
}
