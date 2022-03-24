// https://wiki.seeedstudio.com/Grove-GSR_Sensor/


// Variables globales
const int GSR=A0;   // Pin con el que se realiza la medida
int sensorValue=0;  // Inicializacion de la variable a cero.
int gsr_average=0;  // Inicializacion de la variable a cero.
int imedidas = 10;  // Numero de medidas que hace para hacer la media

// Setup
void setup(){
  Serial.begin(9600);
}

 
// Loop
void loop(){

  long sum=0;  // Var local

  for(int i=0;i<imedidas;i++)           //Average the 10 measurements to remove the glitch
      {
      sensorValue=analogRead(GSR);
      sum += sensorValue;
      delay(5);
      }
   // Realizar media
   gsr_average = sum/imedidas;
   // Mostrar por pantalla
   Serial.println(gsr_average);

}
