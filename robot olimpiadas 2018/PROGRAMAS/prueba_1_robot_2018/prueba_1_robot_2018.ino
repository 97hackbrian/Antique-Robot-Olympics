#include <QTRSensors.h>
//codigo sensor
#define NUM_SENSORS   8     // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4   // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   A4     // emitter is controlled by digital pin 2
// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsAnalog qtra((unsigned char[]) {A10, A4, A1, A2, A0, A8, A5,A6}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
//codigo motores
int in1=6;
int in2=7;
int in3=8;
int in4=9;
//codigo para algoritmo
int error=0, error_Ant=0; 
float P=0, D=0, I=0;
float kp=0.0004, kd=0.81, ki=0.075;           //0.005//0.008kp=0.013  kd=0,03 o  0,02 o 0,06 
int vel=40;//50//35
float vel_der,vel_izq;
int vel_max=110;//70
int vel_min=-20;

//variables del boton
int lectura;
int boton = 48;
void setup() {
 
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(boton, INPUT);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW); 

while(true){  //por siempre
  lectura = digitalRead(boton);
if(lectura==HIGH){
  delay(100);
  break;
  }
}
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 200; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration
  
while(true){  //por siempre
  lectura = digitalRead(boton);
if(lectura==HIGH){
  delay(100);
  break;
  }
}
}
void loop() {
 unsigned int position = qtra.readLine(sensorValues);
error = position-3500;
P = kp*error;
D = kd*(error - error_Ant);
I = ki*(error + error_Ant);
vel_der = vel-P-D-I;
vel_izq = vel+P+D+I;
/*
////max
if(vel_der>vel_max)
{
  vel_der=vel_max;
}
if(vel_izq>vel_max)
{
  vel_izq=vel_max;
}
////////min
if(vel_der<vel_min)
{
  vel_der=vel_min;
}
if(vel_izq<vel_min)
{
  vel_izq=vel_min;
}
*/
/*
//der
 qtrrc.read(sensorValues);
   if((sensorValues[0]<=200)&&(sensorValues[1]<=200)&&(sensorValues[2]<=200)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000))
    {
analogWrite(in1,170);
analogWrite(in2,0);
analogWrite(in3,170);
analogWrite(in4,0);
  delay(300);
analogWrite(in1,170);
analogWrite(in2,0);
analogWrite(in3,0);
analogWrite(in4,170); 
        while(true)   
        {
             qtrrc.read(sensorValues);
               if(sensorValues[0]<=200&&sensorValues[1]<=200&&sensorValues[3]==1000&&sensorValues[4]==1000&&sensorValues[6]<=200&&sensorValues[7]<=200) 
            {
             break;   
            }  
        }                            
    }
//izq
qtrrc.read(sensorValues);
   if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[5]<=200)&&(sensorValues[6]<=200)&&(sensorValues[7]<=200))
    {
analogWrite(in1,170);
analogWrite(in2,0);
analogWrite(in3,170);
analogWrite(in4,0);
  delay(300);
analogWrite(in1,0);
analogWrite(in2,170);
analogWrite(in3,170);
analogWrite(in4,0); 
        while(true)   
        {
             qtrrc.read(sensorValues);
               if(sensorValues[0]<=200&&sensorValues[1]<=200&&sensorValues[3]==1000&&sensorValues[4]==1000&&sensorValues[6]<=200&&sensorValues[7]<=200) 
            {
             break;   
            }  
        }                            
    }
    
  */  
vel_der=constrain(vel_der,vel_min,vel_max);
vel_izq=constrain(vel_izq,vel_min,vel_max);
if(vel_der>=0&&vel_izq>=0)
{
mover_robot(vel_izq,0,vel_der,0);
}
else if(vel_der<=0)
{
  vel_der= vel_der * (-1);
  mover_robot(vel_izq,0,0,vel_der);
}
else if(vel_izq<=0)
{
  vel_izq= vel_izq * (-1);
  mover_robot(0,vel_izq,vel_der,0);
}
   
error_Ant=error;
}
void mover_robot(float vin1,float vin2,float vin3,float vin4)
{
 analogWrite(in1,vin1);
 analogWrite(in2,vin2);
 
 analogWrite(in3,vin3);
 analogWrite(in4,vin4);
}
