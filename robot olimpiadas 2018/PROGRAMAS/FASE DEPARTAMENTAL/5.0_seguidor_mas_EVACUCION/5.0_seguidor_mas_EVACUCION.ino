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
float kp=0.05, kd=0.57, ki=0.0;           //ki=0.028
int vel=60;//50//35
float vel_der,vel_izq;
int vel_max=120;//70
int vel_min=-120;
//variables del boton
int lectura;
int boton = 48;
//COLOR1
const int s2_1 = 30;  
const int s3_1 =32;  
const int out1 = A3;   


// Variables  
int rojo1 = 0;  
int verde1 = 0;  
int azul1 = 0;  

//COLOR2
const int s2_2 = 34;  
const int s3_2 =36;  
const int out2 = A7;   


// Variables  
int rojo2 = 0;  
int verde2 = 0;  
int azul2 = 0;  


//SHARPs
  int lectura1, cm1;
int ir_sensor1 = A15;

   int lectura2, cm2;
int ir_sensor2 = A13;

  int lectura3, cm3;
int ir_sensor3 = A12;//A15

  int lectura4, cm4;
int ir_sensor4 = A11;//PJ3

//variables pista
int e=0;//toma de decisiones
int o=0;// objeto
int b=0;//blanco
//variables zona de evacuación
int x=0; //entrar a la zona de evacuación
int a=0;
int r=0;
int c=0;


int cm_der1=24;
int cm_der2=24;
int cm_adelan=45;
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

  //COLOR
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
      
unsigned int position = qtra.readLine(sensorValues);
error = position-3500;
P = kp*error;
D = kd*(error - error_Ant);
I = ki*(error + error_Ant);
vel_der = vel-P-D-I;
vel_izq = vel+P+D+I;

vel_der=constrain(vel_der,vel_min,vel_max);
vel_izq=constrain(vel_izq,vel_min,vel_max);
/*
qtra.read(sensorValues);      
if((sensorValues[0]<=50)&&(sensorValues[1]<=50)&&(sensorValues[2]<=50)&&(sensorValues[4]>=800)&&(sensorValues[5]>=800)&&(sensorValues[6]>=800)&&(sensorValues[7]>=800))
{
  digitalWrite(13,HIGH);
    mover_robot(0,130,0,130);
  delay(80);

  mover_robot(0,0,0,0);
  delay(300);  
  
  mover_robot(70,0,70,0);
  delay(140);
  mover_robot(55,0,0,80);
  delay(40);
  while(true)
  {
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);
    int position = qtra.readLine(sensorValues);

    qtra.read(sensorValues);
    if((sensorValues[0]<=50)&&((sensorValues[3]>=800)||(sensorValues[4]>=800))&&(sensorValues[7]<=50))
    {
  digitalWrite(13,LOW);
      break;
    }
  }
}
qtra.read(sensorValues);
if((sensorValues[0]>=800)&&(sensorValues[1]>=800)&&(sensorValues[2]>=800)&&(sensorValues[3]>=800)&&(sensorValues[5]<=50)&&(sensorValues[6]<=50)&&(sensorValues[7]<=50))
{
  digitalWrite(13,HIGH);
   mover_robot(0,130,0,130);
  delay(80);

  
  mover_robot(0,0,0,0);
  delay(300);  

  mover_robot(70,0,70,0);
  delay(140);
  mover_robot(0,80,55,0);
  delay(40);
  while(true)
  {
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);
    int position = qtra.readLine(sensorValues);

    qtra.read(sensorValues);
    if((sensorValues[0]<=50)&&((sensorValues[3]>=800)||(sensorValues[4]>=800))&&(sensorValues[7]<=50))
    {
  digitalWrite(13,LOW);
      break;
    }
  }
}
*/
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
//esquina derecha
if (position==7000)
{
mover_robot(0,0,0,60);
 delay(40);
}
//esquina izquierda
if(position==0)
{
mover_robot(0,60,0,0);
 delay(40);
}

