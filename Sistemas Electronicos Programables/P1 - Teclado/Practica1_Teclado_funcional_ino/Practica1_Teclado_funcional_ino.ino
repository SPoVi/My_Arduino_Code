//Introducimos la libreria para guardar la contraseña en la EEPROM.
#include <EEPROM.h>

//Declaramos las variables que vamos a utilizar.
//En este caso booleanos porque son 1 o 0.
boolean a=1,b=1,c=1,d=1,al,sensor,cont,AlarmOn;
char code[12];                                               // Array auxiliar.
char Epin[4];                                                // Pin guardado en la EEPROM
char PinAdmin[7]={'A','1','1','2','3','5'};                  // Contraseña que nos permite cambiar la contraseña de activacion/descativacion. 
int right, wrong, error, block, cnt, time=0, ecnt;

int sen=19;                                          // Salida del sensor. (A5 llevada a tension)
int zumb=12;                                         // Salida del sumbador.
int ledR=11;                                         // Salida LED fallo (rojo).
int ledG=10;                                         // Salida LED correcto (verde).


void setup(){
  //Para imprimir por pantalla.
  //Abre el puerto serie a 9600 bps.
  Serial.begin(9600);
  
  //Declaramos las salidas del teclado.
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
  //Declaramos las entradas.
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  
  //Estan cambiadas de orden segun las transparencias.
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);

  // Ponemos nuestro codigo en la memoria EEPROM:
  /*EEPROM.write(0,'3');
  EEPROM.write(1,'1');
  EEPROM.write(2,'0');
  EEPROM.write(3,'8');*/
  Epin[0]=EEPROM.read(0);
  Epin[1]=EEPROM.read(1);
  Epin[2]=EEPROM.read(2);
  Epin[3]=EEPROM.read(3);
  
  //Declaramos las salidas de los leds, sensor y zumbador:
  pinMode(sen,OUTPUT);
  digitalWrite(sen,LOW);
  pinMode(zumb,OUTPUT);
  digitalWrite(zumb,LOW);
  pinMode(ledR,OUTPUT);
  digitalWrite(ledR,LOW);
  pinMode(ledG,OUTPUT);
  digitalWrite(ledG,LOW);
  
  //Para que salga en pantalla una vez.
  Serial.println("Introduce el codigo:");
}


//La funcion 'loop' es un bucle.
void loop()
{
  static int i;
  char boton=getkey();
  
  if(boton!=0 && block==0) //Capturamos codigo. Si no esta bloqueado.
  {
    
    if(boton!='A' && boton!='B' && boton!='C'&& boton!='D' && boton!='E' && boton!='F') //No imprime las letras.
    {
      Serial.print("*");//Muestra por pantalla.
    }
    code[i]=boton;
    i++;
  }
    
  if(i==4 && code[0]!='A' && code[0]!='F' && block==0) //Comparamos el codigo introducido con el de la contraseña.
   {  
   right=0;
   wrong=0;
   code [i]='\0';//Fin del codigo.Da salto.*/
   
   if (strcmp(code,Epin)==0)//Compara, si es verdad es un 0 si no un 1.
    {
      right=1;
      wrong=0;
     }
       
    else 
     {
       right=0;
       wrong=1;
     }
    i=0;
   }
 
   if(i>4 && (code[0]==PinAdmin[0] && code[1]==PinAdmin[1] && code[2]==PinAdmin[2] && code[3]==PinAdmin[3] && code[4]==PinAdmin[4] && code[5]==PinAdmin[5]) && al==0 && block==0)//Cambiar la contraseña
   {
     if(cont==0 && code[6]=='B')
     {
       Serial.println("\nIntroduce el nuevo PIN: ");
       cont++;      
     }
     if(cont==0 && code[6]!='B' && i>6)
     {
       Serial.println("\nERROR.Tecla incorrecta (B).");
       Serial.println("Introduce el codigo: ");
       i=0; //Para volver a introducir codigo.
       wbeep();      
     }
       
     if(i>9)//Posicion 10 del array.
     {
       EEPROM.write(0,code[7]);
       EEPROM.write(1,code[8]);
       EEPROM.write(2,code[9]);
       EEPROM.write(3,code[10]);
       Epin[0]=EEPROM.read(0);
       Epin[1]=EEPROM.read(1);
       Epin[2]=EEPROM.read(2);
       Epin[3]=EEPROM.read(3);
       
       if(code[11]=='F')
         {
           Serial.println("\nPIN introducido con exito.");
           Serial.println("Introduce el codigo: ");
           i=0;
           error=0;
           cont=0;
       
         }
         if(i>11 && code[11]!='F')//Si has pulsado una tecla que no era en la F.
         {
           Serial.println("\nERROR. Tecla incorrecta (F).");
           Serial.println("Introduce el codigo: ");
           i=0;
           wbeep(); 
         }         
     }
   }
   
   //Para cuando nos equivocamos al introducir el codigo para cambiarlo.Hemos pulsado la A y despues nos hemos equivoado.
   if(i>5 && code[0]==PinAdmin[0] && (code[1]!=PinAdmin[1] || code[2]!=PinAdmin[2] || code[3]!=PinAdmin[3] || code[4]!=PinAdmin[4] || code[5]!=PinAdmin[5]) && al==0 && block==0)
  {
    Serial.println("\nERROR. Codigo incorrecto.");
    Serial.println("Introduce el codigo: ");
    error++;
    wbeep();
    i=0;
  }
  
     
   
   if(right==1 && boton=='A' && al==0)//Si el codigo es correcto , la alarma esta desactivada y puslamos A.
   { 
     right=0;//Para volver a comprobar el codigo.
     error=0;//Para volver a tener 3 oportunidades.     
     i=0;//Array a posicion inicial.
     time=0;
     sensor=digitalRead(sen);
     if(sensor==0)
     {
       Serial.println("\nERROR.Cable de alarma desconectado. Conecta el cable.");
       Serial.println("Introduce el codigo: ");
     }
     if(sensor==1)
     {
       Serial.println("\nAlarma Acivada");
       p_activacion();
       al=1; //Establecemos que la alarma esta activada.
     }
   }
    if (right==1 && boton=='F' && al==1)//Si el codigo es correcto, la alarma esta activada y pulsamos F.
   {
     Serial.println("\nAlarma Desactivada");
     right=0;
     i=0;
     error=0;
     digitalWrite(ledG, HIGH);
     digitalWrite(zumb, HIGH);
     delay(1000);
     digitalWrite(ledG, LOW);
     digitalWrite(zumb, LOW);
     al=0; //Establecemos que la alarma esta descativada.
     sensor=1;//Da igual que este conectado o desconectado de tension.
     time=0; //Reinicia el tiempo de la alarma.
     AlarmOn=0; //Descartiva sonido alarma.
     
   }
      
    if (wrong==1)
   {
     if (boton=='F' || boton=='A')
     {
       error++;
       Serial.println("\nCodigo incorrecto.");
       if(error<=2)
       {
         Serial.println("Introduce el codigo: ");
       }
       wrong=0;
       i=0;     
       wbeep();
     }
   }
   if (error==3)
   {
     delay(1);
     block=1;
     tblock();  
   }
     
   if(al==1)//Alarma activada y ha detectado movimiento.
   { 
     sensor=digitalRead(sen); //Hacemos que el sensor se encienda (1 logico). Si detecta movimiento  o cortan el cable se pondra a 0
     
     if(sensor==0)//Evitamos que si el ladron reconecta la alarma o se quede quieto, esta deje de sonar.
     {
       AlarmOn=1;
     }     
     sound();
     delay(10);     
   }
}

