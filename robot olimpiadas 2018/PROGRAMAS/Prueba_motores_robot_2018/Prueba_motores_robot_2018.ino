int in1=8;
int in2=9;
int in3=6;
int in4=7;

void setup() {


    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

      analogWrite(in1,60);
      analogWrite(in2,0);
      analogWrite(in3,0);
      analogWrite(in4,0);
      delay(1000);
      analogWrite(in1,0);
      analogWrite(in2,60);
      analogWrite(in3,0);
      analogWrite(in4,0);
      delay(1000);
      analogWrite(in1,0);
      analogWrite(in2,0);
      analogWrite(in3,60);
      analogWrite(in4,0);
      delay(1000);
            analogWrite(in1,0);
      analogWrite(in2,0);
      analogWrite(in3,0);
      analogWrite(in4,60);
      delay(1000);

}
