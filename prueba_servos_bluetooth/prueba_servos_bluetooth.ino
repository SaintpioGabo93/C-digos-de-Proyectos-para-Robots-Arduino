//Librerías


#include <Servo.h>
#include <AFMotor.h>


//Variables

int angulo1 = 90;
char val;

//Objetos Servo

Servo servo1;
/*Servo servo2;*/

void setup() {
  Serial.begin(9600);
  servo1.attach(10,600,2400);
  
}

void loop() {
  while(Serial.available() > 0) 
  {
    val = Serial.read();
 
 
  if (val == 'd')
  {
    angulo1 = angulo1 + 5; //Se aumenta el angulo en 5 grados
    Serial.print(angulo1); // Se envía el valor puerto serial
    }

  else if (val == 'i')
  {
    angulo1 = angulo1 - 5; //Se aumenta el angulo en 5 grados
    Serial.print(angulo1); // Se envía el valor puerto serial
    }    
  angulo1 = constrain(angulo1,0,180);
  }
  servo1.write(angulo1);
  delay(100);
}
