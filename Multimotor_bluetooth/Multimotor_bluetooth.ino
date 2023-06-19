//Librerías


#include <Servo.h>
#include <AFMotor.h>


//Variables

int angulo1 = 0;
int angulo2 = 0;
char val;

//Objetos Servo

Servo servo1;
Servo servo2;

// Objeto motor dc

AF_DCMotor motor1(1,MOTOR12_2KHZ);
AF_DCMotor motor2(2,MOTOR12_2KHZ);

void setup() {
  Serial.begin(9600);
  servo1.attach(10,600,2400);
  servo2.attach(9,600,2400);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  
}

void loop() {
  while(Serial.available() > 0) 
  {
    val = Serial.read();
    }
 
  if (val == 'a')
  {
    angulo1 = angulo1 + 5; //Se aumenta el angulo en 5 grados
    Serial.print(angulo1); // Se envía el valor puerto serial
    angulo1 = constrain(angulo1,0,180);
    servo1.write(angulo1);
    delay(100);
    }

  else if (val == 'b')
  {
    angulo1 = angulo1 - 5; //Se aumenta el angulo en 5 grados
    Serial.print(angulo1); // Se envía el valor puerto serial
    angulo1 = constrain(angulo1,0,180);
    servo1.write(angulo1);
    delay(100);     
    }


  else if (val == 'c')
  {
    angulo2 = angulo2 + 5; //Se aumenta el angulo en 5 grados
    Serial.print(angulo2); // Se envía el valor puerto serial
    angulo2 = constrain(angulo2,0,180);
    servo2.write(angulo2);
    delay(100);      
    }

  else if (val == 'c')
  {
    angulo2 = angulo2 - 5; //Se aumenta el angulo en 5 grados
    Serial.print(angulo2); // Se envía el valor puerto serial
    angulo2 = constrain(angulo2,0,180);
    servo2.write(angulo2);
    delay(100);     
    }            

  else if( val == 'd')
  {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    Serial.println(val);
    } 
    
  else if( val == 'f')
  {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    Serial.println(val);
    }  

 else if (val == "g")
 {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  Serial.print(val);
  }

 
}

 else if (val == "z")
 {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  Serial.print(val);
  }

 
}
