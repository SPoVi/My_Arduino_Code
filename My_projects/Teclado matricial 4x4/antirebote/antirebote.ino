//Declaramos las variables que vamos a utilizar.

// Controlar el tiempo: Control de tareas periodicas (REAL TIME)
const unsigned long period = 50; // milisegundos
unsigned long prevMillis = 0;
unsigned long millisPresionado = 0;
// A byte stores an 8-bit unsigned number, from 0 to 255.
      // ¿¿¿¿ Por que lo ponen de mayor a menor ??
byte rowsPins[] = {9,8,7,6}; 
byte columnsPins[] = {5,4,3,2};

// Global vars
byte iRow = 0, iCol = 0;
static byte i = 0;

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
      Serial.println(keys[iRow][iCol]);   // Mostrar tecla
    }
  }
 
}

// Leer el estado del teclado
bool readKeypad()
{
  // Variable local 
  bool rst = false;
  bool presionado = false;
  
  int periodoPresionado = 500; // milisegundos
  
  // Barrido de filas: nRows = 4 . Si haces la busqueda 0 < 4 = 0, 1, 2, 3 == 0 <=3
  for (byte r = 0; r < nRows; r++)
  {
    // Poner fila a LOW
    digitalWrite(rowsPins[r],LOW);

    // Barrer todas las columnas comprobando pulsaciones
    for (byte c = 0; c < nCols; c++)
    {
      // Buscas el 0 logico en cada columna
      // Controlas el antirebote con millis
      if (digitalRead(columnsPins[c]) == LOW && ((millis() - millisPresionado) > periodoPresionado))   
      {
        millisPresionado = millis(); // Actualizas 
    
        // Cojes las var de ese momento
        rst = true;
        iRow = r; // r = 0
        iCol = c; // c = 4    
      }
    }

    // Devolver la fola a alta impedancia
    digitalWrite(rowsPins[r], HIGH);
    
  }
  return rst;
}

void estado_fila(byte i){

    Serial.print("Fila: ");
    Serial.print(i);
    Serial.print(" estado: ");
    Serial.println(digitalRead(rowsPins[i]));
}
