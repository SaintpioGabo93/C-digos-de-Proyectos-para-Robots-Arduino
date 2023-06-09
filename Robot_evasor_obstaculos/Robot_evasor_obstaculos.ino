
//---------------Liberias para control de motores y sensores--------------------//

#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>


//---------------------- Variables para el robot evasor de obstáculos-----------------------//

#define TRIG_PIN A0
#define ECHO_PIN A1
#define distancia_maxima 300 //300 milimetros que son 30cm
#define distancia_colision 30 //30 milimetros que son 3cm
#define velocidad_maxima 160
#define velocidad_maxima_compensado 40
#define distancia_vuelta distancia_colision + 20

//----------------- Creación de objetos para el robot--------------//

AF_DCMotor Motor_izquierdo_1(1, MOTOR12_1KHZ); // Objeto Motor 1 usando salida M1 del Driver, establece una frecuencida de 1kHZ en PWM
AF_DCMotor Motor_izquierdo_2(2, MOTOR12_1KHZ); // Objeto Motor 2 usando salida M2 del Driver, establece una frecuencida de 1kHZ en PWM
AF_DCMotor Motor_derecho_1(3, MOTOR34_1KHZ); // Objeto Motor 3 usando salida M3 del Driver, establece una frecuencida de 1kHZ en PWM
AF_DCMotor Motor_derecho_2(4, MOTOR34_1KHZ); // Objeto Motor 4 usando salida M4 del Driver, establece una frecuencida de 1kHZ en PWM

Servo mi_servo;

NewPing sonar(TRIG_PIN,ECHO_PIN,distancia_maxima);

int distanciaIzquierda, distanciaDerecha;
int curDist = 0;

/* Estas dos variables se van a usar hasta las funciones de movimiento del carrito*/
String establecer_motor = "";
int establecer_velocidad = 0;


//--------------------- Función para determinar pines y demás -------------------//
void setup() {
  mi_servo.attach(10);//Une al servo con el pin 10(El Servo_1 en el Shield)
  mi_servo.write(90);//Nos dice la posición del servo a 90 grados
  delay(1000);

}

//------------------------ Bucle principal -----------------//
void loop() {
  mi_servo.write(90); //Mueve los ojitos hacia adelante
  delay(90);//

  curDist = lecturaSensorUltrasonico(); //Lee la distancia con el sensor ultrasónico 
  
  if(curDist < distancia_colision)
  {
    cambia_camino();
    } //Compara la distancia y leída por el sensor con la de colisión y si es menor se activa la función cambia_camino

  mover_adelante();//Si la comparación no se cumple, pasa a esta función
  delay(500);

}


//---------------------- Funciones Extras ---------------------------//
//---------------------- para que se mueva---------------------------// 
//------------------------ el carrito ------------------------------//


//--------- Función para cambiar el camino --------------//
void cambia_camino(){
  
  movimiento_detenerse(); // Detiene el movimiento hacia adelante
  mi_servo.write(36); // el servo gira hacia los 36° (a la derecha)y revisa la distancia a al derecha
  delay(500);

  distanciaDerecha = lecturaSensorUltrasonico(); //Establece (set) la distancia derecha
  delay(500);
  
  mi_servo.write(144); // el servo gira hacia los 144° (a la izquierda)y revisa la distancia a al izquierda
  delay(700);

  distanciaIzquierda = lecturaSensorUltrasonico(); //Establece (set) la distancia izquierda
  delay(500);

  mi_servo.write(90); // Regresa al centro
  delay(500);

  compararDistancia();
  }

//--------- Función para compara la distancia --------------//
//----- Esta función nos va a determinar cual es la distancia mayor -------//

void compararDistancia(){
  if (distanciaIzquierda < distanciaDerecha) // Si la distancia derecha está menos obstruida
  {
    girar_derecha();
    }
  else if (distanciaDerecha < distanciaIzquierda) // Si la distancia izquierda está menos obstruida
  {
    girar_izquierda();
    }
  else
  {
    dar_la_vuelta();
    }
  
  }

//-------------------------------- Función para la lectura del sensor ultrasónico --------------------//
//------------ Esta función debe ser un int, porque el valor que nos va a regresarn a ser enteros ----//

int lecturaSensorUltrasonico(){
  
  delay(70);
  unsigned int microSegundos = sonar.ping(); //Envía sonido corto y obtiene tiempo de sonido corto en microsegundos

  int centimetros = microSegundos/US_ROUNDTRIP_CM; // Convierte la lectura de microsegundos a centrímetros

  return centimetros;
  }

//-------------- Función para que esté detenido el carrito -----------------//

