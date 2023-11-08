/*#define MOTORLEFT_DIR_A  4
  #define MOTORLEFT_DIR_B  5
  #define MOTORLEFT_PWM    3
  #define MOTORRIGH_DIR_A  8
  #define MOTORRIGH_DIR_B  7
  #define MOTORRIGH_PWM    6
*/
#include <Wire.h>
#include "Adafruit_TCS34725softi2c.h"
#include <QTRSensors.h>

#define SDApin1 47
#define SCLpin1 48

#define SDApin2 45
#define SCLpin2 46




  uint16_t clear , red1, green1, blue1;
   uint16_t  red2, green2, blue2;

#define commonAnode true

Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin1, SCLpin1);

Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin2, SCLpin2);



#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             12  // emitter is controlled by digital pin 2

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


int poslast;


float KP = 0.2; //0.25    0.55         1.81                    0.55              0.54
float KD = 2.36; //5.56    55             90      77              5.56           17.56
float Ki = 0.00037; //0                 0.0008                   0.009v             0.008

int Velmax = 95;//180

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


  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 300; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration
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


  //frenos_contorno();
  PID();

qtra.readLine(sensorValues);


  if(sensorValues[1]>=800&&sensorValues[2]>=800&&sensorValues[3]>=800&&sensorValues[4]>=800&&sensorValues[5]>=800&&sensorValues[6]>=800)
{ motores(-9,-9);
  
    leer_color();
    
    motores(-35,-35);
    delay(135);
    
    motores(0,0);
    delay(100);
    
  if(green1<=360&&green1>=115)
  {
    motores(0,0);
    delay(100);
    motores(-50,80);
    delay(370);
  }
  motores(-5,-5);
  leer_color; if(green2<=360&&green2>=115)
  {
   
    motores(0,0);
    delay(100);
    motores(80,-50);
    delay(370);
  }
}

//PID();

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
  else if ( diferencial < -Velmax ) diferencial = -155;

  ( diferencial < 0 ) ? motores(Velmax + diferencial, Velmax) : motores(Velmax, Velmax - diferencial);
}




void frenos_contorno() {
  qtra.readLine(sensorValues);
  if (sensorValues[0]<=150&&sensorValues[1]>=450&&sensorValues[2]<=150&&sensorValues[5]>=450&&sensorValues[6]>=450&&sensorValues[7]>=450)
  {
    motores(90, -90);
    delay(350);
  }
 else if (sensorValues[7]<=150&&sensorValues[6]>=450&&sensorValues[5]<=150&&sensorValues[2]>=450&&sensorValues[1]>=450&&sensorValues[0]>=450)
  {
    motores(-90, 90);
    delay(350);
  }
}//150

void leer_color()
{ 
  tcs1.getRawData(&red1, &green1, &blue1, &clear);
  tcs2.getRawData(&red2, &green2, &blue2, &clear);
  return red1,green1,blue1,red2,green2,blue2;
}
