//Librerías


#include <Servo.h>
#include <AFMotor.h>


//Variables

int angulo1 = 90;
int angulo2 = 90;
char val;

//Objetos Servo

Servo servo1;
Servo servo2;

// Objeto motor dc

AF_DCMotor motor1(1,MOTOR12_2KHZ);

void setup() {
  Serial.begin(9600);
  servo1.attach(10,600,2400);
  servo2.attach(9,600,2400);
  motor1.run(RELEASE);
  
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


  else if (val == 'e')
  {
    angulo2 = angulo2 + 5; //Se aumenta el angulo en 5 grados
    Serial.print(angulo2); // Se envía el valor puerto serial
    }

  else if (val == 'f')
  {
    angulo2 = angulo2 - 5; //Se aumenta el angulo en 5 grados
    Serial.print(angulo2); // Se envía el valor puerto serial
    }            
  angulo1 = constrain(angulo1,0,180);
  angulo2 = constrain(angulo2,0,180);
  }


  if( val == 'l')
  {
    motor1.run(FORWARD);
    } 


  else if( val == 'n')
  {
    motor1.run(BACKWARD);
    }  
  

  servo1.write(angulo1);
  delay(100);


  servo2.write(angulo2);
  delay(100);  
}
