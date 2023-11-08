#include <QTRSensors.h>

#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             A9  // emitter is controlled by digital pin 2


QTRSensorsAnalog qtra((unsigned char[]) {A6, A5, A8, A0, A2, A1, A4,A10}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


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


int ir_sensor1 = A11;
int ir_sensor2 = A13;
int ir_sensor3 = PJ3;//A15
int ir_sensor4 = A15;//PJ3

void setup()
{
  pinMode(s2_1, OUTPUT);  
  pinMode(s3_1, OUTPUT);  
  pinMode(out1, INPUT);  

  pinMode(s2_2, OUTPUT);  
  pinMode(s3_2, OUTPUT);  
  pinMode(out2, INPUT);  


  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}
void loop()
{
  int lectura1, cm1;
 
  lectura1 = analogRead(ir_sensor1); // lectura del sensor 0
  cm1 = pow(3027.4 / lectura1, 1.7); // 1.7 PARA 20CM A 250CM 
  Serial.print("Sensor 1:   ");
  Serial.print(cm1-1); // lectura del sensor 0 - 1 para ser mas precisos
  Serial.print("     ");
int lectura2, cm2;
 
  lectura2 = analogRead(ir_sensor2); // lectura del sensor 0
  cm2 = pow(3027.4 / lectura2, 1.200); // 497=5cm conversión a centímetros
  Serial.print("Sensor 2:   ");
  Serial.print(cm2-1); // lectura del sensor 0 - 1 para ser mas precisos

  Serial.print("     ");

  int lectura3, cm3;
 
  lectura3 = analogRead(ir_sensor3); // lectura del sensor 0
  cm3 = pow(3027.4 / lectura3, 1.200); // 497=5cm conversión a centímetros
  Serial.print("Sensor 3: ");
  Serial.print(cm3-1); // lectura del sensor 0 - 1 para ser mas precisos
  delay(1);

  Serial.print("     ");
  int lectura4, cm4;
 
  lectura4 = analogRead(ir_sensor4); // lectura del sensor 0
  cm4 = pow(3027.4 / lectura4, 1.7); // 1.7 PARA 20CM A 250CM 
  Serial.print("Sensor 4:  ");
  Serial.println(cm4-1); // lectura del sensor 0 - 1 para ser mas precisos
  delay(200);


  color1(); 
  Serial.print("R Intensidad:");  
  Serial.print(rojo1, DEC);  
  Serial.print(" G Intensidad: ");  
  Serial.print(verde1, DEC);  
  Serial.print(" B Intensidad : ");  
  Serial.print(azul1, DEC);  
  //Serial.println();  
  color1(); 
 if (rojo1 > azul1 && rojo1 < verde1 && verde1 >= 20&&(rojo1 >= 7&&rojo1 <= 10 ))
  {  
   Serial.print(" - (Color Rojo)");  

  }  
 
 else if (azul1 < rojo1 && azul1 < verde1&&( azul1 >= 11))   
  {  
   Serial.print(" - (Color Azul)");  

  }  

else if (verde1 < rojo1 && verde1 > azul1&&(verde1 >= 11))  
  {  
   Serial.print(" - (Color Verde)");  
  
  }  
 
else if(rojo1 < azul1 && verde1 < azul1&&azul1>rojo1&&verde1&&rojo1<14&&(rojo1 >= 10 && verde1 >= 10 ))
  {
   Serial.print(" - (Color amarillo)");  
  }
   
else if(rojo1 < 15 && verde1 < 15 && azul1 < 15)
  {
   Serial.print(" - (Color blanco)");
  }
    color1(); 

  Serial.print("      ");


  color2(); 
  Serial.print("R Intensidad2:");  
  Serial.print(rojo2, DEC);  
  Serial.print(" G Intensidad2: ");  
  Serial.print(verde2, DEC);  
  Serial.print(" B Intensidad2 : ");  
  Serial.print(azul2, DEC);  
  //Serial.println();  
  color2();
 if (rojo2 > azul2 && rojo2 < verde2 && verde2 > 14&&(rojo2 >= 4 ))
  {  
   Serial.print(" - (Color Rojo2)");  

  }  
 
 else if (azul2 < rojo2 && azul2 < verde2&&( azul2 >= 11))   
  {  
   Serial.print(" - (Color Azul2)");  

  }  
  
else if (verde2 < rojo2 && verde2 > azul2&&(verde2 >= 8&&verde2 <= 15))  
  {  
   Serial.print(" - (Color Verde2)");  
  
  }  

else if(rojo2 < azul2 && verde2 < azul2&&azul2>rojo2&&verde2&&rojo2<14&&(rojo2 >= 10 && verde2 >= 10 ))
  {
   Serial.print(" - (Color amarillo2)");  
  }
    
else if(rojo2 < 15 && verde2 < 15 && azul2 < 15)
  {
   Serial.print(" - (Color blanco2)");
  }

   Serial.println("  ");
   
  Serial.println("");
   delay(400);



   unsigned int position = qtra.readLine(sensorValues);
  
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  //Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position); // comment this line out if you are using raw values
  
  delay(500);
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


