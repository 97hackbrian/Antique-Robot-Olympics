#include <QTRSensors.h>
//codigo sensor
#define NUM_SENSORS   8     // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4   // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   A9     // emitter is controlled by digital pin 2
// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsAnalog qtra((unsigned char[]) {A6, A5, A8, A0, A2, A1, A4,A10}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
//codigo motores
int in1=8;
int in2=9;
int in3=6;
int in4=7;
//codigo para algoritmo
  int error=0, error_Ant=0; 
  float P=0, D=0, I=0;
  float kp=0.05, kd=0.6, ki=0.03;           //kp=0.03
  int vel=45;//50//35
  float vel_der,vel_izq;
  int vel_max=80;//70
  int vel_min=-80;
//variables del boton
int lectura;
int boton = 48;



const int s2_1 = 30;  
const int s3_1 =32;  
const int out1 = A3;   


// Variables  
int rojo1 = 0;  
int verde1 = 0;  
int azul1 = 0;  




const int s2_2 = 34;  
const int s3_2 =36;  
const int out2 = A7;   


// Variables  
int rojo2 = 0;  
int verde2 = 0;  
int azul2 = 0;  

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



    pinMode(s2_1, OUTPUT);  
  pinMode(s3_1, OUTPUT);  
  pinMode(out1, INPUT);  

  
  pinMode(s2_2, OUTPUT);  
  pinMode(s3_2, OUTPUT);  
  pinMode(out2, INPUT);


  

while(true){  //por siempre
  lectura = digitalRead(boton);
if(lectura==HIGH){
  delay(100);
  break;
  }
}
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
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
      qtra.read(sensorValues); 
      color1();
unsigned int position = qtra.readLine(sensorValues);
error = position-3500;
P = kp*error;
D = kd*(error - error_Ant);
I = ki*(error + error_Ant);
vel_der = vel-P-D-I;
vel_izq = vel+P+D+I;

vel_der=constrain(vel_der,vel_min,vel_max);
vel_izq=constrain(vel_izq,vel_min,vel_max);

   
if((sensorValues[0]<=50)&&(sensorValues[1]<=50)&&(sensorValues[2]<=50)&&(sensorValues[3]>=800)&&(sensorValues[4]>=800)&&(sensorValues[5]>=800)&&(sensorValues[6]>=800)&&(sensorValues[7]>=800))
{
  digitalWrite(13,HIGH);
    mover_robot(0,50,0,50);
  delay(80);

  mover_robot(0,0,0,0);
  delay(300);  
  
  mover_robot(50,0,50,0);
  delay(350);
    mover_robot(0,0,0,0);
  delay(300);  
  mover_robot(20,0,0,60);
  delay(50);//250
  while(true)
  {
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);
    int position = qtra.readLine(sensorValues);

    qtra.read(sensorValues);
    if((sensorValues[0]<=50)&&(sensorValues[1]<=50)&&((sensorValues[3]>=800)||(sensorValues[4]>=800))&&(sensorValues[6]<=50)&&(sensorValues[7]<=50))
    {
  digitalWrite(13,LOW);
      break;
    }
  }
}


if((sensorValues[0]>=800)&&(sensorValues[1]>=800)&&(sensorValues[2]>=800)&&(sensorValues[3]>=800)&&(sensorValues[4]>=800)&&(sensorValues[5]<=50)&&(sensorValues[6]<=50)&&(sensorValues[7]<=50))
{
  digitalWrite(13,HIGH);
   mover_robot(0,50,0,50);
  delay(80);

  mover_robot(0,0,0,0);
  delay(300);  
  
  mover_robot(50,0,50,0);
  delay(350);
    mover_robot(0,0,0,0);
  delay(300);  
  mover_robot(0,60,20,0);
  delay(50);
  while(true)
  {
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);
    int position = qtra.readLine(sensorValues);

    qtra.read(sensorValues);
    if((sensorValues[0]<=50)&&(sensorValues[1]<=50)&&((sensorValues[3]>=800)||(sensorValues[4]>=800))&&(sensorValues[6]<=50)&&(sensorValues[7]<=50))
    {
  digitalWrite(13,LOW);
      break;
    }
  }
}
//verde
if((rojo1>=18&&rojo1<=21)&&(verde1>=13&&verde1<=16)&&(azul1>=4&&azul1<=7))
{
  mover_robot(0,0,0,0);
  delay(2000);
}



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

void color1()  
{    
  digitalWrite(s2_1, LOW);  
  digitalWrite(s3_1, LOW);  
  
  rojo1 = pulseIn(out1, digitalRead(out1) == HIGH ? LOW : HIGH);  
  digitalWrite(s3_1, HIGH);  
    
  azul1= pulseIn(out1, digitalRead(out1) == HIGH ? LOW : HIGH);  
  digitalWrite(s2_1, HIGH);  
  
  verde1 = pulseIn(out1, digitalRead(out1) == HIGH ? LOW : HIGH);  
}
void color2()  
{    
  digitalWrite(s2_2, LOW);  
  digitalWrite(s3_2, LOW);  
  
  rojo2 = pulseIn(out2, digitalRead(out2) == HIGH ? LOW : HIGH);  
  digitalWrite(s3_2, HIGH);  
    
  azul2= pulseIn(out2, digitalRead(out2) == HIGH ? LOW : HIGH);  
  digitalWrite(s2_2, HIGH);  
  
  verde2 = pulseIn(out2, digitalRead(out2) == HIGH ? LOW : HIGH);  
}