//Tiempo de bloqueo.

void tblock()
{
  int timeb=0;
  
  while(timeb<=60)
  {
    switch(timeb)
    {
      case 1:
        Serial.println("\nHas introducido mal es codigo 3 veces. Espera 60s.\n");
        break;
      case 60:
        block=0;
        error=0;
        Serial.println("Introduce el codigo: ");
        
    }
    delay(1000);
    timeb++;
  }
  
}
  

//Sonido alarma
void sound()
{
  if(AlarmOn==1)
     {
       if(time<30) //Para los 30 primeros segundos solo luce el LED rojo.
      {
        digitalWrite(ledR, HIGH);
        delay(250);
        digitalWrite(ledR, LOW);
        delay(250);
        time++;
      }
      
      if(time>=30) // Pasasdos los 30 segundo suena la alarma(zumbador).
      {
        digitalWrite(zumb, HIGH); //La alarma suena.      
      }
     }
}     
   
//Establecemos el protocolo de activacion que va a seguir el programa.
char p_activacion()
{
  int counter=0;
  while (counter<=61)
    {
    switch (counter)
    {
      case 0:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 1:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 20:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 21:
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 30:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 31:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 40:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 41:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 42:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 43:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 44:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 45:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 46:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 47:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 48:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 49:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 50:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 51:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 52:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 53:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 54:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 55:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 56:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 57:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 58:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 59:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
      case 60:
        digitalWrite(ledG, HIGH);
        digitalWrite(zumb, HIGH);
        break;
      case 61:   
        digitalWrite(ledG, LOW);
        digitalWrite(zumb, LOW);
        break;
    }
    delay (500);//Para que entre cada caso hagan 1s.
    counter++;
    } 
}

//Funcion para cuando introducimos clave erronea y suena el zumbador.(wroong beep)
//Tambien parpadea el LED rojo.
void wbeep()
{
  int bp=0; //contador para el beep.
  
  while(bp<=3)
  {
    switch(bp)
    {
      case 0:
        digitalWrite(zumb, HIGH);
        digitalWrite(ledR, HIGH);
        break;
      case 1:
        digitalWrite(zumb, LOW);
        digitalWrite(ledR, LOW);
        break;
      case 2:
        digitalWrite(zumb, HIGH);
        digitalWrite(ledR, HIGH);
        break;
      case 3:
        digitalWrite(zumb, LOW);
        digitalWrite(ledR, LOW);
        break;
    }
    delay(250);//para dos casos hacen 0.5s
    bp++;
  }
}

 

