////////////////////////////
////////velocista////////////
//////////////////////////
#include <QTRSensors.h>

//DECLARACION DE ENTRADAS///////////////
//BOTONES

const int btn1=12; /////pulsador de inicio
///const int btn2=4;
const int led=13; ///led de calibracion
                  ///se apaga cuando termina la calaibracion

int cruzero = 80;   //// velocidad maxima en linea recta del robot

////motor izquierda
int pwma=9;
int ain2=6;
int ain1=7;

/////motor derecha
int pwmb=3;
int bin2=5;
int bin1=4;

int P=0;
int I=0;
int D=0;
int LAST=0;
float vel;

#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   8     // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
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
  
  pinMode(led,OUTPUT);

  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(1500);
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

for(;;){ ///OJO este es un bucle infinito parecido al while true 

  qtrrc.read(sensorValues);

     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);///0 para pista blanca con linea negra
                                                                 ///1 para pista negra en linea blanca
                                                                                        
 P = ((position)-(3500)); /// ERROR
 
 ///D = (P - LAST); ///ERROR MENOS EL ERRROR ANTERIOR
 ///I = (P + LAST); ///
/////FRENOS////
if(P<-3500)
{
 analogWrite(pwma,120); // VELOCIDAD PARA EL MOTOR IZQUIERDO
  analogWrite(pwmb,180); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,LOW);  ///RETROCEDE
 digitalWrite(bin2,HIGH);
} 

else if (P>3500)
{
 analogWrite(pwma,135); // VELOCIDAD PARA EL MOTOR IZQUIERDO
 analogWrite(pwmb,90); //  VELOCIDAD PARA EL MOTOR DERECHO
 digitalWrite(ain1,LOW);   ///RETROCEDE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);

}
/////////////////////////
  else{
 D= (P - LAST); /// ERROR MENOS EL ERROR ANTERIOR , DERIVATIVO
   I=(P+ LAST); //INTEGRAL
   
   
//vel=(P*0.025)+(D*0.095)+(I*0); // PID
   
vel=(P*0.045)+(D*0.07)+(I*0.00065);// para velocidad 120//////estaba en 0.0925

//vel=(P*0.0428)+(D*0.085)+(I*0); //para velocidad 80 kd=0.06

///CRUZERO =VELOCIDAD PUNTA , V

    if(vel >cruzero) vel=cruzero;
    if(vel<-cruzero) vel=-cruzero;

  analogWrite(pwma,cruzero-vel); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwmb,cruzero+vel); //  VELOCIDAD PARA EL MOTOR IZQUIERDO

 digitalWrite(ain1,HIGH);   ///FRENTE
 digitalWrite(ain2,LOW);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 
LAST=P;
  }
}////BUCLE INFINITO
}///PRESIONO BOTON
}///FIN DEL LOOP


