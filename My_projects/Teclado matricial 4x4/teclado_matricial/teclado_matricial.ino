//Declaramos las variables que vamos a utilizar.

// Controlar el tiempo: Control de tareas periodicas (REAL TIME)
const unsigned long period = 50;
unsigned long prevMillis = 0;

// A byte stores an 8-bit unsigned number, from 0 to 255.
      // ¿¿¿¿ Por que lo ponen de mayor a menor ??
byte rowsPins[] = {9,8,7,6}; 
byte columnsPins[] = {5,4,3,2};

// Global vars
byte iRow = 0, iCol = 0;    
const byte nRows = 4;
const byte nCols = 4;        

// Teclado alfanumerico
char keys[nRows][nCols]={{'1','2','3','A'},
                   {'4','5','6','B'},
                   {'7','8','9','C'},
                   {'*','0','#','D'}};
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
    pinMode(rowsPins[nr], OUTPUT); // ines: 9, 8, 7, 6
    digitalWrite(rowsPins[nr], HIGH);
  }

  //Para que salga en pantalla una vez.
  Serial.println("Introduce el codigo:");
}

void loop()
{
  if (millis() - prevMillis > period)   // Espera no bloqueante
  {
    prevMillis = millis();
    if (readKeypad())   // Detección de tecla pulsada
    {
      Serial.println(keys[iRow][iCol]);   // Mostrar tecla
    }
  }
}

// Leer el estado del teclado
bool readKeypad()
{
  bool rst = false;
  // Barrido de filas
  for (byte r = 0; r < nRows; r++)
  {
    // Poner fila a LOW
      /* Empieza por la 5, dado como está la lista rowsPins = {5,4,3,2}*/
    digitalWrite(rowsPins[r],LOW);

    // Barrer todas las columnas comprobando pulsaciones
    for (byte c = 0; c < nCols; c++)
    {
      if (digitalRead(columnsPins[c]) == LOW)   
      {
        // Pulsacion detectada, guardar fila y columna
        Serial.println("Tecla dectada");
        rst = true;
        iRow = r;
        iCol = c; 

        // Anti-rebote: No hace nada
        while(digitalRead(columnsPins[c]) == LOW){}
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
