#define BT1 28
int boton1 = 0;
int e = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BT1, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  while (true)
  {
    boton1 = digitalRead(BT1);
    if (boton1 == HIGH)
    {
      delay(500);
      e++;
    }

    if (analogRead(A0) <= 100 && analogRead(A1) <= 100 && analogRead(A2) <= 100 && analogRead(A3) <= 100 && analogRead(A4) <= 100 && analogRead(A5) <= 100 && analogRead(A6) <= 100 && analogRead(A7) <= 100 )
    {
      Serial.println(e);
      break;
    }
  }
  delay(99);
  digitalWrite(13, HIGH);
  delay(99);
  digitalWrite(13, LOW);
  delay(99);
  digitalWrite(13, HIGH);
  delay(99);
  digitalWrite(13, LOW);
  delay(705);

  for (int x = 0; x < e; x++)
  {
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
  }
  digitalWrite(13, LOW);

  delay(1100);
  digitalWrite(13, HIGH);
  delay(99);
  digitalWrite(13, LOW);
  delay(150);
  digitalWrite(13, HIGH);
  delay(99);
  digitalWrite(13, LOW);
}
void loop() {

}
