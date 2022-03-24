//Introducimos los pines que vamos a utilizar
boolean a=1,b=1,c=1,d=1;

void setup(){
  //Para que salga en pantalla.
  Serial.begin(9600);
  //Salidas
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  //Entradas
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  
  //Como por ahora solo vamos a utilizar una fila no necesitamos que se haga un bucle.
  //Establecemos las entradas al Arduino como 1 logicos.
  //Habilita un resistencia interna de 20k conectada en PullUp
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  //Enstablecemos las salidas del Arduino que nos leera la fila (una sola).
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  
   Serial.print("Introduce un numero: \n");
}

void loop(){
  
  //Tenemos que leer el boton que pulsamos en las salidas quese veran mofificaadas
  //cuando pulsamos los botoenes.
  a = digitalRead(9);
  b = digitalRead(8);
  c = digitalRead(7);
  d = digitalRead(6);
  
  //Para la primera fila.
    if (a==LOW && b==HIGH && c==HIGH && d==HIGH){
      Serial.print("Has introducido un 1\n");
    }else if (a==HIGH && b==LOW && c==HIGH && d==HIGH){
      Serial.print("Has introdudico un 2\n");      
    }else if(a==HIGH && b==HIGH && c==LOW && d==HIGH){
      Serial.print("Has introducido un 3\n");     
    }else if(a==HIGH && b==HIGH && c==HIGH && d==LOW){
      Serial.print("Has introducido una F\n");
    }
    delay(200);
 }
