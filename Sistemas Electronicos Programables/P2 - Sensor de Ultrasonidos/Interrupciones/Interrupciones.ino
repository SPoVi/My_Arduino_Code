
//Decalracion de variables.
int pin = 13; //Pin que vamos a utilizar.
volatile int estado = LOW; //Declaramos el estado inicial.


void setup()
{
  pinMode(pin, OUTPUT);
  attachInterrupt(0, parpadeo, CHANGE); //Interrupcion (pin2) - funcion -modo
}

//Bucle.
void loop()
{
  digitalWrite(pin, estado);
}

//Subrutina.
void parpadeo()
{
  estado = !estado;
}
