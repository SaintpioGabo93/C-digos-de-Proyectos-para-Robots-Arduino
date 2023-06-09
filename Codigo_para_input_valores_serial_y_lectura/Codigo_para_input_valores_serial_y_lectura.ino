
//------------------ Código para lectura de valor vía bluetooth --------------//

char val; //

void setup() {
  Serial.begin(9600);

}

void loop() {
  while(Serial.available() > 0) //Código que se va a estár ejecuntando hasta recibir una insrucción del bluetooth
  {
    val = Serial.read();
    /*Aquí va el código que se va a ejecutar de acuerdo con 
    el valor leído y comparado por el puerto Serial*/
    }

}