//giro a la derecha e==0 se suma e++
if((sensorValues[0]>=990)&&(sensorValues[1]>=990)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]>=990)&&(sensorValues[7]>=990)&&(e==0))
{
  digitalWrite(13,HIGH);
  mover_robot(0,0,0,0);
  delay(300);  
  mover_robot(70,0,70,0);
  delay(30);
  mover_robot(40,0,0,60);
  delay(250);
  while(true)
  {
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);
    qtra.read(sensorValues);
    if((sensorValues[0]<=50)&&((sensorValues[3]>=800)||(sensorValues[4]>=800))&&(sensorValues[7]<=50))
    {
  digitalWrite(13,LOW);
      e++;//e=1;
      break;
    }
  }
}
//giro a la izquierda e==1 se suma e++ y o++
if((sensorValues[0]>=900)&&(sensorValues[1]>=900)&&(sensorValues[2]>=900)&&(sensorValues[3]>=900)&&(sensorValues[4]>=900)&&(sensorValues[5]>=900)&&(sensorValues[6]>=900)&&(sensorValues[7]>=900)&&(e==1))
{
  digitalWrite(13,HIGH);
  mover_robot(0,0,0,0);
  delay(200);  
  mover_robot(25,0,60,0);
  delay(250);

  while(true)
  {
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);
    qtra.read(sensorValues);
    if((sensorValues[0]<=50)&&((sensorValues[2]>=800)||(sensorValues[3]>=800)||(sensorValues[4]>=800))&&(sensorValues[7]<=50))
    {
  digitalWrite(13,LOW);
      e++;//e=2;
      o++;//o=1;
      break;
    }
  }
}

if(o==1)
{
   
    lectura2 = analogRead(ir_sensor2); // lectura del sensor 0
  cm2 = pow(3027.4 / lectura2, 1.200); // 497=5cm conversión a centímetros
}
if((cm2<=6)&&o==1)
{

  mover_robot(0,0,0,0);
    delay(400);

     mover_robot(0,50,0,50);
    delay(380);
  mover_robot(50,0,0,50);
  delay(250);
  mover_robot(50,0,50,0);
  delay(460);
  mover_robot(0,50,50,0);
  delay(250);
  mover_robot(45,0,50,0);
  delay(400);
  while(true)
  {
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);
    qtra.read(sensorValues);
    if((sensorValues[3]>=800)||(sensorValues[4]>=800||sensorValues[5]>=800))
  {

    mover_robot(60,0,0,30);
    delay(200);
      o++;//o=2;
      break;
    }
  }
}

  
//giro a la izquierda e==2 se suma e++ 
if((sensorValues[0]>=900)&&(sensorValues[1]>=900)&&(sensorValues[2]>=900)&&(sensorValues[3]>=900)&&(sensorValues[4]>=900)&&(sensorValues[5]>=900)&&(sensorValues[6]>=900)&&(sensorValues[7]>=900)&&(e==2))
{
  digitalWrite(13,HIGH);
  mover_robot(0,60,0,60);
  delay(60);  
  mover_robot(70,0,70,0);
  delay(10);
  
  mover_robot(0,60,40,0);
  delay(150);
  while(true)
  {
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);
    qtra.read(sensorValues);
    if((sensorValues[0]<=50)&&((sensorValues[3]>=800)||(sensorValues[4]>=800))&&(sensorValues[7]<=50))
    {
  digitalWrite(13,LOW);

   mover_robot(0,0,0,0);
  delay(100);
      e++;//e=3;
      b++;//b=1;
      break;
    }
  }
}

if((sensorValues[0]<=50)&&(sensorValues[1]<=50)&&(sensorValues[2]<=50)&&(sensorValues[3]<=50)&&(sensorValues[4]<=50)&&(sensorValues[5]<=50)&&(sensorValues[6]<=50)&&(sensorValues[7]<=50)&&(b==1))
{
  mover_robot(52,0,60,0);
  delay(370);
}
//esquina derecha
if (position==7000&&b==1)
{
mover_robot(0,0,0,60);
 delay(10);
}
//esquina izquierda
if(position==0&&b==1)
{
mover_robot(0,60,0,0);
 delay(10);
}

