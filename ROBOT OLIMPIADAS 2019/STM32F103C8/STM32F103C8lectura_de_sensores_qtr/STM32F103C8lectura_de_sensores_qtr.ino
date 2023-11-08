void setup() {
Serial.begin(9600);
}

void loop() {
  /*
Serial.print(digitalRead(PA0));
Serial.print('\t');
Serial.print(digitalRead(PA1));
Serial.print('\t');
Serial.print(digitalRead(PA2));
Serial.print('\t');
Serial.print(digitalRead(PA3));
Serial.print('\t');
Serial.print(digitalRead(PA4));
Serial.print('\t');
Serial.print(digitalRead(PA5));
Serial.print('\t');
Serial.print(digitalRead(PA6));
Serial.print('\t');
Serial.print(digitalRead(PA10));

Serial.println();
delay(7);
*/
//PINES EN ORDEN SI USAS EL ESQUEMA.
Serial.print(analogRead(PA0));
Serial.print('\t');
Serial.print(analogRead(PA1));
Serial.print('\t');
Serial.print(analogRead(PA2));
Serial.print('\t');
Serial.print(analogRead(PA3));
Serial.print('\t');
Serial.print(analogRead(PA4));
Serial.print('\t');
Serial.print(analogRead(PA5));
Serial.print('\t');
Serial.print(analogRead(PA6));
Serial.print('\t');
Serial.print(digitalRead(PA10));
Serial.println();
delay(7);

}
