#include <QTRSensors.h>

//DECLARACION DE ENTRADAS///////////////
//BOTONES

const int btn1=12; /////pulsador de inicio
///const int btn2=4;
const int led=13; ///led de calibracion
                  ///se apaga cuando termina la calaibracion

int cruzero = 80;   //// velocidad maxima en linea recta del robot

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

#define NUM_SENSORS   8     // numero de sensorea
#define TIMEOUT       2500  // 2500 tiempo de encendido y apagado de los sensores//para calibrar
#define EMITTER_PIN   8     // emicion de la señal al pin LEDON del QTR

//numeracion de los pines a usar del sensor QTR(1-8)y uso de las variables de calibración
QTRSensorsRC qtrrc((unsigned char[]) {19, 18, 11, 17, 16, 10, 15, 14},
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
 delay(40);
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
 delay(40);
}
else if((sensorValues[0]<=150)&&(sensorValues[1]<=150)&&(sensorValues[2]<=150)&&(sensorValues[3]<=150)&&(sensorValues[4]<=150)&&(sensorValues[5]<=150)&&(sensorValues[6]<=150)&&(sensorValues[7]<=150))
{
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(1);
}



if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000))
{
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,10); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,90); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(1000);
 digitalWrite(13,HIGH);
}

if((sharp1==4)||(sharp1==5)||(sharp1==6)||(sharp1==7)||(sharp1==8)||(sharp1==9))
{
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,80); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(230);
  digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,0); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,0); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(300);

  digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,130); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,130); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(250);
   digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,130); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,130); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(320);
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 analogWrite(pwma,130); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,130); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(190);
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,80); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,27); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
  delay(1500);
}
LAST=P;
}////BUCLE INFINITO
}///PRESIONO BOTON
}///FIN DEL LOOP