//esquina derecha
if ((sensorValues[0]<=50)&&(sensorValues[1]<=50)&&(sensorValues[6]>=800)&&(sensorValues[7]>=800)&&b==1)
{
mover_robot(40,0,0,50);
 delay(300);
}





//giro a la dercha tiempos e==3 se suma e++
if((sensorValues[1]>=900)&&(sensorValues[2]>=900)&&(sensorValues[3]>=900)&&(sensorValues[4]>=900)&&(sensorValues[5]>=900)&&(sensorValues[6]>=900)&&(e==3))
{
  digitalWrite(13,HIGH);
  
  mover_robot(0,0,0,0);
  delay(200);  
  mover_robot(50,0,28,0);
  delay(380);

  while(true)
  {
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);
    qtra.read(sensorValues);
    if((sensorValues[0]<=50)&&((sensorValues[3]>=800)||(sensorValues[4]>=800))&&(sensorValues[7]<=50))
    {
      b++;//b=2;
      e++;//e=4;
      break;
    }
  }
}



//giro a la izquierda e==4 se suma e++ 
if((sensorValues[0]>=900)&&(sensorValues[1]>=900)&&(sensorValues[2]>=900)&&(sensorValues[3]>=900)&&(sensorValues[4]>=900)&&(sensorValues[5]>=900)&&(sensorValues[6]>=900)&&(sensorValues[7]>=900)&&(e==4))
{
  digitalWrite(13,HIGH);
  mover_robot(0,0,0,0);
  delay(300);  
  mover_robot(40,0,35,0);
  delay(500);
  while(true)
  {
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);
    qtra.read(sensorValues);
    if((sensorValues[0]<=150)&&((sensorValues[3]>=600)||(sensorValues[4]>=600))&&(sensorValues[7]<=150))
    {
  digitalWrite(13,LOW);
    mover_robot(40,0,42,0);
  delay(100);
      e++;//e=5;
      x++;//X=1;
      break;
    }
  }
}
if(x==1)
{
  digitalWrite(s2_1, LOW);  
  digitalWrite(s3_1, LOW);  
  
  rojo1 = pulseIn(out1, digitalRead(out1) == HIGH ? LOW : HIGH);  
  digitalWrite(s3_1, HIGH);  
    
  azul1= pulseIn(out1, digitalRead(out1) == HIGH ? LOW : HIGH);  
  digitalWrite(s2_1, HIGH);  
  
  verde1 = pulseIn(out1, digitalRead(out1) == HIGH ? LOW : HIGH);  

  digitalWrite(s2_2, LOW);  
  digitalWrite(s3_2, LOW);  
  
  rojo2 = pulseIn(out2, digitalRead(out2) == HIGH ? LOW : HIGH);  
  digitalWrite(s3_2, HIGH);  
    
  azul2= pulseIn(out2, digitalRead(out2) == HIGH ? LOW : HIGH);  
  digitalWrite(s2_2, HIGH);  
  
  verde2 = pulseIn(out2, digitalRead(out2) == HIGH ? LOW : HIGH);  
  


 
}
if(((rojo1>=7&&rojo1<=10)&&(verde1>=17&&verde1<=21)&&(azul1==4||azul1==5))||((rojo2>=3&&rojo2<=6)&&(verde2>=7&&verde2<=12)&&(azul2==3||azul2==2))&&x==1)
{
 
   mover_robot(0,0,0,0);
   delay(400);
   x++;//x=2;
    mover_robot(40,0,50,0);
   delay(1200);
}