void movimiento_detenerse(){

  
         /*Estas son las instrucciones que se van a ejecutar cuando se llame a esta función*/
  Motor_izquierdo_1.run(RELEASE);
  Motor_izquierdo_2.run(RELEASE);
  Motor_derecho_1.run(RELEASE);
  Motor_derecho_2.run(RELEASE);
  }

//--------------- Función para mover el carrito hacia adelante ----------------//

void mover_adelante(){

  establecer_motor = "Hacia Adelante";

  Motor_izquierdo_1.run(FORWARD);
  Motor_izquierdo_2.run(FORWARD);
  Motor_derecho_1.run(FORWARD);
  Motor_derecho_2.run(FORWARD);


     /*Este ciclo for es para elevar lentamente la velocidad para evitar que las baterias se gasten muy rápido */
  for (establecer_velocidad = 0; establecer_velocidad < velocidad_maxima; establecer_velocidad += 2)
  {
    Motor_izquierdo_1.setSpeed(establecer_velocidad);
    Motor_izquierdo_2.setSpeed(establecer_velocidad);
    Motor_derecho_1.setSpeed(establecer_velocidad);
    Motor_derecho_2.setSpeed(establecer_velocidad);
    delay(5); 
     }
  
  }

//------------------ Función mover hacia atrás ---------------//

void mover_atras(){

  establecer_motor = "Hacia atras";

  Motor_izquierdo_1.run(BACKWARD);
  Motor_izquierdo_2.run(BACKWARD);
  Motor_derecho_1.run(BACKWARD);
  Motor_derecho_2.run(BACKWARD);


     /*Este ciclo for es para elevar lentamente la velocidad para evitar que las baterias se gasten muy rápido */
  for (establecer_velocidad = 0; establecer_velocidad < velocidad_maxima; establecer_velocidad += 2)
  {
    Motor_izquierdo_1.setSpeed(establecer_velocidad);
    Motor_izquierdo_2.setSpeed(establecer_velocidad);
    Motor_derecho_1.setSpeed(establecer_velocidad);
    Motor_derecho_2.setSpeed(establecer_velocidad);
    delay(5); 
     }
  
  }


//-------------- Función para girar hacia la derecha -------------------//

void girar_derecha(){
  
  establecer_motor = "Derecha";

  Motor_izquierdo_1.run(FORWARD);
  Motor_izquierdo_2.run(FORWARD);
  Motor_derecho_1.run(BACKWARD);
  Motor_derecho_2.run(BACKWARD);

  Motor_derecho_1.setSpeed(establecer_velocidad + velocidad_maxima_compensado);
  Motor_derecho_2.setSpeed(establecer_velocidad + velocidad_maxima_compensado);
  delay(1500);

  establecer_motor = "Hacia adelante";

  Motor_izquierdo_1.run(FORWARD);
  Motor_izquierdo_2.run(FORWARD);
  Motor_derecho_1.run(FORWARD);
  Motor_derecho_2.run(FORWARD);

  }


//-------------- Función para girar hacia la izquierda -------------------//

void girar_izquierda(){
  
  establecer_motor = "Izquierda";

  Motor_izquierdo_1.run(BACKWARD);
  Motor_izquierdo_2.run(BACKWARD);
  Motor_derecho_1.run(FORWARD);
  Motor_derecho_2.run(FORWARD);

  Motor_izquierdo_1.setSpeed(establecer_velocidad + velocidad_maxima_compensado);
  Motor_izquierdo_2.setSpeed(establecer_velocidad + velocidad_maxima_compensado);
  delay(1500);

  establecer_motor = "Hacia adelante";

  Motor_izquierdo_1.run(FORWARD);
  Motor_izquierdo_2.run(FORWARD);
  Motor_derecho_1.run(FORWARD);
  Motor_derecho_2.run(FORWARD);

  }


//------------- Función para dar la vuelta ----------------//

void dar_la_vuelta(){

  establecer_motor = "Derecha";

  Motor_izquierdo_1.run(FORWARD);
  Motor_izquierdo_2.run(FORWARD);
  Motor_derecho_1.run(BACKWARD);
  Motor_derecho_2.run(BACKWARD);

  Motor_derecho_1.setSpeed(establecer_velocidad + velocidad_maxima_compensado);
  Motor_derecho_2.setSpeed(establecer_velocidad + velocidad_maxima_compensado);
  delay(1700);

  establecer_motor = "Hacia adelante";

  Motor_izquierdo_1.run(FORWARD);
  Motor_izquierdo_2.run(FORWARD);
  Motor_derecho_1.run(FORWARD);
  Motor_derecho_2.run(FORWARD);
  
  }



  
