///PINES SENSORES SEGUIDORES
const int tcr1 = A0;
const int tcr2 = A1;
const int tcr3 = A2;
const int tcr4 = A3;
const int tcr5 = A4;
const int tcr6 = A5;
const int tcr7 = A6;
const int tcr8 = A7;

const int tcr9=A8;
const int tcr10=A9;

int sen1, sen2, sen3, sen4, sen5, sen6, sen7, sen8,sen9,sen10;
int sen1a, sen2a, sen3a, sen4a, sen5a, sen6a, sen7a, sen8a,sen9a,sen10a;

void setup()
{
  pinMode (tcr1, INPUT);
  pinMode (tcr2, INPUT);
  pinMode (tcr3, INPUT);
  pinMode (tcr4, INPUT);
  pinMode (tcr5, INPUT);
  pinMode (tcr6, INPUT);
  pinMode (tcr7, INPUT);
  pinMode (tcr8, INPUT);
    pinMode (tcr9, INPUT);
      pinMode (tcr10, INPUT);
  Serial.begin(9600);
}
void loop ()
{
  sen1 = digitalRead(tcr1);
  sen2 = digitalRead(tcr2);
  sen3 = digitalRead(tcr3);
  sen4 = digitalRead(tcr4);
  sen5 = digitalRead(tcr5);
  sen6 = digitalRead(tcr6);
  sen7 = digitalRead(tcr7);
  sen8 = digitalRead(tcr8);
  sen9 = digitalRead(tcr9);
  sen10 = digitalRead(tcr10);

  sen1a = analogRead(tcr1);
  sen2a = analogRead(tcr2);
  sen3a = analogRead(tcr3);
  sen4a = analogRead(tcr4);
  sen5a = analogRead(tcr5);
  sen6a = analogRead(tcr6);
  sen7a = analogRead(tcr7);
  sen8a = analogRead(tcr8);
  sen9a = analogRead(tcr9);
  sen10a = analogRead(tcr10);

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
  Serial.print(sen9);  
  Serial.print(" ");
  Serial.print(sen10);



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
  Serial.print(sen8a);
  
  Serial.print(" ");
  Serial.print(sen9a);
  
  Serial.print(" ");
  Serial.println(sen10a);
  delay (1);
}
