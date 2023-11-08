///
/// Utilización del sensor de distancia Sharp 2Y0A21
/// by RafaG
///<<<<<
 
// Pines de lectura

int ir_sensor1 = A11;
int ir_sensor2 = A13;
int ir_sensor3 = PJ3;//A15
int ir_sensor4 = A15;//PJ3
void setup()
{
  // inicia comunicaciones serie a 9600 bps
  Serial.begin(9600);
}
 
void loop()
{
  int lectura1, cm1;
 
  lectura1 = analogRead(ir_sensor1); // lectura del sensor 0
  cm1 = pow(3027.4 / lectura1, 1.7); // 1.7 PARA 20CM A 250CM 
  Serial.print("Sensor 1:   ");
  Serial.print(cm1-1); // lectura del sensor 0 - 1 para ser mas precisos
  Serial.print("     ");
int lectura2, cm2;
 
  lectura2 = analogRead(ir_sensor2); // lectura del sensor 0
  cm2 = pow(3027.4 / lectura2, 1.200); // 497=5cm conversión a centímetros
  Serial.print("Sensor 2:   ");
  Serial.print(cm2-1); // lectura del sensor 0 - 1 para ser mas precisos

  Serial.print("     ");

  int lectura3, cm3;
 
  lectura3 = analogRead(ir_sensor3); // lectura del sensor 0
  cm3 = pow(3027.4 / lectura3, 1.200); // 497=5cm conversión a centímetros
  Serial.print("Sensor 3: ");
  Serial.print(cm3-1); // lectura del sensor 0 - 1 para ser mas precisos
  delay(1);

  Serial.print("     ");
  int lectura4, cm4;
 
  lectura4 = analogRead(ir_sensor4); // lectura del sensor 0
  cm4 = pow(3027.4 / lectura4, 1.7); // 1.7 PARA 20CM A 250CM 
  Serial.print("Sensor 4:  ");
  Serial.println(cm4-1); // lectura del sensor 0 - 1 para ser mas precisos
  delay(1);
  /*
  if((cm1-1<=15)||(cm1-1<=15))
  {
    while (true)
    {
    Serial.println("lol");
    }
  }
  */
}
