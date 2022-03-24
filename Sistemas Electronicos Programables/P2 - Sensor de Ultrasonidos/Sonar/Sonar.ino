

void setup()
{
  //Declaramos las salidas
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  
}

void loop()
{
  int i;
  
  
  //Ondas. (8 ciclos)
  for(i=0;i<=8;i++)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(0.125):
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    delay(0.125);
  }
  delay(2000); //Espera 2
} 
    
