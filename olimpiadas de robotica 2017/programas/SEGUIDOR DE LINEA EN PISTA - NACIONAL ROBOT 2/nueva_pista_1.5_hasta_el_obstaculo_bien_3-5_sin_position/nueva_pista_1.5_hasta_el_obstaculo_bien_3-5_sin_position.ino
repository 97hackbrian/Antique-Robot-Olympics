#include <QTRSensors.h>
///probar break con los pines que no se usan en el caso
//DECLARACION DE ENTRADAS///////////////
//BOTONES
const int btn1=12; /////pulsador de inicio

const int led=13; ///led de calibracion
                  ///se apaga cuando termina la calaibracion

int cruzero = 90;   //// velocidad maxima en linea recta del robot

////motor izquierda
int pwmb=9;
int bin2=6;
int bin1=7;

/////motor derecha
int pwma=3;
int ain2=5;
int ain1=4;

int ir_sharp1 = A6;
int lectura1, sharp1;

int P=0;
int I=0;
int D=0;
int LAST=0;
float vel;
int x=0;
int z=0;
int r=0;
#define NUM_SENSORS   8     // numero de sensorea
#define TIMEOUT       2500  // 2500 tiempo de encendido y apagado de los sensores//para calibrar
#define EMITTER_PIN   8     // emicion de la señal al pin LEDON del QTR

//numeracion de los pines a usar del sensor QTR(1-8)y uso de las variables de calibración
QTRSensorsRC qtrrc((unsigned char[]) {19, 2, 11, 17, 16, 10, 15, 14},
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
  pinMode(ir_sharp1,INPUT);
  
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

 pinMode(2,OUTPUT);
 digitalWrite(2,LOW);
}
void loop()
{
  
  if (digitalRead(btn1)==1){

for(;;){ ///OJO este es un bucle infinito parecido al while true 
 while(x==0&&r<2)
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
   
vel=(P*0.064)+(D*0.11)+(I*0.00560);// para velocidad 120//////estaba en 0.0925

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


if((sensorValues[0]<=20)&&(sensorValues[1]<=20)&&(sensorValues[3]>=500)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000))
{
  //gira a la derecha                                                                            
 analogWrite(pwma,85); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,110); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///RETROCEDE
 digitalWrite(bin2,HIGH);
  while(true)
{
     qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
 if((sensorValues[2]==1000||sensorValues[3]==1000)&&(sensorValues[7]<=20))
  {
    break;
  }
}
} 
if ((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]>=200)&&(sensorValues[6]<=20)&&(sensorValues[7]<=20))
{
  //gira a la izquierda
 analogWrite(pwma,105); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,90); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
   digitalWrite(bin2,LOW);
  while(true)
{
     qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
if((sensorValues[4]==1000||sensorValues[5]==1000)&&(sensorValues[0]<=20))
  {
    break;
  }
}
} 

if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(r==0))
{
  ///ojo
  digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,100); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  while(true) 
{
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[1]==1000||sensorValues[2]==1000)&&(sensorValues[7]<=20))
  {
    r++;
    break;
  }
}
}
if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(r==1))
{
  r++;
  digitalWrite(13,HIGH);
  ///ultimo negro
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,20); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(600);
  while(true) 
{
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[1]==1000||sensorValues[2]==1000)&&(sensorValues[7]<=20))
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
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delayMicroseconds(1);
}

LAST=P;
 }
 while(x==0&&r==2)
 {
  z=0;
lectura1 = analogRead(ir_sharp1); // lectura del sensor 0
  sharp1 = pow(3027.4 / lectura1, 1.000)-1; // 497=5cm conversión a centímetros
  delayMicroseconds(1); // tiempo de espera
 
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
   
vel=(P*0.050)+(D*0.02)+(I*0.00500);// para velocidad 120//////estaba en 0.0925

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

if((sensorValues[0]<=20)&&(sensorValues[1]<=20)&&(sensorValues[3]>=500)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000))
{
  //gira a la derecha                                                                            
 analogWrite(pwma,85); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,110); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///RETROCEDE
 digitalWrite(bin2,HIGH);
  while(true)
{
     qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
 if((sensorValues[2]==1000||sensorValues[3]==1000)&&(sensorValues[7]<=20))
  {
    break;
  }
}
} 
if ((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]>=500)&&(sensorValues[6]<=20)&&(sensorValues[7]<=20))
{
  //gira a la izquierda
 analogWrite(pwma,105); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,90); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
   digitalWrite(bin2,LOW);
  while(true)
{
     qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
if((sensorValues[4]==1000||sensorValues[5]==1000)&&(sensorValues[0]<=20))
  {
    break;
  }
}
} 
if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(z==0))
{
z++;
digitalWrite(13,HIGH);
digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,100); 
 analogWrite(pwmb,30); 
  delay(700);
 while (true)
 {
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
   if((sensorValues[1]==1000||sensorValues[2]==1000||sensorValues[3]==1000||sensorValues[4]==1000)&&(sensorValues[7]<=20))
  {
    break;
  }
 }
}
if((sharp1==14||sharp1==15||sharp1==16||sharp1==17)&&(sensorValues[3]==1000||sensorValues[4]==1000)&&(z==1))
{
  z++;
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(240);
  digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,0); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,0); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(300);



  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 analogWrite(pwma,120); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,120); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(270);
   digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,120); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,120); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(280);
  digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,130); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,130); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(237);
  x++;
// if((sensorValues[0]<=150)&&(sensorValues[1]<=150)&&(sensorValues[2]<=150)&&(sensorValues[3]<=150)&&(sensorValues[4]<=150)&&(sensorValues[5]<=150)&&(sensorValues[6]<=150)&&(sensorValues[7]<=150))
//  {

while(true)
{
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,28); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[0]==1000)||(sensorValues[1]==1000)||(sensorValues[2]==1000))
  {
    break;
  }
}
}


 LAST=P;
 }
   while(x==3)
   {
int e=0;   
cruzero=80;
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
   
vel=(P*0.065)+(D*0.04)+(I*0.00500);// para velocidad 120//////estaba en 0.0925

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

if((sensorValues[0]<=250)&&(sensorValues[1]<=250)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000))
{ 
  //gira a la derecha
 analogWrite(pwma,cruzero+vel); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,cruzero-vel-I); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///RETROCEDE
 digitalWrite(bin2,HIGH);
 delay(50);
} 

if ((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[6]<=250)&&(sensorValues[7]<=250))
{
  //gira a la izquierda
 analogWrite(pwma,cruzero+vel+I); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,cruzero-vel); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///RETROCEDE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 delay(50);
}



if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(e==0))
{
  e++;
 while (true)
 {
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[4]==1000)&&(sensorValues[5]==1000))
  {
    break;
  }
 }
}


if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(e==1))
{
  e++;
 while (true)
 {
  digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[4]==1000)||(sensorValues[5]==1000))
  {
    break;
  }
 }
}
 LAST=P;
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

