/*


Sensor de color      Arduino
 -----------         --------
 VCC                  5V
 GND                  GND
 s2                   12
 s3                   11
 OUT                  10
*/
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
    
void setup()   
{  
  Serial.begin(9600); 

  pinMode(s2_1, OUTPUT);  
  pinMode(s3_1, OUTPUT);  
  pinMode(out1, INPUT);  

  
  pinMode(s2_2, OUTPUT);  
  pinMode(s3_2, OUTPUT);  
  pinMode(out2, INPUT);  

}  
    
void loop() 
{  
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

else if (verde1 < rojo1 && verde1 > azul1&&(verde1 >= 9&&verde1 <= 15))  
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
 if (rojo2 > azul2 && rojo2 < verde2 && verde2 > 13&&(rojo2 >= 4&&rojo2 <= 8 ))
  {  
   Serial.print(" - (Color Rojo2)");  

  }  
 
 else if (azul2 < rojo2 && azul2 < verde2&&( azul2 >= 11))   
  {  
   Serial.print(" - (Color Azul2)");  

  }  
  
else if (verde2 < rojo2 && verde2 > azul2&&(verde2 >= 7&&verde2 <= 13))  
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