//Sustituimos lo que antes haciamos en en loop por la funcion "getkey".
char getkey()
{
//Declaramos las variables que vamos a necesitar.

int cnt;
char tecla=0;

  //Establecemos la condicion.
  //Primera fila.(1,2,3,F).
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  
  //Leemos el boton pulsado.
  //Al ponerlo detras de las condiciones de la fila, solo cogemos esa fila.
  //Si lo pones delante, estas seleccionando las columnas primero y despues la fila, por eso salian toda la columna.
  a = digitalRead(9);
  b = digitalRead(8);
  c = digitalRead(7);
  d = digitalRead(6);
  
  
  if(a==LOW && b==HIGH && c==HIGH && d==HIGH)
  {
    //No funciona si pones 'a' porque no la estas actualizando.
    //Introducimos un contador 'cnt' y le ponemos la condcion en el bucle.
    //Dentro del bucle le decimos que aumente en uno cada vez que ejecute el bucle.
    while (cnt<3000 && digitalRead(9)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='1';
    //Serial.print("1");
    //Reseteamos el valor del contador.
    cnt=0;
  }else if(a==HIGH && b==LOW && c==HIGH && d==HIGH)
  {
    while (cnt<3000 && digitalRead(8)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='2';
    //Serial.print("2");
    cnt=0;
  }else if(a==HIGH && b==HIGH && c==LOW && d==HIGH)
  {
    while (cnt<3000 && digitalRead(7)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='3';
    //Serial.print("3"); 
    cnt=0;
  }else if(a==HIGH && b==HIGH && c==HIGH && d==LOW
  ){
    while (cnt<3000 && digitalRead(6)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='F';
    //Serial.print("F");
    cnt=0;
    
  }
  
  //Segunda fila. (4,5,6,E)
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  
  //Leemos el boton pulsado.
  a = digitalRead(9);
  b = digitalRead(8);
  c = digitalRead(7);
  d = digitalRead(6);
  
  if(a==LOW && b==HIGH && c==HIGH && d==HIGH)
  {
   while (cnt<3000 && digitalRead(9)==LOW)
   {
      delay(1);
      cnt++;
   }
   tecla='4';
    //Serial.print("4");
    cnt=0;
  }else if(a==HIGH && b==LOW && c==HIGH && d==HIGH)
  {
    while (cnt<3000 && digitalRead(8)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='5';
    //Serial.print("5");
    cnt=0;
  }else if(a==HIGH && b==HIGH && c==LOW && d==HIGH)
  {
    while (cnt<3000 && digitalRead(7)==LOW)
    {
      delay(1);
      cnt++;
    }
   tecla='6';
   //Serial.print("6");
   cnt=0;
  }else if(a==HIGH && b==HIGH && c==HIGH && d==LOW)
  {
    while (cnt<3000 && digitalRead(6)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='E';
   //Serial.print("E");
   cnt=0;
  }
  
  
  //Tercera fila.(7,8,9,D).
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  
  //Leemos el boton pulsado.
  a = digitalRead(9);
  b = digitalRead(8);
  c = digitalRead(7);
  d = digitalRead(6);
  
  if(a==LOW && b==HIGH && c==HIGH && d==HIGH)
  {
    while (cnt<3000 && digitalRead(9)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='7';
    //Serial.print("7");
    cnt=0;
  }else if(a==HIGH && b==LOW && c==HIGH && d==HIGH)
  {
    while (cnt<3000 && digitalRead(8)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='8';
    //Serial.print("8");
    cnt=0;
  }else if(a==HIGH && b==HIGH && c==LOW && d==HIGH)
  {
    while (cnt<3000 && digitalRead(7)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='9';
    //Serial.print("9");
    cnt=0;
  }else if(a==HIGH && b==HIGH && c==HIGH && d==LOW)
  {
    while (cnt<3000 && digitalRead(6)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='D';
    //Serial.print("D");
    cnt=0;
  }
 
  
  //Cuarta fila.(A,0,B,C).
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  
  //Leemos el boton pulsado.
  a = digitalRead(9);
  b = digitalRead(8);
  c = digitalRead(7);
  d = digitalRead(6);
  
  if(a==LOW && b==HIGH && c==HIGH && d==HIGH)
  {
    while (cnt<3000 && digitalRead(9)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='A';
    //Serial.print("A");
    cnt=0;
  }else if(a==HIGH && b==LOW && c==HIGH && d==HIGH)
  {
    while (cnt<3000 && digitalRead(8)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='0';
    //Serial.print("0");
    cnt=0;
  }else if(a==HIGH && b==HIGH && c==LOW && d==HIGH)
  {
    while (cnt<3000 && digitalRead(7)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='B';
    //Serial.print("B");
    cnt=0;
  }else if(a==HIGH && b==HIGH && c==HIGH && d==LOW)
  {
    while (cnt<3000 && digitalRead(6)==LOW)
    {
      delay(1);
      cnt++;
    }
    tecla='C';
    //Serial.print("C");
    cnt=0;
  }
  return(tecla);
  delay(1);
}
