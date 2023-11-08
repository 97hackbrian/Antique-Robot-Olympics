#include <QTRSensors.h>
///probar break con los pines que no se usan en el caso
//DECLARACION DE ENTRADAS///////////////
//BOTONES
const int btn1=13; /////pulsador de inicio

const int led=13; ///led de calibracion
                  ///se apaga cuando termina la calaibracion

int cruzeroiz = 134;   //// velocidad maxima en linea recta del robot
int cruzeroder = 120;
int cruzero = 150;
////motor izquierda
int pwmb=3;
int bin2=4;
int bin1=2;
/////motor derecha
int pwma=6;
int ain2=7;
int ain1=5;
int ir_sensor1 = A4;
int ir_sensor2 = A5;
int ir_sensor3 = A6;
int ir_sensor4 = A7;

int P=0;
int I=0;
int D=0;
int LAST=0;
float vel;
int x=0;///total de ciclos
int r=0;///veces en que pasa casos negros en el primer while
int z=0;///veces en que pasa casos negros en el segundo while
int e=0; 
int c=0;
#define NUM_SENSORS   8     // numero de sensorea
#define TIMEOUT       2500  // 2500 tiempo de encendido y apagado de los sensores//para calibrar
#define EMITTER_PIN   8     // emicion de la señal al pin LEDON del QTR

//numeracion de los pines a usar del sensor QTR(1-8)y uso de las variables de calibración
QTRSensorsRC qtrrc((unsigned char[]) {16, 12, 11, 14, 15, 10, 9, 17},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

unsigned int position=0;

void setup()
{

  pinMode(btn1, INPUT);
    
  pinMode(pwma,OUTPUT);
  pinMode(ain1,OUTPUT);
  pinMode(ain2,OUTPUT);
  pinMode(pwmb,OUTPUT);
  pinMode(bin1,OUTPUT);
  pinMode(bin2,OUTPUT);
  
  
  pinMode(led,OUTPUT);
  // comienzo de la calibración de los sensores QTR
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(1500);
  digitalWrite(led, HIGH);
   for (int j = 0; j < 200; j++)  
 {                                 
                    
  qtrrc.calibrate();       

 }
 // se termina de calibrar
  digitalWrite(led, LOW); 
                                                                   
 digitalWrite(ain1,HIGH);
 digitalWrite(ain2,LOW);
 
 digitalWrite(bin1,HIGH);
 digitalWrite(bin2,LOW);
 
 analogWrite(pwma,0);
 analogWrite(pwmb,0);
  pinMode(13,INPUT);
}
void loop()
{
  
  if (digitalRead(btn1)==1){

for(;;){ ///OJO este es un bucle infinito parecido al while true 
   pinMode(13,OUTPUT);
    digitalWrite(13,LOW);
 while(x==0&&r<3)
 {
  /*
lectura1 = analogRead(ir_sharp1); // lectura del sensor 0
  sharp1 = pow(3027.4 / lectura1, 1.000)-1; // 497=5cm conversión a centímetros
  delayMicroseconds(1); // tiempo de espera
*/
  qtrrc.read(sensorValues);

     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);///0 para pista blanca con linea negra
                                                                 ///1 para pista negra en linea blanca
                                                                                        
 P = ((position)-(3500)); /// ERROR
 
 ///D = (P - LAST); ///ERROR MENOS EL ERRROR ANTERIOR
 ///I = (P + LAST); ///


/////////////////////////

 D= (P - LAST); /// ERROR MENOS EL ERROR ANTERIOR , DERIVATIVO
   I=(P+ LAST); //INTEGRAL
   
   
//vel=(P*0.025)+(D*0.095)+(I*0); // PID
   
//vel=(P*0.064)+(D*0.11)+(I*0.00560);// para velocidad 120//////estaba en 0.0925

 vel=(P*0.015)+(D*0.100)+(I*0.00200);
 
//vel=(P*0.034)+(D*0.100)+(I*0.00350);

//vel=(P*0.0428)+(D*0.085)+(I*0); //para velocidad 80 kd=0.06

///CRUZERO =VELOCIDAD PUNTA , V

    if(vel >cruzero) vel=cruzero;
    if(vel<-cruzero) vel=-cruzero;

  analogWrite(pwma,cruzero+vel); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,cruzero-vel); //  VELOCIDAD PARA EL MOTOR IZQUIERDO

 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
    LAST=P;
    
if (position==7000&&r==0)
{
 analogWrite(pwma,140); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,140); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,HIGH);   ///RETROCEDE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 delay(40);
 //digitalWrite(13,HIGH);
}
/*
else
{
   digitalWrite(13,LOW);
}
*/
if(position==0&&r==0)
{
 analogWrite(pwma,140); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,140); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
 delay(40);
  //digitalWrite(13,HIGH);
}
/*
else 
{
   digitalWrite(13,HIGH);
}
*/
if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(r==0))
{
 //digitalWrite(13,HIGH);///ojo
  digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,140); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,140); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(200);
  while(true) 
{
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[3]==1000||sensorValues[4]==1000)&&(sensorValues[7]<=20))
  {
    r++;
    break;
  }
}
}
if ((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[7]<=65)&&(r==1))
{
 ///digitalWrite(13,HIGH);
  //gira adelante
 analogWrite(pwma,140); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,140); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
 digitalWrite(bin2,LOW);
 delay(45);
  while(true)
{
   //gira a la izquierda
 analogWrite(pwma,104); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,110); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
   digitalWrite(bin2,LOW);
     qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
