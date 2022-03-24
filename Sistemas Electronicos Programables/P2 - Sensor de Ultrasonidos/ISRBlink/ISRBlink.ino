#include <TimerOne.h>
 
void setup() 
{
  // Initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards
  pinMode(13, OUTPUT);    
  
  //Inicializa el timer una vez pasados 'x' microsegundos.
  Timer1.initialize(100000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  
  //Funcion que realiza cuando interrumpimos el timer.
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
}
 
void loop()
{
  // Main code loop
  // TODO: Put your regular (non-ISR) logic here
}
 
/// --------------------------
/// Custom ISR Timer Routine
/// --------------------------
void timerIsr()
{
    // Toggle LED
    digitalWrite( 13, digitalRead( 13 ) ^ 1 ); // Invierte el estado de 0 a 1 y de 1 a 0 en el pin 13.
}
