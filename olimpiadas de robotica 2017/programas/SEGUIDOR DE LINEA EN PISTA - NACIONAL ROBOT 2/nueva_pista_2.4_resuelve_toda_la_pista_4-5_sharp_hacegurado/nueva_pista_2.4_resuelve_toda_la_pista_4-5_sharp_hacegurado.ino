#include <QTRSensors.h>
///probar break con los pines que no se usan en el caso
//DECLARACION DE ENTRADAS///////////////
//BOTONES
const int btn1=12; /////pulsador de inicio

const int led=13; ///led de calibracion
                  ///se apaga cuando termina la calaibracion

int cruzero = 100;   //// velocidad maxima en linea recta del robot

////motor izquierda
int pwmb=9;
int bin2=6;
int bin1=7;

/////motor derecha
int pwma=3;
int ain2=5;
int ain1=4;

int ir_sharp1 = A4;


int P=0;
int I=0;
int D=0;
int LAST=0;
float vel;
int x=0;///total de ciclos
int r=0;///veces en que pasa casos negros en el primer while
int z=0;///veces en que pasa casos negros en el segundo while
int e=0; 
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

}
void loop()
{
  
  if (digitalRead(btn1)==1){

for(;;){ ///OJO este es un bucle infinito parecido al while true 
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

 vel=(P*0.034)+(D*0.100)+(I*0.00350);

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
    
if (position>6990&&r==0)
{
 analogWrite(pwma,150); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,HIGH);   ///RETROCEDE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 delay(30);
}
if(position<10&&r==0)
{
 analogWrite(pwma,100); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,155); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
 delay(30);
}

if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(r==0))
{
  //digitalWrite(13,HIGH);///ojo
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
if ((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]>=200)&&(sensorValues[6]<=150)&&(sensorValues[7]<=150)&&(r==1))
{
  //gira adelante
 analogWrite(pwma,100); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
 digitalWrite(bin2,LOW);
 delay(50);
  while(true)
{
   //gira a la izquierda
 analogWrite(pwma,105); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,90); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
   digitalWrite(bin2,LOW);
     qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
if((sensorValues[6]==1000)&&(sensorValues[0]<=20))
  { r++;
    break;
  }
}
} 

if((sensorValues[0]>=500)&&(sensorValues[1]>=500)&&(sensorValues[2]>=500)&&(sensorValues[3]>=500)&&(sensorValues[4]>=500)&&(sensorValues[5]>=500)&&(sensorValues[6]>=500)&&(sensorValues[7]>=500)&&(r==2))
{
  r++;
  ///ultimo negro
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,20); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(700);
  while(true) 
{
  ///ultimo negro
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,32); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
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
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delayMicroseconds(1);
}
 }
 while(x==0&&r==3)
 {
 
long lectura1, sharp1;

 
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

 vel=(P*0.040)+(D*0.100)+(I*0.00350);

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

digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,100); 
 analogWrite(pwmb,25);
  delay(900);

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
lectura1 = analogRead(ir_sharp1); // lectura del sensor 0
  sharp1 = pow(3027.4 / lectura1, 1.000)-1; // 497=5cm conversión a centímetros
  delayMicroseconds(1); // tiempo de espera 

if((sharp1==7||sharp1==8||sharp1==9||sharp1==10||sharp1==11&&z==1))
{

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
 analogWrite(pwma,32); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[0]==1000)||(sensorValues[1]==1000)||(sensorValues[2]==1000)&&(sensorValues[7]<=27))
  {
      z++;
    break;
  }
}
}


 LAST=P;
 }
   while(x==1&&z==2)
   {
  
cruzero=100;
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
   

 vel=(P*0.034)+(D*0.100)+(I*0.00350);

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
 
if (position>6990)
{
 analogWrite(pwma,125); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,150); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,HIGH);   ///RETROCEDE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 delay(25);
}
if(position<10)
{
 analogWrite(pwma,120); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,125); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
 delay(25);
}


if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(e==0))
{
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(15);
 while (true)
 {
qtrrc.read(sensorValues);
 position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
  if((sensorValues[0]<=27)&&(sensorValues[7]<=27))
  {
    e++;
    break;
  }
 }
}


if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000)&&(e==1))
{
        
  digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(100);
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
if ((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]>=200)&&(sensorValues[6]<=150)&&(sensorValues[7]<=150)&&(e==2))
{
    digitalWrite(13,HIGH);  
  //gira adelante

 //gira a la izquierda
 analogWrite(pwma,90); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,105); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCEDE
   digitalWrite(bin2,LOW);
   delay(240);
  while(true)
{
     qtrrc.read(sensorValues);
     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
if((sensorValues[6]==1000)&&(sensorValues[0]<=27))
  { e++;      
  digitalWrite(13,LOW); 
    break;
  }
}
} 
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