if((sensorValues[4]==1000)&&(sensorValues[0]<=20))
  { r++;
    break;
  }
}
} 

if((sensorValues[0]>=500)&&(sensorValues[1]>=500)&&(sensorValues[2]>=500)&&(sensorValues[3]>=500)&&(sensorValues[4]>=500)&&(sensorValues[5]>=500)&&(sensorValues[6]>=500)&&(sensorValues[7]>=500)&&(r==2))
{
  r++;
   //digitalWrite(13,HIGH);
  ///ultimo negro
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,65); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,190); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(500);
  while(true) 
{
  ///ultimo negro
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,65); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,180); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[2]==1000||sensorValues[3]==1000||sensorValues[4]==1000||sensorValues[5]==1000||sensorValues[6]==1000)&&(sensorValues[7]<=20))
  {
    break;
  }
}
}
 if((sensorValues[0]<=150)&&(sensorValues[1]<=150)&&(sensorValues[2]<=150)&&(sensorValues[3]<=150)&&(sensorValues[4]<=150)&&(sensorValues[5]<=150)&&(sensorValues[6]<=150)&&(sensorValues[7]<=150)&&(r==1))
{
  
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,130); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,130); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delayMicroseconds(1);
}
if((sensorValues[0]<=75)&&(sensorValues[5]<=75)&&(sensorValues[6]<=75)&&(sensorValues[7]==1000)&&(r==1))
{
  
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 analogWrite(pwma,150); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,130); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 while(true)
 {
  qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[3]==1000)||(sensorValues[4]==1000))
  {
    break;
  }
 }
}
if((sensorValues[7]<=75)&&(sensorValues[2]<=75)&&(sensorValues[1]<=75)&&(sensorValues[0]==1000)&&(r==1))
{
  
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,60); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,200); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 while(true)
 {
  qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[3]==1000)||(sensorValues[4]==1000))
  {
    break;
  }
 }
}
 }
 while(x==0&&r==3)
 {
  cruzero=130; 
  qtrrc.read(sensorValues);

     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);///0 para pista blanca con linea negra
                                                                 ///1 para pista negra en linea blanca
                                                                                        
 P = ((position)-(3500)); /// ERROR
 
 ///D = (P - LAST); ///ERROR MENOS EL ERRROR ANTERIOR
 ///I = (P + LAST); ///


