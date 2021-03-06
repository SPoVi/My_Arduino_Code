#include <EEPROM.h>

char tecla;                 //Para la subrutina GetKey
int fila;                   //Para leer el teclado con un escaneo por fila
int contador;               //Para hacer el antirrebote de la pulsación de teclas
int cambio=0;               //Para hacer el tiempo de antirrebote menor y simular el funcionamiento de un teclado de ordenador
char contrasena [5];        //Array en el que guardaremos la CONTRASEÑA del arduino guardada en la eeprom
char input [5];             //Array en el que guardaremos lo INTRODUCIDO POR EL TECLADO
int code=0;                 //Para meter las teclas pulsadas al array de input
int estado=0;               //para determinar el estado de activacion o desactivacion de la alarma
int error=0;                //Para contabilizar el numero de contraseñas erroneas introducidas
int bloqueo=0;              //Contador para el bloqueo del teclado
int act=0;                  //Contador para la secuencia de activacion
int enemytime=0;            //Contador para los 30seg de tiempo para poner la contraseña  
int eliminar_enemigo=0;     //memoria para hacer sonar la alarma
int alarm=0;                //contador para hacer sonar la alarma
char serial[9];             //Array en el que guardamos el nº de SERIE BUENO
char serialinput[9];        //Array en el que guardaremos el nº de SERIE INTRODUCIDO
int cambiandocontrasena=0;  //Memoria del estado del proceso de cambio de contraseña
char cambiar [5];           //Array para el cambio de contraseña

void setup()
{
  Serial.begin(9600);       //Inicialización del puerto Serial
  pinMode (2,OUTPUT);       //Configuración de los pines como entradas o salidas
  pinMode (3,OUTPUT);
  pinMode (4,OUTPUT);
  pinMode (5,OUTPUT);
  pinMode (6,INPUT);
  pinMode (7,INPUT);
  pinMode (8,INPUT);
  pinMode (9,INPUT);
  digitalWrite(6,HIGH);     //inicialización de los pines a un estado HIGH
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  serial[0]=EEPROM.read(4); 
  serial[1]=EEPROM.read(5);
  serial[2]=EEPROM.read(6);
  serial[3]=EEPROM.read(7);
  serial[4]=EEPROM.read(8);
  serial[5]=EEPROM.read(9);
  serial[6]=EEPROM.read(10);
  serial[7]=EEPROM.read(11);
  serial[8]=0;
  pinMode (12,OUTPUT);
  digitalWrite(12,LOW);
  pinMode (13,OUTPUT);
  digitalWrite(13,LOW);
  pinMode (11,OUTPUT);
  digitalWrite(11,LOW); 
  pinMode (10,INPUT);
  
 }
 
 void callingPolice(void)
 {
   if (alarm<250)
   {
    digitalWrite(12,HIGH);
   }
  alarm++;
  if (alarm>=250)
  {
   digitalWrite(12,LOW);
  }
  if (alarm==350)
  {
    alarm=0;
  }
 }
 
 void enemydetected(void)
 {
   delay(1);
   enemytime++;
   if(enemytime==450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==1050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==1450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==1550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==1950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==2050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==2450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==2550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==2950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==3050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==3450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==3550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==3950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==4050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==4450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==4550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==4950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==5050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==5450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==5550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==5950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==6050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==6450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==6550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==6950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==7050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==7450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==7550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==7950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==8050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==8450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==8550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==8950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==9050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==9450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==9550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==9950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==10050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==10450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==10550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==10950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==11050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==11450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==11550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==11950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==12050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==12450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==12550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==12950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==13050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==13450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==13550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==13950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==14050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==14450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==14550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==14950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==15050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==15450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==15550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==15950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==16050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==16450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==16550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==16950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==17050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==17450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==17550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==17950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==18050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==18450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==18550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==18950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==19050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==19450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==19550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==19950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==20050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==20450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==20550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==20950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==21050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==21450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==21550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==21950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==22050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==22450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==22550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==22950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==23050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==23450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==23550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==23950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==24050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==24450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==24550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==24950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==25050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==25450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==25550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==25950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==26050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==26450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==26550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==26950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==27050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==27450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==27550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==27950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==28050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==28450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==28550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==28950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==29050)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==29450)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==29550)
   {
    digitalWrite(11,LOW); 
   }
   if(enemytime==29950)
   {
    digitalWrite(11,HIGH); 
   }
   if(enemytime==30000)
   {
    eliminar_enemigo=1;    
   }
 }
 void activacion(void)       //Subrutina de activación para los pitidos
{
 if(act==2)
  {
  Serial.println("Activando");
  }
 delay (1);
 act++;
 if(act==10000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==10250)
  {
  digitalWrite(12,LOW);
  }
 if(act==15000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==15250)
  {
  digitalWrite(12,LOW);
  }
 if(act==20000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==20250)
  {
  digitalWrite(12,LOW);
  }
 if(act==21000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==21250)
  {
  digitalWrite(12,LOW);
  }
 if(act==22000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==22250)
  {
  digitalWrite(12,LOW);
  } 
 if(act==23000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==23250)
  {
  digitalWrite(12,LOW);
  }
 if(act==24000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==24250)
  {
  digitalWrite(12,LOW);
  }
 if(act==25000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==25250)
  {
  digitalWrite(12,LOW);
  }
 if(act==26000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==26250)
  {
  digitalWrite(12,LOW);
  } 
 if(act==27000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==27250)
  {
  digitalWrite(12,LOW);
  }
 if(act==28000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==28250)
  {
  digitalWrite(12,LOW);
  }
 if(act==29000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==29250)
  {
  digitalWrite(12,LOW);
  }
 if(act==30000)
  {
  digitalWrite(12,HIGH);
  }
 if(act==30250)
  {
  digitalWrite(12,LOW);
  estado=2;
  Serial.println("Activado"); 
  }
  
}
 
