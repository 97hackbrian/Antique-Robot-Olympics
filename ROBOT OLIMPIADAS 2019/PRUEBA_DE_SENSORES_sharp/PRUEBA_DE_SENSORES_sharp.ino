///PINES SENSORES SEGUIDORES
const int tcr1 = A15;
const int tcr2 = A14;
const int tcr3 = A13;
const int tcr4 = A12;
const int tcr5 = A11;


int sen1, sen2, sen3, sen4, sen5, sen6, sen7, sen8;
int sen1a, sen2a, sen3a, sen4a, sen5a, sen6a, sen7a, sen8a;
boolean senb4a, senb5a;
void setup()
{
  pinMode (tcr1, INPUT);
  pinMode (tcr2, INPUT);
  pinMode (tcr3, INPUT);
  pinMode (tcr4, INPUT);
  pinMode (tcr5, INPUT);

  Serial.begin(9600);
}
void loop ()
{
  sen1 = digitalRead(tcr1);
  sen2 = digitalRead(tcr2);
  sen3 = digitalRead(tcr3);
  sen4 = digitalRead(tcr4);
  sen5 = digitalRead(tcr5);


  sen1a = analogRead(tcr1);
  sen2a = analogRead(tcr2);
  sen3a = analogRead(tcr3);
  sen4a = analogRead(tcr4);
  sen5a = analogRead(tcr5);


  //senb4a = map(sen4a, 1, 287, 0, 1);//287//187mucha presición para codigos avanzados//400como tubiera que ser
  //senb5a = map(sen5a, 1, 287, 0, 1);//287//187mucha presición para codigos avanzados//400como tubiera que ser
  //247para ir mas recto y que solo avance en liena recta
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
  Serial.print(sen6a);
  Serial.print(" ");
  Serial.print(sen7a);
  Serial.print(" ");
  Serial.println(sen8a);
  delay (1);
}
