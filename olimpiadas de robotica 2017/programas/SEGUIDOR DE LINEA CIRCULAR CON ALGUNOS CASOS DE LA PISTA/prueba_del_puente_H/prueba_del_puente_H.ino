//prueba del puente H polulo 2017
////////////////////MAXIMO DE PWM 215//////////////
const int in1=4;
const int in2=5;
const int ena=3;
const int in3=7;
const int in4=6;
const int emb=9;
const int pul=12;
int p;
void adelante ()
{
  //5,15=200 pwm
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena,215);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(emb,215);
}
void apagar ()
{
  //5,15=200 pwm
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(ena,0);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  analogWrite(emb,0);
}
void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(emb,OUTPUT);
  pinMode(pul,INPUT);
}
void loop() {
  p=digitalRead(pul);
  if(p==1)
  {
  adelante ();
  delay(1000);
  apagar ();
  delay(3000);
  }
    }