int antirebote (int pin)                      //Subrutina de antirebote
{
     while((digitalRead(pin)==0)&&(contador<400)&&(cambio==0))
     { 
       delay(1);
       contador++;
     }  
    cambio=1;
    while((digitalRead(pin)==0)&&(contador<100)&&(cambio==1))
     { 
       delay(1);
       contador++;
     }  
     if(digitalRead(pin)==HIGH)
     {
       cambio=0;
     }
}

char getKey ()                             //Subrutina para la lectura del teclado
{
  char tecla;
    for(fila=2;fila<6;fila++)
  {
    digitalWrite(fila,LOW);
     int columna1=digitalRead(9);
     int columna2=digitalRead(8);
     int columna3=digitalRead(7);
     int columna4=digitalRead(6);  
    if(fila==2&&columna1==LOW)
    {
     contador=0;
     tecla='A';    
     antirebote(9);
     }
     if(fila==2&&columna2==LOW)
    {
     contador=0;
     tecla='0';    
     antirebote(8);
     }
     if(fila==2&&columna3==LOW)
    {
     contador=0;
     tecla='B';    
     antirebote(7);
     }
     if(fila==2&&columna4==LOW)
    {
     contador=0;
     tecla='C';    
     antirebote(6);
     }
     if(fila==3&&columna1==LOW)
    {
     contador=0;
     tecla='7';    
     antirebote(9);
     }
     if(fila==3&&columna2==LOW)
    {
     contador=0;
     tecla='8';    
     antirebote(8);
     }
     if(fila==3&&columna3==LOW)
    {
     contador=0;
     tecla='9';    
     antirebote(7);
     }
     if(fila==3&&columna4==LOW)
    {
     contador=0;
     tecla='D';    
     antirebote(6);
     }
     if(fila==4&&columna1==LOW)
    {
     contador=0;
     tecla='4';    
     antirebote(9);
     }
     if(fila==4&&columna2==LOW)
    {
     contador=0;
     tecla='5';    
     antirebote(8);
     }
     if(fila==4&&columna3==LOW)
    {
     contador=0;
     tecla='6';    
     antirebote(7);
     }
     if(fila==4&&columna4==LOW)
    {
     contador=0;
     tecla='E';    
     antirebote(6);
     }
     if(fila==5&&columna1==LOW)
    {
     contador=0;
     tecla='1';    
     antirebote(9);
     }
     if(fila==5&&columna2==LOW)
    {
     contador=0;
     tecla='2';    
     antirebote(8);
     }
     if(fila==5&&columna3==LOW)
    {
     contador=0;
     tecla='3';    
     antirebote(7);
     }
     if(fila==5&&columna4==LOW)
    {
     contador=0;
     tecla='F';    
     antirebote(6);
     }
   digitalWrite(fila,HIGH);
  }
return(tecla);  
}
void loop()
{
  contrasena[0]=EEPROM.read(0); 
  contrasena[1]=EEPROM.read(1);
  contrasena[2]=EEPROM.read(2);
  contrasena[3]=EEPROM.read(3);
  contrasena[4]=0;
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH); 
    tecla=getKey();
    if(tecla!=0&&tecla!='A'&&tecla!='B'&&tecla!='C'&&tecla!='D'&&tecla!='E'&&tecla!='F'&&error!=3&&cambiandocontrasena==0) //Captura en el array de la contraseña introducida
    {
      input[code]=tecla;
      Serial.print(input[code]);
      code++;
     if (code==4 && error!=3&&cambiandocontrasena==0)
     {
       input[code]=0;
       Serial.println("");   
     }  
    }
    
      if  (strcmp(input,contrasena)!=0 && estado==0 && input[0]!=0 && input[1]!=0 && input[2]!=0 &&input[3]!=0)
      {     
        code=0;   
        Serial.println("Contrasena incorrecta");
        error++;
        memset(input,0,5);
      }
      if  (strcmp(input,contrasena)!=0 && estado==2 && input[0]!=0 && input[1]!=0 && input[2]!=0 &&input[3]!=0)
      {
        code=0;
        digitalWrite(11,HIGH);
        digitalWrite(12,HIGH);
        delay(100);
        digitalWrite(12,LOW);
        Serial.println("Contrasena incorrecta");
        delay(500);
        error++;
        digitalWrite(12,HIGH);
        delay(100);
        digitalWrite(12,LOW);
        digitalWrite(11,LOW);
        memset(input,0,5);
      }
 
    if (error==3)                   //Iniciación de la secuencia de Bloqueo
    {
      delay(1);
      bloqueo++;
    }
    
    if (bloqueo==5000)
    {
      error=0;
      bloqueo=0;
    }
    if(tecla=='A' && strcmp(input,contrasena)==0 && estado==0 && input[0]!=0 && input[1]!=0 && input[2]!=0 &&input[3]!=0)        //Cambio de estado a ACTIVADO
    {
      act=0;        
      estado=1;
      memset(input,0,5);
      error=0;
      code=0;
    }
    if(tecla=='F' && strcmp(input,contrasena)==0 && (estado==2||estado==3) && input[0]!=0 && input[1]!=0 && input[2]!=0 &&input[3]!=0)        //Cambio de estado a DESACTIVADO
    {
      Serial.println("Desactivado"); 
      estado=0;
      enemytime=0;
      eliminar_enemigo=0;
      alarm=0;
      memset(input,0,5);
      error=0;
      code=0;
      digitalWrite(13,HIGH);
      digitalWrite(12,HIGH);
      delay(100);
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
    }
    
    if(estado==1)        //Inciciación de la secuencia de pitidos de la activación
    {
     activacion();
    }
    
    if(estado==2 && digitalRead(10)==LOW) 
    {
     estado=3;
    }
    
    if(estado==3)      //Inicia el tiempo de desactivación de la alarma
    {
     enemydetected(); 
    }
    
    if(eliminar_enemigo==1)     //Empieza a sonar la alarma
    {
     callingPolice(); 
    }
    if(tecla=='A' && code==0 && cambiandocontrasena==0 && estado==0) //Iniciamos proceso de cambio de contraseña
    {
      Serial.print("NºSerie:");
      cambiandocontrasena=1;
    }
   if(cambiandocontrasena==1 && tecla!=0 && tecla!='A' && tecla!='B' && tecla!='C' && tecla!='D' && tecla!='E' && tecla!='F' && error!=3) //Introduce el numero de serie
   {
     serialinput[code]=tecla;
     Serial.print(serialinput[code]);
     code++;
     if (code==8 && error!=3&&cambiandocontrasena==1)
     {
       serialinput[code]=0;
       Serial.println("");   
     }
   }
   if  (strcmp(serialinput,serial)!=0 && estado==0 && cambiandocontrasena==1 && serialinput[0]!=0 && serialinput[1]!=0 && serialinput[2]!=0 && serialinput[3]!=0 && serialinput[4]!=0 && serialinput[5]!=0 && serialinput[6]!=0 && serialinput[7]!=0)
   {     
     code=0;   
     Serial.println("Nº Serie incorrecto");
     error++;
     memset(serialinput,0,9);
   }
  if  (strcmp(serialinput,serial)==0 && estado==0 && cambiandocontrasena==1)  
   {     
     code=0;   
     Serial.println("Nº Serie Correcto");
     memset(serialinput,0,9);
     cambiandocontrasena=2;
   }
  if (cambiandocontrasena==2 && tecla=='B')   //Pulsa la tecla B para empezar a introducir la contraseña nueva
  {
    cambiandocontrasena=3;
    Serial.println("Introduce Nueva Contraseña");
  }
 if (cambiandocontrasena==3 && tecla!=0 && tecla!='A' && tecla!='B' && tecla!='C' && tecla!='D' && tecla!='E' && tecla!='F' && error!=3) //introducimos la contraseña nueva
   {
     cambiar[code]=tecla;
     Serial.print(cambiar[code]);
     code++;
     if (code==4 && error!=3 && cambiandocontrasena==3)
     {
       cambiar[code]=0;
       Serial.println("");
       Serial.println("contraseña cambiada");
       cambiandocontrasena=4; 
     }
   }
 if (cambiandocontrasena==4)    //Graba en la EEPROM la contraseña nueva
 {
    EEPROM.write(0, cambiar[0]);
    EEPROM.write(1, cambiar[1]);
    EEPROM.write(2, cambiar[2]);
    EEPROM.write(3, cambiar[3]);
    cambiandocontrasena=0;
    code=0;
    error=0;
  } 
}
