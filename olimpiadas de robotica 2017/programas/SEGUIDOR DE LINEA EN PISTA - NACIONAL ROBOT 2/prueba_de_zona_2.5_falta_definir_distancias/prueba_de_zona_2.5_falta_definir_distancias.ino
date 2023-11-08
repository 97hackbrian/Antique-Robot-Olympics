#include <QTRSensors.h>
///probar break con los pines que no se usan en el caso
//DECLARACION DE ENTRADAS///////////////
//BOTONES
const int btn1=13; /////pulsador de inicio

const int led=13; ///led de calibracion
                  ///se apaga cuando termina la calaibracion

int cruzeroiz = 134;   //// velocidad maxima en linea recta del robot
int cruzeroder = 120;
int cruzero = 110;
////motor izquierda
int pwmb=3;
int bin2=2;
int bin1=4;
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
int x=2;///total de ciclos
int r=0;///veces en que pasa casos negros en el primer while
int z=0;///veces en que pasa casos negros en el segundo while
int e=4; 
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
 while(e==4&&x==2)
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

 vel=(P*0.017)+(D*0.100)+(I*0.00270);

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

/// empiezo de la zona de evacuacion 
if((sensorValues[0]<=150)&&(sensorValues[1]<=150)&&(sensorValues[2]<=150)&&(sensorValues[3]<=150)&&(sensorValues[4]<=150)&&(sensorValues[5]<=150)&&(sensorValues[6]<=150)&&(sensorValues[7]<=150)&&(c==0))
{
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,110); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,110); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
while(true)
{
  
  long lectura1, sharp1;
  lectura1 = analogRead(ir_sensor1); // lectura del sensor 0
  sharp1 = pow(3027.4 / lectura1, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
  
  long lectura4, sharp4;
  lectura4 = analogRead(ir_sensor4); // lectura del sensor 0
  sharp4 = pow(3027.4 / lectura4, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
  if(sharp1>46&&sharp1<80)
  {
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,100); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,70); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(1);
  }
  if(sharp4<20)
  {
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,70); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(1);
  }
///cuando detecte al cubo
if(sharp1 >25 && sharp1<45)
 {
   digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,0); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,0); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(400);
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,85); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(390);
 c++;
 break;
 }
}
}
while(c==1&&x==2);
{

 long lectura3, sharp3;
  lectura3 = analogRead(ir_sensor3); // lectura del sensor 0
  sharp3 = pow(3027.4 / lectura3, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
if((sharp3>=6)&&(c==1))
{
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,110); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,110); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
while(true)
{
  
long lectura1, sharp1;
  lectura1 = analogRead(ir_sensor1); // lectura del sensor 0
  sharp1 = pow(3027.4 / lectura1, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
  
  long lectura4, sharp4;
  lectura4 = analogRead(ir_sensor4); // lectura del sensor 0
  sharp4 = pow(3027.4 / lectura4, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
  if(sharp1<80)
  {
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,100); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,70); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(1);
  }
  if(sharp4<20)
  {
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,70); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(1);
  }
 if(sharp3<6)
{
  c++;
  break;
}
}
}
long lectura2, sharp2;
  lectura2 = analogRead(ir_sensor2); // lectura del sensor 0
  sharp2 = pow(3027.4 / lectura2, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
if((sharp2>=15)&&(c==2))
{
  digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,110); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,110); //  VELOCIDAD PARA EL MOTOR IZQUIERDO  
 while(true)
 {
  long lectura1, sharp1;
  lectura1 = analogRead(ir_sensor1); // lectura del sensor 0
  sharp1 = pow(3027.4 / lectura1, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
  
  long lectura4, sharp4;
  lectura4 = analogRead(ir_sensor4); // lectura del sensor 0
  sharp4 = pow(3027.4 / lectura4, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
  if(sharp1<80)
  {
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,100); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,70); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(1);
  }
  if(sharp4<20)
  {
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,70); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(1);
  }
 
  long lectura2, sharp2;
  lectura2 = analogRead(ir_sensor2); // lectura del sensor 0
  sharp2 = pow(3027.4 / lectura2, 1.260); // 497=5cm conversión a centímetros
  delayMicroseconds(1);
    if(sharp2<15)
    {
      c++;
      digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 analogWrite(pwma,110); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,110); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(400);
      break;
    }
 }
 }
 qtrrc.read(sensorValues);

     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
     
 if((sensorValues[0]<=150)&&(sensorValues[1]<=150)&&(sensorValues[2]<=150)&&(sensorValues[3]<=150)&&(sensorValues[4]<=150)&&(sensorValues[5]<=150)&&(sensorValues[6]<=150)&&(sensorValues[7]<=150)&&(c==3))
{
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,110); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,110); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
while(true)
{
  qtrrc.read(sensorValues);

     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);

 if((sensorValues[0]==1000)&&(sensorValues[1]==1000)&&(sensorValues[2]==1000)&&(sensorValues[3]==1000)&&(sensorValues[4]==1000)&&(sensorValues[5]==1000)&&(sensorValues[6]==1000)&&(sensorValues[7]==1000))
 {
   digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,LOW);
 analogWrite(pwma,0); // VELOCIDAD PARA EL MOTOR DERECHO
 analogWrite(pwmb,0); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
 delay(4000);
 c++;
 break;
 }
}
}
}
 }
}

  }}
 








