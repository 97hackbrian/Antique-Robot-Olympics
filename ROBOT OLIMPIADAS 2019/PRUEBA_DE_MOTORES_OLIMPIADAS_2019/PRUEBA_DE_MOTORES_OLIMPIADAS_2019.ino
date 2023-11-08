


#define MOTORLEFT_DIR_A  11
#define MOTORLEFT_DIR_B  13
#define MOTORLEFT_PWM    8



#define MOTORRIGH_DIR_A  9
#define MOTORRIGH_DIR_B  10
#define MOTORRIGH_PWM    6
void setup() {
  pinMode(MOTORRIGH_DIR_A , OUTPUT);
  pinMode(MOTORRIGH_DIR_B , OUTPUT);
  pinMode(MOTORRIGH_PWM   , OUTPUT);
  pinMode(MOTORLEFT_DIR_A , OUTPUT);
  pinMode(MOTORLEFT_DIR_B , OUTPUT);
  pinMode(MOTORLEFT_PWM   , OUTPUT);
   motores(0, 0);
  delay(1009);

}


void setMotorLeft(int value)
{
  if ( value >= 0 )
  {
    digitalWrite(MOTORRIGH_DIR_A, HIGH);
    digitalWrite(MOTORRIGH_DIR_B, LOW);
  }
  else
  {
    digitalWrite(MOTORRIGH_DIR_A, LOW);
    digitalWrite(MOTORRIGH_DIR_B, HIGH);
    value *= -1;
  }
  analogWrite(MOTORRIGH_PWM, value);
}

void setMotorRigh(int value)
{
  if ( value >= 0 )
  {
    digitalWrite(MOTORLEFT_DIR_A, HIGH);
    digitalWrite(MOTORLEFT_DIR_B, LOW);
  }
  else
  {
    digitalWrite(MOTORLEFT_DIR_A, LOW);
    digitalWrite(MOTORLEFT_DIR_B, HIGH);
    value *= -1;
  }
  analogWrite(MOTORLEFT_PWM, value);
}

void motores(int left, int righ)
{
  //digitalWrite(STANDBY,HIGH);
  setMotorLeft(left);
  setMotorRigh(righ);
}

void freno(boolean left, boolean righ, int value)
{
  //  digitalWrite(STANDBY,HIGH);

  if ( left )
  {
    digitalWrite(MOTORRIGH_DIR_A, HIGH);
    digitalWrite(MOTORRIGH_DIR_B, HIGH);
    analogWrite (MOTORRIGH_PWM, value);
  }

  if ( righ )
  {
    digitalWrite(MOTORLEFT_DIR_A, HIGH);
    digitalWrite(MOTORLEFT_DIR_B, HIGH);
    analogWrite (MOTORLEFT_PWM, value);
  }
}
void loop() {
 


  motores(100, 100);
  delay(1999);

  motores(-100, -100);
  delay(1999);
  motores(-100, 100);
  delay(1999);
  motores(100, -100);
  delay(1999);
  
  motores(100, 0);
  delay(1999);
  
  motores(0, 100);
  delay(1999);
}
