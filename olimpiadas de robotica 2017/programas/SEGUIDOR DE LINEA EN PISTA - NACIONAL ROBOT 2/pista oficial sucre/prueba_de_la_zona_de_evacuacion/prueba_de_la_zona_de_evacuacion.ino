#include <QTRSensors.h>
///probar break con los pines que no se usan en el caso
//DECLARACION DE ENTRADAS///////////////
//BOTONES
const int btn1=13; /////pulsador de inicio

const int led=13; ///led de calibracion
                  ///se apaga cuando termina la calaibracion
int servo=1;
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
int x=1;///total de ciclos
int r=0;///veces en que pasa casos negros en el primer while
int z=0;///veces en que pasa casos negros en el segundo while
int e=0; 
int c=0;
int b=0;//casos de obstaculos
int i=0;
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
  pinMode(servo,OUTPUT);
  pinMode(btn1,INPUT);
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
    digitalWrite(servo,LOW);
 while(x==1&&c==0)
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

if((sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(c==0))
{
 
//digitalWrite(13,HIGH);
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 analogWrite(pwma,120); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,120); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(200);
 while (true)
 {
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
   //if((sensorValues[4]==1000)||(sensorValues[3]==1000)&&(sensorValues[0]<=77))
  if((sensorValues[0]<=30)&&(sensorValues[3]==1000||sensorValues[4]==1000)&&(sensorValues[7]<=30))
  {
    c++;
    x++;
    break;
  }
 }
}
}
while(x==2&&c==1&&i==0)
{
  cruzero=100;
     qtrrc.read(sensorValues);

     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);///0 para pista blanca con linea negra
                                                                 ///1 para pista negra en linea blanca
                                                                                        
 P = ((position)-(3500)); /// ERROR
 
 ///D = (P - LAST); ///ERROR MENOS EL ERRROR ANTERIOR
 ///I = (P + LAST); ///

if((sensorValues[0]==1000)&&(sensorValues[5]<=75)&&(sensorValues[6]<=75)&&(sensorValues[7]<=75)&&(z==0))
{
  
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,90); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,90); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
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
if((sensorValues[0]<=75)&&(sensorValues[5]<=75)&&(sensorValues[6]<=75)&&(sensorValues[7]==1000)&&(z==0))
{
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 analogWrite(pwma,90); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,90); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
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

if((sensorValues[0]<=75)&&(sensorValues[6]==1000)&&(z==0))
{
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,90); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,0); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
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
if((sensorValues[7]<=75)&&(sensorValues[1]==1000)&&(z==0))
{
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,0); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,90); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
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

if((sensorValues[0]<=75)&&(sensorValues[5]==1000)&&(z==0))
{
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,120); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,50); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
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

if((sensorValues[7]<=75)&&(sensorValues[2]==1000)&&(z==0))
{
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,50); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,120); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
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
if((sensorValues[0]<=90)&&(sensorValues[1]<=90)&&(sensorValues[2]<=90)&&(sensorValues[3]<=90)&&(sensorValues[4]<=90)&&(sensorValues[5]<=90)&&(sensorValues[6]<=90)&&(sensorValues[7]<=90))
 {  
 i++;
}
}
while(x==2&&i>=1)
{
  

long lectura4, sharp4;
  lectura4 = analogRead(ir_sensor4); // lectura del sensor 0
  sharp4 = pow(3027.4 / lectura4, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);


  
  long lectura1, sharp1;
  lectura1 = analogRead(ir_sensor1); // lectura del sensor 0
  sharp1 = pow(3027.4 / lectura1, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
///CENTROC
if(sharp4<=13&&sharp4>=12)
{
  analogWrite(pwma,60); 
 analogWrite(pwmb,60); 
   digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
delay(1);
}

  lectura4 = analogRead(ir_sensor4); // lectura del sensor 0
  sharp4 = pow(3027.4 / lectura4, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
  
if(sharp4<12&&sharp4>=9)
{
  digitalWrite(13,HIGH);
  analogWrite(pwma,60); 
 analogWrite(pwmb,150); 
   digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
delay(1);
}
else
{
   digitalWrite(13,LOW);
}

  lectura4 = analogRead(ir_sensor4); // lectura del sensor 0
  sharp4 = pow(3027.4 / lectura4, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
if(sharp4<9&&sharp4>=6)
{
  digitalWrite(13,HIGH);
  analogWrite(pwma,50); 
 analogWrite(pwmb,160); 
   digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
delay(1);
}
else
{
   digitalWrite(13,LOW);
}

  lectura4 = analogRead(ir_sensor4); // lectura del sensor 0
  sharp4 = pow(3027.4 / lectura4, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);

if(sharp4>13&&sharp4<=17)
{
  analogWrite(pwma,150); 
 analogWrite(pwmb,60); 
   digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
delay(1);
}

  lectura4 = analogRead(ir_sensor4); // lectura del sensor 0
  sharp4 = pow(3027.4 / lectura4, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
if(sharp4>17&&sharp4<=23)
{
  analogWrite(pwma,160); 
 analogWrite(pwmb,50); 
   digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
delay(1);

}

 lectura1 = analogRead(ir_sensor1); // lectura del sensor 0
  sharp1 = pow(3027.4 / lectura1, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
  if(sharp1<=20)
  {
    analogWrite(pwma,0); 
 analogWrite(pwmb,0); 
   digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///RETROCED
 digitalWrite(bin2,LOW);
delay(2000);
    analogWrite(pwma,80); 
 analogWrite(pwmb,80); 
   digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
 delay(380);
     analogWrite(pwma,80); 
 analogWrite(pwmb,80); 
   digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
 delay(3000);
  }
}
}
  }
}


