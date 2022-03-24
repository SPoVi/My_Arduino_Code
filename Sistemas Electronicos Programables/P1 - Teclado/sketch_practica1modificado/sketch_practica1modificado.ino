#include <EEPROM.h>
int out2 = 2;
int out3 = 3;
int out4 = 4;
int out5 = 5;
int in6 = 6;
int in7 = 7;
int in8 = 8;
int in9 = 9;
int ledR = 11; // Led indicador de "fallo" en salida 12 
int ledG = 12; // Led indicador de "correcto" en salida 13
int y=0; //Entero que contara el paso por la funcion loop
int n=0; //Entero que contara los errores cometidos
char getkey(); //Cargamos la funcion "lectura de teclado"
char Pin[8]; //Establecemos un Array para nuestro Pin tecleado de 8 posiciones
char Pinsecret[4]; //Establecemos un Array de 4 posiciones para nuestra contraseña 
char Pinadmin[4]={'A','1','2','F'}; //Contraseña serial para permisos de administrador, cambio de contraseña
unsigned char index=0; //Marcamos el inicio de nuestro puntero en la posicion 0



void setup ()
{
  
// Asignamos las salidas:
  pinMode(out2,OUTPUT);
  pinMode(out3,OUTPUT);
  pinMode(out4,OUTPUT);
  pinMode(out5,OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  
// Asignamos las entradas:
  pinMode(in6,INPUT);
  pinMode(in7,INPUT);
  pinMode(in8,INPUT);
  pinMode(in9,INPUT);
  
// Establecemos las PULL UP:
  digitalWrite(in6,HIGH);
  digitalWrite(in7,HIGH);
  digitalWrite(in8,HIGH);
  digitalWrite(in9,HIGH);

// Ponemos nuestro codigo en la memoria EEPROM:
  /*EEPROM.write(0,'2');
  EEPROM.write(1,'8');
  EEPROM.write(2,'8');
  EEPROM.write(3,'5');*/
  Pinsecret[0]=EEPROM.read(0);
  Pinsecret[1]=EEPROM.read(1);
  Pinsecret[2]=EEPROM.read(2);
  Pinsecret[3]=EEPROM.read(3);
// Activamos monitor serie:
  Serial.begin(9600);


} 
 
void loop() {
 char tempkey=getkey();
   
   if(tempkey!=0) {
   Serial.print(tempkey);
   Pin[index]=tempkey;
   index++;
   }


   if((index>3)&&(Pinsecret[0]==Pin[0])&&(Pinsecret[1]==Pin[1])&&(Pinsecret[2]==Pin[2])&&(Pinsecret[3]==Pin[3])) {
   Serial.println("OK");
   digitalWrite(ledG, HIGH);
   delay(5000);
   digitalWrite(ledG, LOW);
   index=0;
  }
  
    if((index>3)&&((Pinadmin[0]==Pin[0])&&(Pinadmin[1]==Pin[1])&&(Pinadmin[2]==Pin[2])&&(Pinadmin[3]==Pin[3])))  {
    if (y==0)  {
    Serial.println("Introduzca nuevo PIN");
    y++;
    }
    if (index>7) {
    EEPROM.write(0,Pin[4]);
    EEPROM.write(1,Pin[5]);
    EEPROM.write(2,Pin[6]);
    EEPROM.write(3,Pin[7]);
    Pinsecret[0]=EEPROM.read(0);
    Pinsecret[1]=EEPROM.read(1);
    Pinsecret[2]=EEPROM.read(2);
    Pinsecret[3]=EEPROM.read(3);
    Serial.println("PIN introducido correctamente");
    index=0;
    }
    
    }
  
   if((index>3)&&((Pinadmin[0]!=Pin[0])||(Pinadmin[1]!=Pin[1])||(Pinadmin[2]!=Pin[2])||(Pinadmin[3]!=Pin[3]))&&((Pinsecret[0]!=Pin[0])||(Pinsecret[1]!=Pin[1])||(Pinsecret[2]!=Pin[2])||(Pinsecret[3]!=Pin[3]))) {
   if (n!=2) {
   Serial.println("Vuelve a intentarlo");
   digitalWrite(ledR, HIGH);   
   delay(5000);
   digitalWrite(ledR, LOW);
   
   n++;
   index=0;
   }
   else
   {
   Serial.println("CONTRASEÑA INCORRECTA");
   digitalWrite(ledR, HIGH);   
   delay(20000);
   digitalWrite(ledR, LOW);
   n=0;
   index=0;  
   }
   
   }
  
 
 
 }

 
  
 


char getkey(){ // Funcion lectura del teclado
char key=0;
// Establecemos la primera salida para centrarnos en la fila 1
  digitalWrite(out2,HIGH);
  digitalWrite(out3,HIGH);
  digitalWrite(out4,HIGH);
  digitalWrite(out5,LOW);
// Comprobamos si es LOW la entrada a deseada y la visualizamos la tecla pulsada en la consola
  if(digitalRead(in9)==LOW)
  {
     //Serial.println("TECLA PULSADA '1'");
     key='1';
     delay(300);
  }
  
  if(digitalRead(in8)==LOW)
  {
     //Serial.println("TECLA PULSADA '2'");
     key='2';
     delay(300);
  }
  
  if(digitalRead(in7)==LOW)
  {
     //Serial.println("TECLA PULSADA '3'");
     key='3';
     delay(300);
  }
  
  if(digitalRead(in6)==LOW)
  {
     //Serial.println("TECLA PULSADA 'F'");
     key='F';
     delay(300);
  }
  
 // Establecemos la segunda salida para centrarnos en la fila 2
 digitalWrite(out2,HIGH);
 digitalWrite(out3,HIGH);
 digitalWrite(out4,LOW);
 digitalWrite(out5,HIGH);
 
 // Comprobamos si es LOW la entrada a deseada y la visualizamos la tecla pulsada en la consola
   if(digitalRead(in9)==LOW)
  {
     //Serial.println("TECLA PULSADA '4'");
     key='4';
     delay(300);
  }
  
  if(digitalRead(in8)==LOW)
  {
     //Serial.println("TECLA PULSADA '5'");
     key='5';
     delay(300);
  }
  
  if(digitalRead(in7)==LOW)
  {
     //Serial.println("TECLA PULSADA '6'");
     key='6';
     delay(300);
  }
  
  if(digitalRead(in6)==LOW)
  {
     //Serial.println("TECLA PULSADA 'E'");
     key='E';
     delay(300);
  }
  // Establecemos la tercera salida para centrarnos en la fila 3
 digitalWrite(out2,HIGH);
 digitalWrite(out3,LOW);
 digitalWrite(out4,HIGH);
 digitalWrite(out5,HIGH);
 
 // Comprobamos si es LOW la entrada a deseada y la visualizamos la tecla pulsada en la consola
   if(digitalRead(in9)==LOW)
  {
     //Serial.println("TECLA PULSADA '7'");
     key='7';
     delay(300);
  }
  
  if(digitalRead(in8)==LOW)
  {
     //Serial.println("TECLA PULSADA '8'");
     key='8';
     delay(300);
  }
  
  if(digitalRead(in7)==LOW)
  {
     //Serial.println("TECLA PULSADA '9'");
     key='9';
     delay(300);
  }
  
  if(digitalRead(in6)==LOW)
  {
     //Serial.println("TECLA PULSADA 'D'");
     key='D';
     delay(300);
  }
// Establecemos la cuarta salida para centrarnos en la fila 4
 digitalWrite(out2,LOW);
 digitalWrite(out3,HIGH);
 digitalWrite(out4,HIGH);
 digitalWrite(out5,HIGH);
 
// Comprobamos si es LOW la entrada a deseada y la visualizamos la tecla pulsada en la consola
   if(digitalRead(in9)==LOW)
  {
     //Serial.println("TECLA PULSADA 'A'");
     key='A';
     delay(300);
  }
  
  if(digitalRead(in8)==LOW)
  {
     //Serial.println("TECLA PULSADA '0'");
     key='0';
     delay(300);
  }
  
  if(digitalRead(in7)==LOW)
  {
     //Serial.println("TECLA PULSADA 'B'");
     key='B';
     delay(300);
  }
  
  if(digitalRead(in6)==LOW)
  {
     //Serial.println("TECLA PULSADA 'C'");
     key='C';
     delay(300);
  }  
  return key; 
  
}
