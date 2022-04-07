//Introducimos la libreria para guardar la contraseña en la EEPROM.
#include <EEPROM.h>

// Controlar el tiempo: Control de tareas periodicas (REAL TIME)
const unsigned long period = 50; // milisegundos
unsigned long prevMillis = 0;

// A byte stores an 8-bit unsigned number, from 0 to 255.
      // ¿¿¿¿ Por que lo ponen de mayor a menor ??
byte rowsPins[] = {9,8,7,6}; 
byte columnsPins[] = {5,4,3,2};

// Global vars
byte iRow = 0, iCol = 0;
static byte i = 0;
bool right=0, wrong =0;
// No se pueden modificar    
const byte nRows = 4;
const byte nCols = 4;        

// Teclado alfanumerico
char keys[nRows][nCols]={{'1','2','3','A'},
                   {'4','5','6','B'},
                   {'7','8','9','C'},
                   {'*','0','#','D'}};

// Array auxiliar para guardar valor de teclas pulsadas
char code[12];                                               // Array auxiliar.
char Epin[5];     
// Inicializacion
void setup()
{
  
  Serial.begin(9600);

  Serial.println("Flag - Estableciendo Columnas");  // Filas en pullup
  // Columnas en alta impedancia
  for (byte nc = 0; nc < nCols; nc++)
  {
    pinMode(columnsPins[nc],INPUT_PULLUP); // Pines: 5, 4, 3, 2
    //digitalWrite(columnsPins[c], HIGH);
  }

  Serial.println("Flag - Estableciendo Filas");  // Filas en pullup
  for (byte nr = 0; nr < nRows; nr++)
  {
    pinMode(rowsPins[nr], OUTPUT); // Pines: 9, 8, 7, 6
    digitalWrite(rowsPins[nr], HIGH); // uno logico
  }

  // Ponemos nuestro codigo en la memoria EEPROM:
  EEPROM.write(0,'3');
  EEPROM.write(1,'1');
  EEPROM.write(2,'0');
  EEPROM.write(3,'8');
  Epin[0]=EEPROM.read(0);
  Epin[1]=EEPROM.read(1);
  Epin[2]=EEPROM.read(2);
  Epin[3]=EEPROM.read(3);
  Epin[4]='\0';

  // Mostrar EPIN
  mostrarEpin();
  mostrarArray(Epin,4);
  
  //Para que salga en pantalla una vez.
  Serial.println("Introduce el codigo:");
}

void loop()
{
  if (millis() - prevMillis > period)   // Espera no bloqueante
  {
    prevMillis = millis(); // Si esta delante de la accion, tienes en cuenta el tiempo que dura la accion
    if (readKeypad())   // Detección de tecla pulsada. Bool
    {
      // Valor de la tecla pulsada
      char boton = keys[iRow][iCol];
      // Codigo inicial
      introducirPin(boton);
    }
  }
  
  //Comparamos el codigo introducido con el de la contraseña.
  if(i==4 && code[0]!='A' && code[0]!='F') 
   {  
   right=0;
   wrong=0;
   code[i]='\0';//Fin del codigo.Da salto.*/

   // Comparacion entre el codigo introducido y el de la memoria EEPROM
   // code[0]==Epin[0] && code[1] == Epin[1] && code[2]==Epin[2] && code[3] == Epin[3]
   if (strcmp(code, Epin)==0)//Compara, si es verdad es un 0 si no un 1.
    {
      Serial.println("");
      Serial.println("Codigo introducido CORRECTO");
      right=1;
      wrong=0;
     }
       
    else 
     {
      Serial.println("");
      Serial.println("Codigo INCORRECTO");
      right=0;
      wrong=1;
     }
    i=0; // reset para introducir codigo de nuevo
   }
}

// Function - Leer el estado del teclado
bool readKeypad()
{
  // Variable local 
  bool rst = false;
  bool presionado = false;
  // Barrido de filas: nRows = 4 . Si haces la busqueda 0 < 4 = 0, 1, 2, 3 == 0 <=3
  for (byte r = 0; r < nRows; r++)
  {
    // Poner fila a LOW
      /* Empieza por la 5, dado como está la lista rowsPins = {5,4,3,2}
      
         cuando r = 0 -> mandando 0  a la fila {*, 0,#,D}
         cuando r = 1 -> mandando 0  a la fila {7, 8,9,C}
         cuando r = 2 -> mandando 0  a la fila {4,5,6,B}
         cuando r = 3 -> mandando 0  a la fila {1,2,3,A}*/
    digitalWrite(rowsPins[r],LOW);

    // Barrer todas las columnas comprobando pulsaciones
    /*
     * Para r = 0:
     *    En el momento en el que pulse la tecla, la columna de esa tecla cierra el lazo con la tomta tierra.
     *    Es decir, se pone a cero logico.
     */
    for (byte c = 0; c < nCols; c++)
    {
      // Buscas el 0 logico en cada columna
      if (digitalRead(columnsPins[c]) == LOW && presionado == false)   
      {
        presionado = true;
        // Pulsacion detectada, guardar fila y columna
        //Serial.println("Tecla dectada"); // Para la tecla 'D'
        rst = true;
        iRow = r; // r = 0
        iCol = c; // c = 4

        // Anti-rebote: 
        while(digitalRead(columnsPins[c]) == LOW){}
        
      }
      presionado = false;
    }

    // Devolver la fola a alta impedancia
    digitalWrite(rowsPins[r], HIGH);
    
  }
  return rst;
}

// Procedure - IntroducirPin
void introducirPin(char boton){
      // Si la tecla introducida no es una alfabetica
    if(boton!='A' && boton!='B' && boton!='C'&& boton!='D') //No imprime las letras.
    {
      //Serial.print("*");//Muestra por pantalla.
      Serial.print(boton);
    }else
      Serial.print(boton);
      code[i]=boton;        // Estas guardando el valor de la tecla pulsada 
      i++;
}

// Procedure - Mostrar pin de la EEPROM
void mostrarEpin(){

  Serial.print("Mostrando pin de la EEPROM: ");
  for(byte j=0; j<4; j++){
    Serial.print(Epin[j]);
  }
  Serial.println();
}

// Procedure - Mostrar pin de la EEPROM
void mostrarArray(char a[], byte n){

  Serial.print("Mostrando array: ");
  for(byte j=0; j<n; j++){
    Serial.print(a[j]);
  }
  Serial.println();
}