/////////////////////////

 D= (P - LAST); /// ERROR MENOS EL ERROR ANTERIOR , DERIVATIVO
   I=(P+ LAST); //INTEGRAL
   
   
//vel=(P*0.025)+(D*0.095)+(I*0); // PID

 vel=(P*0.017)+(D*0.050)+(I*0.00270);

//vel=(P*0.0428)+(D*0.085)+(I*0); //para velocidad 80 kd=0.06

///CRUZERO =VELOCIDAD PUNTA , V

    if(vel >cruzero) vel=cruzeroder;
    if(vel<-cruzero) vel=-cruzeroiz;

  analogWrite(pwma,cruzeroder+vel); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,cruzeroiz-vel); //  VELOCIDAD PARA EL MOTOR IZQUIERDO

 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
    LAST=P;


if((sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(z==0))
{

digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,140); 
 analogWrite(pwmb,60);
  delay(600);

   while(true)
   {
    qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
if((sensorValues[3]==1000||sensorValues[4]==1000)&&(sensorValues[0]<=28||sensorValues[0]<=28))///0 y 7
  {
    z++;
    break;
  }
}
} 
if((position>6000)&&(z==1))
{
 digitalWrite(13,HIGH);
 analogWrite(pwma,130); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,170); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,HIGH);   ///RETROCEDE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 delay(60);

 while(true)
 {
   qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
     if((sensorValues[1]==1000)||(sensorValues[2]==1000))
     {
       digitalWrite(13,LOW);
      break;
     }
 }
}
if(position<100&&z==1)
{
 analogWrite(pwma,170); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,110); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
 delay(30);
  //digitalWrite(13,HIGH);
while(true)
 {
   qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
     if((sensorValues[3]==1000)||(sensorValues[4]==1000))
     {
      break;
     }
 }
}


if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(z==1))
{
 z++;
digitalWrite(13,HIGH);
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,120); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,120); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(15);
 while (true)
 {
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[0]<=27)&&(sensorValues[7]<=27))
  {
    x++;
    break;
  }
 }
}



 LAST=P;
 }
   while(x==1&&z==2)
   {
  
cruzero=130;
  qtrrc.read(sensorValues);

     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);///0 para pista blanca con linea negra
                                                                 ///1 para pista negra en linea blanca
                                                                              
 P = ((position)-(3500)); /// ERROR
 
 ///D = (P - LAST); ///ERROR MENOS EL ERRROR ANTERIOR
 ///I = (P + LAST); ///


/////////////////////////

 D= (P - LAST); /// ERROR MENOS EL ERROR ANTERIOR , DERIVATIVO
   I=(P+ LAST); //INTEGRAL
   
   
//vel=(P*0.025)+(D*0.095)+(I*0); // PID
   
 vel=(P*0.015)+(D*0.100)+(I*0.00200);

//vel=(P*0.0428)+(D*0.085)+(I*0); //para velocidad 80 kd=0.06

///CRUZERO =VELOCIDAD PUNTA , V

    if(vel >cruzero) vel=cruzero;
    if(vel<-cruzero) vel=-cruzero;

  analogWrite(pwma,cruzero+vel); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,cruzero-vel); //  VELOCIDAD PARA EL MOTOR IZQUIERDO

 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
    LAST=P;
 

if (position==7000&&e==0)
{
 analogWrite(pwma,130); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,170); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,HIGH);   ///RETROCEDE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 delay(80);
 //digitalWrite(13,HIGH);
}
/*
else
{
   digitalWrite(13,LOW);
}
*/
if(position==0&&e==0)
{
 analogWrite(pwma,170); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,130); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
 delay(80);
  //digitalWrite(13,HIGH);
}
/*
else 
{
   digitalWrite(13,HIGH);
}
*/


