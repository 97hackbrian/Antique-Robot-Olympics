///PINES SENSORES SEGUIDORES
const int tcr1=11;
const int tcr2=12;
const int tcr3=13;
const int tcr4=14;
const int tcr5=15;
const int tcr6=16;
const int tcr7=17;
const int tcr8=18;
int sen1,sen2,sen3,sen4,sen5,sen6,sen7,sen8;
int sen1a,sen2a,sen3a,sen4a,sen5a,sen6a;
void setup()
{
  pinMode (tcr1,INPUT);
  pinMode (tcr2,INPUT);
  pinMode (tcr3,INPUT);
  pinMode (tcr4,INPUT); 
  pinMode (tcr5,INPUT);
  pinMode (tcr6,INPUT);
  pinMode (tcr7,INPUT);
  pinMode (tcr8,INPUT);
  Serial.begin(9600);
}
void loop ()
{
  sen1=digitalRead(tcr1);
  sen2=digitalRead(tcr2);
  sen3=digitalRead(tcr3);
  sen4=digitalRead(tcr4);
  sen5=digitalRead(tcr5);
  sen6=digitalRead(tcr6);
  sen7=digitalRead(tcr7);
  sen8=digitalRead(tcr8);
  sen1a=analogRead(tcr1);
  sen2a=analogRead(tcr2);
  sen3a=analogRead(tcr3);
  sen4a=analogRead(tcr4);
  sen5a=analogRead(tcr5);
  sen6a=analogRead(tcr6);
  Serial.print(sen1 );
  Serial.print(" ");
  Serial.print(sen2 );
   Serial.print(" ");
  Serial.print(sen3 );
   Serial.print(" ");
  Serial.print(sen4 );
   Serial.print(" ");
  Serial.print(sen5);
   Serial.print(" ");
  Serial.print(sen6);
   Serial.print(" ");
  Serial.print(sen7);
   Serial.print(" ");
  Serial.print(sen8);
  
 Serial.print(" "); 
 Serial.print(" "); 
 Serial.print(" ");
 Serial.print(" ");
 Serial.print(" ");
 Serial.print(" ");
 Serial.print(" ");
 Serial.print(" ");
 Serial.print(" ");
 Serial.print(" ");
 Serial.print(" ");
 Serial.print(" ");
 
  Serial.print(sen1a );
  Serial.print(" ");
  Serial.print(sen2a );
   Serial.print(" ");
  Serial.print(sen3a );
   Serial.print(" ");
  Serial.print(sen4a );
   Serial.print(" ");
  Serial.print(sen5a);
   Serial.print(" ");
  Serial.println(sen6a);
  delay (5);
}

