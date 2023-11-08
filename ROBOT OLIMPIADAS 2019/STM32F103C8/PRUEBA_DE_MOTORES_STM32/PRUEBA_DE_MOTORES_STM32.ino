  

int IN1=PB13;
int IN2=PB12;
int pwma=PA8;


int IN3=PB14;
int IN4=PB15;
int pwmb=PA9;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin PB1 as an output.
  pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
      pinMode(pwma, PWM); 
        pinMode(IN3, OUTPUT);
          pinMode(IN4, OUTPUT);
            pinMode(pwmb, PWM);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  pwmWrite(pwma, 11000);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);             // wait for a second
  pwmWrite(pwmb, 10000);    // turn the LED off by making the voltage LOW
  delay(1300);  
  
  
  
  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  pwmWrite(pwma, 11000);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);             // wait for a second
  pwmWrite(pwmb, 10000);    // turn the LED off by making the voltage LOW
  delay(1300);    
}
