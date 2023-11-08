///PROGRAMA SEGUIDOR DE LINEA//
///maximo 215 pwm;
///PINES PUENTE H
const int in1=4;
const int in2=5;
const int ena=3;
const int in3=7;
const int in4=6;
const int emb=9;
const int p=12;
int pul;

///PINES SENSORES SEGUIDORES
const int tcr1=19;////sen1
const int tcr2=18;////sen2
const int tcr3=17;////sen3
const int tcr4=16;////sen4
const int tcr5=15;////sen5
const int tcr6=14;////sen5
int sen1,sen2,sen3,sen4,sen5,sen6;
/////VELOCIDADES DE LOS MOTORES SEGUN LOS CASOS

int velena=150;//motor izquierda MAS O MENOS PARA IR A LA DERECHA
int velemb=150;//motor derecha
int ademas=205;
int ademenos=170;
int ademasmenos=170;
int ademasmas=215;
void setup()
{
  pinMode (in1,OUTPUT);
  pinMode (in2,OUTPUT);
  pinMode (ena,OUTPUT);
  pinMode (in3,OUTPUT);
  pinMode (in4,OUTPUT);
  pinMode (emb,OUTPUT);
  pinMode (tcr1,INPUT);
  pinMode (tcr2,INPUT);
  pinMode (tcr3,INPUT);
  pinMode (tcr4,INPUT); 
  pinMode (tcr5,INPUT);
  pinMode (tcr6,INPUT);
}
void parar(void)
{
    
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    analogWrite(ena,0);
    ///MOTOR 2
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    analogWrite(emb,0);    
}
void adelante1(void)
{
  ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,195);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(emb,195);
    delayMicroseconds(1);
}
void adelanteder(void)
{
  ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,ademas);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(emb,ademenos);
    delayMicroseconds(1);
}
void adelanteizq(void)
{
  ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,ademenos);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(emb,ademas);
    delayMicroseconds(1);
}
void adelantedermas(void)
{
  ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,ademasmas);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(emb,ademasmenos);
    delayMicroseconds(1);
}
void adelanteizqmas(void)
{
  ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,ademasmenos);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(emb,ademasmas);
    delayMicroseconds(1);
}
void izquierda(void)
{
  ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    analogWrite(ena,velena);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(emb,velemb);
    delayMicroseconds(1);
  }
void derecha(void)
  {
     ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,velena);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    analogWrite(emb,velemb);
    delayMicroseconds(1);
    }
    void izquierdamas(void)
{
  ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    analogWrite(ena,80);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(emb,80);
    delayMicroseconds(1);
  }
void derechamas(void)
  {
     ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,80);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    analogWrite(emb,80);
    delayMicroseconds(1);
    }
    void izquierdaes(void)
{
  ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,80);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(emb,130);
    delayMicroseconds(1);
  }
void derechaes(void)
  {
     ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,130);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    analogWrite(emb,80);
    delayMicroseconds(1);
    }
void atras (void)
{
  ///MOTOR 1 IZQUIERDA
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    analogWrite(ena,velena);
    ///MOTOR 2 DERECHA
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    analogWrite(emb,velemb);
    delay(25);
  }

void loop()
{
  pul=digitalRead(p);
  if(pul==1)
  {
  while(true)
  {
  sen1=digitalRead(tcr1);
  sen2=digitalRead(tcr2);
  sen3=digitalRead(tcr3);
  sen4=digitalRead(tcr4);
  sen5=digitalRead(tcr5);
  sen6=digitalRead(tcr6);
    
  ///////////////////////////////////////////////////////////////
 ///VARIABLE ADELANTE 110011
  if ((sen1==0)&&(sen2==0)&&(sen3==1)&&(sen4==1)&&(sen5==0)&&(sen6==0))
  {
   adelante1();
  }
  if ((sen3==0)&&(sen4==1))
  {
   adelanteder();
  }
  if ((sen3==1)&&(sen4==0))
  {
   adelanteizq();
  }
  
  if ((sen2==0)&&(sen5==1))
  {
   adelantedermas();
  }
  if ((sen2==1)&&(sen5==0))
  {
   adelanteizqmas();
  }
  
  
  if ((sen1==0)&&(sen5==1)&&(sen6==1))
  {
   derechamas();
  }
  if ((sen1==1)&&(sen2==1)&&(sen6==0))
  {
   izquierdamas();
  }
  }
}
}
  
