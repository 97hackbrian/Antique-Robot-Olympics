////////////////////////////
////////PID TUP ROTIC////////////
//////////////////////////
#include <QTRSensors.h>

//DECLARACION DE ENTRADAS///////////////
//BOTONES

/// Pines sharp de lectura
const int ir_sensor0 = A4;
long lectura, cm;                                                
///////////////////////////////////////////

const int btn1=12; /////pulsador de inicio
///const int btn2=4;
const int led=13; ///led de calibracion
                  ///se apaga cuando termina la calaibracion

int cruzero = 200;   //// velocidad maxima en linea recta del robot

/// SENSORES
int sen1m,sen2m,sen3m,sen4m,sen5m,sen6m,sen7m,sen8m;
int sen1,sen2,sen3,sen4,sen5,sen6,sen7,sen8;
///
///////variables control de casos/////////////7
int a=0;
int estado=0;
//////////////////////////////////////////////

////motor izquierda
int pwmb=9;
int bin2=6;
int bin1=7;

/////motor derecha
int pwma=3;
int ain2=5;
int ain1=4;


int P=0;
int I=0;
int D=0;
int LAST=0;
float vel;

#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   8     // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
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
  
  pinMode(led,OUTPUT);

 //Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  //delay(1500);
  digitalWrite(led, HIGH);
   for (int j = 0; j < 200; j++)  
 {                                 
                    
  qtrrc.calibrate();       

 }
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

    for(;;){ ///OJO este es un bucle infinito parecido al while 

    qtrrc.read(sensorValues);

    position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);///0 para pista blanca con linea negra
                                                                 ///1 para pista negra en linea blanca
                                                                                        
    P = ((position)-(3500)); /// ERROR
    
    mapeo();
    medir();

    if(cm>5)
    {
    ///////////////////////////////////////////////////////////////////////////
    D= (P - LAST); /// ERROR MENOS EL ERROR ANTERIOR , DERIVATIVO
    I=(P+ LAST); //INTEGRAL
   
vel=(P*0.003)+(D*0.100)+(I*0.00900);// para velocidad 120//////estaba en 0.0925
///vel=(P*0.06)+(D*0.260)+(I*0.00350);

///vel=(P*0.005)+(D*0.100)+(I*0.00097);//velocidad crucero 150 

//vel=(P*0.025)+(D*0.095)+(I*0.00065);// para velocidad 120//////estaba en 0.0925 ///para una velocidad crucero de 100 
///vel=(P*0.045)+(D*0.07)+(I*0.00065);// para velocidad 120//////estaba en 0.0925
//vel=(P*0.025)+(D*0.095)+(I*0); // PID
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


/////////////////////////////////TERMINA PID Y EMPIEZA CASOS///////////////////////////////////////////
/////FRENOS////
if(position<10)
{
 analogWrite(pwma,100); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,150); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///RETROCED
 digitalWrite(bin2,LOW);
 delay(10);
} 

if (position>6990)
{
 analogWrite(pwma,150); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,HIGH);   ///RETROCEDE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,HIGH);
 delay(10);
}

/////////////////////////
if((sen2==1)&&(sen3==1)&&(sen4==1)&&(sen5==1)&&(sen6==1)&&(sen7==1))
{
  estado ++;
  delay(50);
if (estado==1)
{
   izquierda();
   delay(300);
  //Serial.print("caso1");
}
if (estado==2)
{
  izquierda();
  delay(200);
  adelante();
  delay(300);
  //Serial.print("caso2");
}
if (estado==3)
{
  derecha();
  delay(200);
  adelante();
  delay(400);
  //Serial.print("caso3");
}
if(estado==4)
{
  adelante();
  delay(100);
  //Serial.print("caso4");
}
if (estado==5)
{
  izquierda();
  delay(250);
  //Serial.print("caso5");
}
}

  
} ///distance >
if((cm==8)||(cm==9))
{
parar();
delay(3000);
}
}////for
}///boton
}///loop

//////////////////FUNCIONES/////////////////////

void parar (void)
{
 analogWrite(pwma,0); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,0); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,LOW);   ///RETROCEDE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///FRENTE
 digitalWrite(bin2,LOW);
}
void adelante (void)
{
 analogWrite(pwma,100); // VELOCIDAD PARA EL MOTOR DERECHA
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDA
 digitalWrite(ain1,HIGH);   //MOTOR DERECHA
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///MOTOR IZQUIERDA
 digitalWrite(bin2,LOW);
 delay(5);
}
void derecha (void)
{
 analogWrite(pwma,150); // VELOCIDAD PARA EL MOTOR DERECHA
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDA
 digitalWrite(ain1,HIGH);   //MOTOR DERECHA
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///MOTOR IZQUIERDA
 digitalWrite(bin2,HIGH);
 delay(5);
}
void izquierda (void)
{
 analogWrite(pwma,150); // VELOCIDAD PARA EL MOTOR DERECHA
 analogWrite(pwmb,100); //  VELOCIDAD PARA EL MOTOR IZQUIERDA
 digitalWrite(ain1,LOW);   //MOTOR DERECHA
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///MOTOR IZQUIERDA
 digitalWrite(bin2,LOW);

  delay(5);
}


void medir (void)
{
  lectura = analogRead(ir_sensor0); // lectura del sensor 0
  cm = pow(3027.4 / lectura, 1.2134); // conversión a centímetros
  //Serial.print("fernando Sensor 0: ");
  //Serial.println(cm); // lectura del sensor 0
  delay(1); // tiempo de espera
  /*                                    
  Serial.println(cm);                              
  delay(1);
  */   
}
void mapeo(void)
{
//////////////////////////////LECTURA EN BRUTO DE LOS SENSORES///////////////////////////////////
qtrrc.read(sensorValues);
position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);///0 para pista blanca con linea negra
                                                           ///1 para pista negra en linea blanca
 sen1m=sensorValues[0];
 sen2m=sensorValues[1];
 sen3m=sensorValues[2];
 sen4m=sensorValues[3];
 sen5m=sensorValues[4];
 sen6m=sensorValues[5];
 sen7m=sensorValues[6];
 sen8m=sensorValues[7];

/////////MAPEADO DE LOS SENSORES DESPUES DE LA LECTURA AUTOMATICA/////////////////
 sen1=map(sen1m,10,990,0,1);
 sen2=map(sen2m,10,990,0,1);
 sen3=map(sen3m,10,990,0,1);
 sen4=map(sen4m,10,990,0,1);
 sen5=map(sen5m,10,990,0,1);
 sen6=map(sen6m,10,990,0,1);
 sen7=map(sen7m,10,990,0,1);
 sen8=map(sen8m,10,990,0,1);
 
////IMPRESION DE SENSORES EN EL MONITOR SERIAL///////
/*
Serial.print(sen1);
Serial.print("   ");
Serial.print(sen2);
Serial.print("   ");
Serial.print(sen3);
Serial.print("   ");
Serial.print(sen4);
Serial.print("   ");
Serial.print(sen5);
Serial.print("   ");
Serial.print(sen6);
Serial.print("   ");
Serial.print(sen7);
Serial.print("   ");
Serial.println(sen8);

///////////////////////////FIN DE PRUEBAS DE SENSORES//////////////////////////////////////     
*/
}

