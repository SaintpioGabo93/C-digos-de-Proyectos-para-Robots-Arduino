#include <L298N.h>

// Declaracion de Pines
const unsigned int m1 [] = {7,8,9};
const unsigned int m2 [] = {13,12,11};
char val;
// Creacion de objeto motor

L298N motor1 (m1[2],m1[0],m1[1]);
L298N motor2 (m2[2],m2[0],m2[1]);



void setup() {
  Serial.begin(9600);
  motor1.setSpeed(150);
  motor2.setSpeed(150);
}



void loop() {
  
  while (Serial.available() > 0)
  {
   val = Serial.read();
   Serial.println(val);
    }
  
  if( val == 'F')
  {
    motor1.forward();
    motor2.forward();
    } 

  else if (val == 'B')
  {
    motor1.backward();
    motor2.backward();    
    }
  
  else if(val == 'R')
  {
    motor1.forward();
    motor2.backward();            
    } 

  else if(val == 'L')
  {
    motor1.backward();
    motor2.forward();         
    }
    
  else if(val == 'S')
  {
    motor1.stop();
    motor2.stop();    
    }
  
}