if((sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(e==0))
{
   
  digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,120); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,140); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(80);
 while (true)
 {
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[1]==1000||sensorValues[2]==1000)&&(sensorValues[7]<=20))
  {
      e++;
 
    break;
  }
 }
}
if((position<10)&&(e==1))
{
    
  //gira adelante

 //gira a la izquierda
 analogWrite(pwma,140); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,140); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
   digitalWrite(bin2,LOW);
   delay(40);
  while(true)
{
     qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
if((sensorValues[6]==1000)&&(sensorValues[0]<=27))
  { e++;      

    break;
  }
}
}
if((position<10)&&(e==2))
{
  
  //gira adelante

 //gira a la izquierda
 analogWrite(pwma,140); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,140); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
   digitalWrite(bin2,LOW);
   delay(40);
  while(true)
{
     qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
if((sensorValues[6]==1000)&&(sensorValues[0]<=27))
  { e++;      
    break;
    cruzero=60;
  }
}
}

  
if ((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]>=200)&&(sensorValues[6]<=150)&&(sensorValues[7]<=150)&&(e==3))
{
    //digitalWrite(13,HIGH);  
  //gira adelante

 //gira a la izquierda
 analogWrite(pwma,130); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,120); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
   digitalWrite(bin2,LOW);
   delay(80);
  while(true)
{
     qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
if((sensorValues[6]==1000)&&(sensorValues[0]<=90))
  { e++;      
    break;
  }
}
}
if ((sensorValues[0]<=27)&&(sensorValues[1]<=27)&&(sensorValues[2]<=27)&&(sensorValues[3]<=27)&&(sensorValues[4]<=27)&&(sensorValues[5]<=27)&&(sensorValues[6]<=27)&&(sensorValues[7]<=27)&&(e==4))
{
  
   analogWrite(pwma,50); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,60); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
   digitalWrite(bin2,LOW);
delay(1000);

while(true)
{
  long lectura3, cm3;
 
  lectura3 = analogRead(ir_sensor3); // lectura del sensor 0
  cm3 = pow(3027.4 / lectura3, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
  if(cm3 >25 && cm3 <45)
  {
     analogWrite(pwma,0); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,0); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///RETROCEDE
   digitalWrite(bin2,LOW);

    e++;
    x++;
    break;
  }
}
}
   }
 while(c<=3&&x==2&&e==5)
 {
qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);

long lectura3, cm3;
 
  lectura3 = analogRead(ir_sensor3); // lectura del sensor 0
  cm3 = pow(3027.4 / lectura3, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
if(cm3 >25 && cm3 <45&&c==0)
{
   analogWrite(pwma,76); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
   digitalWrite(bin2,LOW);

while(true)
{
 long lectura2, cm2;
 
  lectura2 = analogRead(ir_sensor2); // lectura del sensor 0
  cm2 = pow(3027.4 / lectura2, 1.000); // 497=5cm conversión a centímetros
  delayMicroseconds(1);

   if(cm2>=5)
  {
    c++;
    break;
  }
}
}
long lectura2, cm2;
 
  lectura2 = analogRead(ir_sensor2); // lectura del sensor 0
  cm2 = pow(3027.4 / lectura2, 1.000); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
if(cm2>=5&&c==1)
  {
  
   digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,0); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,0); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(400);
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
   
while(true)
{
  long lectura2, cm2;
 
  lectura2 = analogRead(ir_sensor2); // lectura del sensor 0
  cm2 = pow(3027.4 / lectura2, 1.000); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
  if(cm2<=5)
  {
    c++;
       digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(800);
 
    break;
  }
}
 }
  digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(80);
digitalWrite(13,HIGH);
delay(60);
digitalWrite(13,LOW);
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,46); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(3700);
digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,0); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,0); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(5000);
 }
/*
if ((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[3]<=250)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000))
{
  //gira a la izquierda
 analogWrite(pwma,cruzero2+vel+I); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,cruzero2-vel); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///RETROCEDE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 delay(200);
 digitalWrite(13,HIGH);
}
 else
 {
  digitalWrite(13,LOW);
 }
 */

}////BUCLE INFINITO
}///PRESIONO BOTON
}///FIN DEL LOOP

