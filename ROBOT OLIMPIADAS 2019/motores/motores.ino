const int Ain1=3;
const int Ain2=5;
const int Bin1=6;
const int Bin2=9;
void setup() {
  pinMode(Ain1,OUTPUT);
  pinMode(Ain2,OUTPUT);
  pinMode(Bin1,OUTPUT);
  pinMode(Bin2,OUTPUT);

  delay(200);
}

void loop() {
  while(true)
  {
  analogWrite(Ain1,50);
   analogWrite(Ain2,0);
    analogWrite(Bin1,50);
    analogWrite(Bin2,0);

delay(500);
     analogWrite(Ain1,0);
   analogWrite(Ain2,50);
    analogWrite(Bin1,0);
   analogWrite(Bin2,50);
     delay(500);
}
} 
