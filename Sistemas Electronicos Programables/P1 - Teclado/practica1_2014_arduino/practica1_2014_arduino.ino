#include <EEPROM.h>

const int numRows = 4;
const int numCols = 4;
const int debounceTime = 70;
const char keymap[numRows][numCols] = {
  {'1', '2', '3', 'F' },
  {'4', '5', '6', 'E' },
  {'7', '8', '9', 'D' },
  {'A', '0', 'B', 'C' },
  };
const int rowPins[numRows] = { 5, 4, 3, 2};
const int colPins[numCols] = { 9, 8, 7, 6};

int ledR = 11; // Led indicador de "fallo" en salida 11 
int ledG = 12; // Led indicador de "correcto" en salida 12
int Alarm = 10; 
int y=0; //Entero que contara el paso por la funcion loop
int i=0;


//int compareLimit = 4;


char getkey(); //Cargamos la funcion "lectura de teclado"
char Pin[15]; //Array que guardara los valores del teclado pulsados con el getkey
char Pinsecret[4]; //Establecemos un Array de 4 posiciones para nuestra contraseña 
char Pinadmin[10]={'A','5','5','5','5','5','5','5','5','B'}; //Contraseña serial para permisos de administrador, cambio de contraseña
unsigned char index=0; //Marcamos el inicio de nuestro puntero en la posicion 0



void setup ()
{
//Activacion del monitor serie:
Serial.begin(9600);

// Asignamos las salidas:
pinMode(ledR, OUTPUT);
pinMode(ledG, OUTPUT);
pinMode(Alarm, OUTPUT);
  
// Ponemos nuestro codigo en la memoria EEPROM y posteriormente anulamos mediante comentario las ordenes (para que unicamente ejecute una vez la grabacion)
/*EEPROM.write(0,'2');
  EEPROM.write(1,'8');
  EEPROM.write(2,'8');
  EEPROM.write(3,'5');*/
  Pinsecret[0]=EEPROM.read(0);
  Pinsecret[1]=EEPROM.read(1);
  Pinsecret[2]=EEPROM.read(2);
  Pinsecret[3]=EEPROM.read(3);
  
// Asiganamos recorrido de salidas y entradas para nuestro teclado
for (int row = 0; row < numRows; row++)
  {
    pinMode(rowPins[row],INPUT);
    digitalWrite(rowPins[row],HIGH);  //Estableciendo PULL UP
  }
for (int column = 0; column < numCols; column++)
  {
    pinMode(colPins[column],OUTPUT);
    digitalWrite(colPins[column],HIGH);  //Estableciendo PULL UP
  }
  
}

void loop() 
{
   char tempkey=getkey();
   
   if(tempkey!=0) {
   Serial.print(tempkey);
   Pin[index]=tempkey;
   index++;
   }
    
   
// Si la contraseña es correcta.   
 if((index>3)&&(strncmp(Pinsecret, Pin, 4)==0)) 
    
   {
// Pulse 'A' para Activacion o 'F' para Desactivacion
  
//ACTIVACION:     
     if((index>4)&&(Pin[4]=='A')) {
     Serial.println("ACTIVACION 30seg");
     digitalWrite(ledG, HIGH);
     digitalWrite(Alarm, HIGH);
     delay(5000);
     digitalWrite(ledG, LOW);
     digitalWrite(Alarm, LOW);
     index=0;
     y=0;
  
     }
     
//DESACTIVACION:
    if((index>4)&&(Pin[4]=='F')) {
     Serial.println("DESACTIVACION COMPLETA");
     digitalWrite(ledG, HIGH);
     delay(5000);
     digitalWrite(ledG, LOW);
     index=0;
     y=0;
     
     }
     
     if((index>4)&&(Pin[4]!='A')&&(Pin[4]!='F')) {
     
     Serial.println("ERROR");
     index=0;
     y++; 
     }
     
     
    }
  
 if((index>3)&&(strncmp(Pinadmin, Pin, 10)==0))  
   {
     
     if (i==0)  
        {
          Serial.println("Introduzca nuevo PIN");
          i++;
        }
     if (index>13) 
        {
              EEPROM.write(0,Pin[10]);
              EEPROM.write(1,Pin[11]);
              EEPROM.write(2,Pin[12]);
              EEPROM.write(3,Pin[13]);
              Pinsecret[0]=EEPROM.read(0);
              Pinsecret[1]=EEPROM.read(1);
              Pinsecret[2]=EEPROM.read(2);
              Pinsecret[3]=EEPROM.read(3);
              Serial.println("PIN introducido correctamente");
              index=0;
              y=0;
        }
      
   }

// Cuando la contraseña es incorrecta
if((index>3)&&(strncmp(Pinadmin, Pin, 4)!=0)&&(strncmp(Pinsecret, Pin, 4)!=0)) 

     {
       Serial.println("Vuelve a intentarlo");
       digitalWrite(ledR, HIGH);   
       delay(5000);
       digitalWrite(ledR, LOW);
       index=0;
       y++;
      }
   
 // Bloqueo de 60seg con 3 claves erroneas
 if(y==3) {
   Serial.println("BLOQUEADO, ESPERE 60seg");
   delay(30000);
   Serial.println("BLOQUEADO, ESPERE 30seg");
   delay(30000);
   Serial.println("INTRODUCCA CLAVE");
   index=0;
   y=0;
   }
     
 }
   

 char getkey()
  { 
    char key=0;
    
    for(int column = 0; column < numCols; column++)
      {
          digitalWrite(colPins[column],LOW);
          for(int row = 0; row < numRows; row++)
          {
            if(digitalRead(rowPins[row]) == LOW)
                {
                  delay(debounceTime);
                  while(digitalRead(rowPins[row]) == LOW);
                  key = keymap[row][column];
                }
          }
          digitalWrite(colPins[column],HIGH);
      }
      return key;
  }
            