while(x==2&&a<=2)
{
    long lectura1, cm1;
    long lectura2, cm2;
    long lectura3, cm3;
    long lectura4, cm4;

    lectura2 = analogRead(ir_sensor2);
  cm2 = pow(3027.4 / lectura2, 1.200);

      lectura4 = analogRead(ir_sensor4);
  cm4 = pow(3027.4 / lectura4, 1.7);

   if(cm4==cm_der1)
   {
    mover_robot(50,0,50,0);
   }
    else if(cm4>cm_der1&&cm2>30)
    {
      mover_robot(50,0,0,0);
    
    }
    else if(cm4<cm_der1&&cm2>30)
    {
      mover_robot(0,0,50,0);
      
    }
        lectura2 = analogRead(ir_sensor2);
  cm2 = pow(3027.4 / lectura2, 1.200);
    if(cm2==20||cm2==21)
    {
      pinMode(43,OUTPUT);
      digitalWrite(43,HIGH);
      mover_robot(0,40,50,0);
      delay(850);
      while(true)
      {
            lectura2 = analogRead(ir_sensor2);
  cm2 = pow(3027.4 / lectura2, 1.200);

      lectura4 = analogRead(ir_sensor4);
  cm4 = pow(3027.4 / lectura4, 1.7);

    
        if(cm2>31)
        {
                digitalWrite(43,LOW);
                mover_robot(0,0,0,0);
                delay(1000);

          a++;
          break;
        }
       }
     }

}
while(a==3)
  {
  digitalWrite(13,HIGH);

 
long lectura1, cm1;
    long lectura2, cm2;
    long lectura3, cm3;
    long lectura4, cm4;
  

                lectura2 = analogRead(ir_sensor2);
  cm2 = pow(3027.4 / lectura2, 1.200);

      lectura4 = analogRead(ir_sensor4);
  cm4 = pow(3027.4 / lectura4, 1.7);


       if(cm4==cm_der2)
   {
    mover_robot(50,0,50,0);
   }

    
     else if(cm4>cm_der2)
    {
      mover_robot(50,0,0,0);
     
    }
    else if(cm4<cm_der2)
    {
      mover_robot(0,0,50,0);
   
    }
    
                  lectura2 = analogRead(ir_sensor2);
  cm2 = pow(3027.4 / lectura2, 1.200);
  
    if(cm2==cm_adelan)
    {
         digitalWrite(43,HIGH);

     mover_robot(0,0,0,0);
     delay(1000);
    if(r==0);
    {
      cm_der2=cm_der2+21;
    }
      mover_robot(0,40,50,0);
      delay(850);///980
      while(true)
      {

                          lectura2 = analogRead(ir_sensor2);
  cm2 = pow(3027.4 / lectura2, 1.200);

      lectura4 = analogRead(ir_sensor4);
  cm4 = pow(3027.4 / lectura4, 1.7);

        
        if(cm2>cm_adelan)
        {
      digitalWrite(43,LOW);

          r++;
          break;
        }
       }
     }
 
      if(r==4)
      {
        cm_der2 = cm_der2+15;
        cm_adelan=cm_adelan+15;
        if(cm3<10)
        {
          
          c++;
          mover_robot(0,0,0,0);
          delay(2000);
          
        }
      }
   lectura3 = analogRead(ir_sensor3);
  cm3 = pow(3027.4 / lectura3, 1.2);
    if(cm3<10)
        {
          
          //c++;
          mover_robot(0,0,0,0);
          delay(2000);
          mover_robot(110,0,110,0);
          delay(100);

          while(true)
          {
            
          
          mover_robot(35,0,67,0); 
            qtra.read(sensorValues);

if((sensorValues[0]>=900)&&(sensorValues[1]>=900)&&(sensorValues[2]>=900)&&(sensorValues[3]>=900)&&(sensorValues[4]>=900)&&(sensorValues[5]>=900)&&(sensorValues[6]>=900)&&(sensorValues[7]>=900))
{
  while(true)
  {
    mover_robot(0,0,0,0);
    delay(4000);
  }
}
          }
          
         
        }

        if(r==4)
        {
          r=0;
        }


  }


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
