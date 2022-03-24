#include <TimerOne.h>
#include <EEPROM.h> 
#include <GraphSeries.h>
GraphSeries g_aGraphs[] = {"Temperatura Ambiente", "Distancia Relativa"};

int long time;
float temp;
float distanciacm;
int primereco=0;
int perdido=0;

//Para la velocidad
float velocidad;
float y=1.4; 
float R=8.314;
float M=0.029;
float offset;
float distancia_relativa;

//Para la memoria
int ee=12;
int i=0;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(2, INPUT); 
  pinMode(13,OUTPUT);
  pinMode(A5, INPUT);
  pinMode(8,INPUT);
  digitalWrite(8, HIGH); 
  Timer1.initialize(40000);
  Timer1.attachInterrupt( ecoperdido );
  attachInterrupt(0, senalrecibida, FALLING);
  EEPROM_read_float(12,&offset);

}

void loop() 
{
  
  static float distancia_1;
  float distancia_e;

  Timer1.attachInterrupt( ecoperdido );  //El timer se interrumpe cuando el eco se ha perdido.
  pulsosenviados(); //Enviamos los pulsos.
  
  if (perdido==1)
  {  
    perdido=0;
  }
  
  //Calculo de la disancia de la señal si hemos encontrado el primer eco.
  if (primereco==1)
  {

    velocidad=100*(sqrt(y*R*(temperatura()+273)/M));
    distancia_e=((float)time*velocidad)/(1000000*2);
    distanciacm=(distancia_1+0.1*(distancia_e-distancia_1));
    distancia_1=distanciacm;
    distancia_relativa=distanciacm-offset;
    //Serial.println(distancia_relativa);
     

  }

  if (digitalRead(8)==LOW) //Boton.
  {
    int cont;
    while(cont<500&&digitalRead(6)==LOW) //Antirrebote del boton. 
    { 
      delay(1); 
      cont++; 
    } 
    puestacero();
  }
  g_aGraphs[0].SendData(temp);
  g_aGraphs[1].SendData(distancia_relativa);



}

//Busqueda del primer eco.
void senalrecibida()
{
  if (primereco==0)
  {
    time=Timer1.read();	
    Timer1.stop();
    primereco=1;
    perdido=0;

  }

}

//Envio de pulsos.
void pulsosenviados()
{
  Timer1.restart();//Reiniciamos el timer1.
  Timer1.start(); //Iniciamos el timer1.
  primereco=0; //Poenemos la condicion de busqueda del primer eco.
  for(i=0;i<=7;i++)
  {
    PORTD=(PORTD&0xEF)|0x20;//Hacemos una AND del puerto B con 0xEF para poner el PIN4 a 0 y una OR con 0x20 para poner el PIN5 a 1
    delayMicroseconds(12);
    PORTD=(PORTD&0xDF)|0x10; //Hacemos una AND del puerto B con 0xDF para poner el PIN4 a 1 y una OR con 0x10 para poner el PIN5 a 0
    delayMicroseconds(13);	
  }
  i=0; //Omitible.
  delay(50);//29ms que tarda entre un pulso y otro
}

//Condicion para interrumpir el timer1.
void ecoperdido()
{
  perdido=1;
}

//Calculamos la variable temperatura.
float temperatura()
{
  float LM35; //Variable del LM35.
  float temp_e; //Temperatura en grados sin filtrar.
  float temp_1; //Variables auxiliar.
  LM35=analogRead(A5); //Entrada analogia del LM35.
  temp_e=LM35*100*5/1024;//multiplicamos la tension del lm35 por 100 para pasar a grados y lo multiplicamos por 5/1024 por la resolucion del arduino
  temp=(temp_1+0.01*(temp_e-temp_1))*100; //Filtramos la señal.
  temp_1=temp;
  
  return temp;

}

//Establecer nuevo punto de referencia.
void puestacero()
{
  
  offset=distanciacm; //Nuevo punto de referencia.
  EEPROM_write_float(12,&distanciacm); //Llamada a la funcion.(celda de memoria, casilla distancia)
//En nuestro caso empeazira en 0.

}

//Escritura en la memoria EEPROM
void EEPROM_write_float(int ee, float *value)
{
  
  byte *p = (byte*)value;  //Valor en bytes.
  int i;
  for (i = 0; i < sizeof(*value); i++) //No estaban los corchetes.
  {
    EEPROM.write(ee++, *p++); //En cada celda del la memoria EEPROM escrive el valor en bytes. Ambas condiciones con postincremento.
  }
  
}

//Lectura de la memoria EEPROM
void EEPROM_read_float(int ee, float *value)
{
  
  byte* p = (byte*)value;  //Valor en bytes
  int i;
  for (i = 0; i < sizeof(*value); i++)
  {
    *p++ = EEPROM.read(ee++); //Lee el valor de la celda y la asigna al valor.Ambas con postincremento.
  }
}


  
  
/*NOTAS:
Puede que las memorias esten en bytes porque solo hay hasta 256 valores por celda. 
De esta forma podemos guardar digito por celda

FILTROS:
Usar punteros y memoria.

float filtro(float *x, float *y)
{
  float *x,*y;
  
  y=y+a*(x-y);
  
  return *y;
}/*
//Utilizar la EEPROM y asignar antes el valor i. no en el bucle, para nueva referncia el 0, para filtros utilizar otros 5 o mayor


