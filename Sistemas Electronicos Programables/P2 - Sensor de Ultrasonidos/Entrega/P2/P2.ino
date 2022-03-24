//Declaramos las librerias que vamos a utilizar:
#include <TimerOne.h>          //Libreria del timer1
#include <GraphSeries.h>       //Libreria para poder graficar
#include <EEPROM.h>            //Libreria para utilizar la memorira EEPROM

//Para graficar:
GraphSeries g_aGraphs[] = {"Distancia Relativa","Temperatura Ambiente"};

float vs,  a=0.1, nr, d_rel, fd_e1;
unsigned long int time_e1;
boolean e1=0, lost=0;
int EE, i, rs;

//Declaramos las varaibles para la velocidad del sonido (vs)
   float y=1.4;       //Coeficiente de dilatacion adiabatica.
   float R=8.314;     //Constante universal de los gases.
   //float T=293.15;  //Temperatura en kelvin (20ºC). Una vez la calculamos con el LM35 no hace falta declarar esta variable.
   float M=0.029;     //Masa molar del gas
  

 void setup()
 {
   //Para imprimir por pantalla. Abre el puerto serie a 9600 bps.
   Serial.begin(9600);
   
   //Declaramos los pines.
   pinMode(2, INPUT);
   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
   pinMode(A0, INPUT);       //Entrada del LM35
   
   //Boton:
   pinMode(7, INPUT);        //Boton de enviar a graficar.
   digitalWrite(7, HIGH);    //Estado inicial del pin.
   
   //Condiciones del Timer1
   Timer1.initialize(35000); // Minimo será el tiempo en recorrer 10m (5 ida y 5 vuelta).(No menos de 30000).
   Timer1.attachInterrupt(lost_eco);
   //Interrupcion externa del pin2.Buscamos el primer eco.
   //No se puede imprimir dentro de una interrupcion, lleva mucho tiempo.
   attachInterrupt(0, pos_e1, FALLING);
   
   //Lectura de la memoria EEPROM
   EEPROM_rf(0,&nr);
 }
 
 //Bucle.
 void loop()
 { 
 
   Timer1.attachInterrupt(lost_eco); //El timer se interrumpe cuando el eco se ha perdido.
   
   Timer1.start();     //Iniciamos el Timer1.
   Sended_pulses();    //Enviamos los pulsos.
   
   //Mensaje de eco perdido.
   if(lost==1 && e1==0)
   {
     Serial.println("Se ha perdido el eco.");
     lost=0;
   }
   
   
   //Busqueda de la señal si hemos encontrado el primer eco.
   if(e1==1)
   {
     signal_distance();
   
     //Ayudas para visualizar los datos:
     //Serial.println(time_e1);
     //Serial.println(signal_distance());
     Serial.println(d_rel);
     
     //Envio de datos al ordenador para graficarlos.
     g_aGraphs[0].SendData(d_rel);         //Envio de datos de la distancia relativa.
     g_aGraphs[1].SendData(Tamb());        //Envio de datos de la temperatura pasada por el filtro.  
   }
   
   //Para graficar.
   Boton();
 }
 
 //Envio de los pulsos.(Beacon)
 void Sended_pulses()
 {
    int i=0;
    
   // Definimos los estados de los pines 4 y 5 mediante mascaras con puertas AND y OR.
   // Tienen que ser 16  pulsos (8 ciclos).(El cero tambien cuenta).
   /*El noInterrupts hace que se ejecute esa parte del codigo sistematicamente aunque haya un interupcion externa.Para volver a tener la condicion utilizalos el interrupts.
   Lo hacemos para que no pierda tiempo con el primer ruido que tenemos propio*/
   noInterrupts();
   for(i=0;i<8;i++)
   {
     PORTD=(PORTD&0xEF)|0x20;
     delayMicroseconds(12);
     PORTD=(PORTD&0xDF)|0x10;
     delayMicroseconds(12);     //Si quitamos esto tenemos pulsos , si lo ponemos ,ondas cuadradas.
   }
   interrupts();                //Reactivamos la condicion de interrupcion externa.
   delayMicroseconds(50);       //Actua como filtro del pulso que nos sale en el pin2 nada mas enviar el primer pulso.
    e1=0;
   delay(30);                   //Tiene que ser mas pequeño que el "Timer1.initialice" para que no corte la señal.
 }
 
 //Localizacion del primer eco (en tiempo) solo si no lo hemos buscado.
void pos_e1()
 {
   if(e1==0)
   {
     e1=1;                         //Hemos encontrado el primer eco.
     lost=0;                       //No se ha perdido.
     time_e1=Timer1.read();        //Leemos el tiempo que ha tardado
     Timer1.restart();             //Reiniciamos el timer para el siguiente envio de pulsos.
   }
 }


//Calculos para obtener la temperatura ambiente en ºC. (Hay que pasarlos a ºK)
float Tamb()
{
  float LM35;              //Señal analogica recivida del LM35.
  float Tgrad;             //Temperatura ambiente en grados.
  static float FTgrad;     //Temperatura ambiente en grados con filtro.Es necesario que sea static sino se machaca.
  
  LM35=analogRead(0);                 //Leemos lo que nos llega a la entrada analogica;
  Tgrad=(LM35*5/1024)*100;            //Con el parentesis hacemos la conversion analogica a V y multiplicando por 100 obtenemos grados.
  FTgrad=FTgrad+a*(Tgrad-FTgrad);     //Filtro exponencial.
  
  //Si queremos utilizar la funcion filtro.
  //Filter(Tgrad, &FTgrad);
  
  return FTgrad;
}


//Calculos para obtener la distancia hasta la señal en cm.
float signal_distance()
{
  float d_e1;             //Distancia hasta el primer eco.
  static float fd_e1;     //Distancia filtrada.
   
  vs=sqrt(y*R*(Tamb()+273)/M)*100;      //Lo multiplicamos por 100 para pasarlo a cm. Añadimos la temperaura ambiente medida con el LM35.
  d_e1=time_e1*vs/(1000000*2);          //Lo dividimos por 10^6 para tener us, y por dos por que es ida y vuelta.
  fd_e1=fd_e1+a*(d_e1-fd_e1);           //Distancia filtrada.
  
  //Si queremos utilizar la funcion filtro.
  //Filter(d_e1, &fd_e1);
  
  d_rel=fd_e1-nr;                       //Distancia de raltiva.
  
  return fd_e1;
}


//Funcion del eco perdido.
void lost_eco()
{
  lost=1;
}


//Establecer nuevo punto de referencia.
void new_ref()
{
  Serial.print("Nueva referencia ");
  nr=signal_distance();                            //Nuevo punto de referencia.
  Serial.println(nr);
  EEPROM_wf(0,&nr);                    //Llamada a la funcion.(celda de memoria, casilla distancia)

}

//Lectura de la EEPROM.
void EEPROM_rf(int EE, float *val)
{
  unsigned char* p = (unsigned char*)val;                //Valor en bytes del float.
  unsigned char i;
  for (i = 0; i < 4; i++)
  {
    *p++ = EEPROM.read(EE++);          //Lee el valor de la celda y la asigna al valor.Ambas con postincremento.
  }
}

//Escritura en la memoria EEPROM
void EEPROM_wf(int EE, float *val)
{
  Serial.println("Guardado de nueva referncia");
  unsigned char *p = (unsigned char*)val;                //Valor en bytes.
  unsigned char i;
  for (i = 0; i < 4; i++)   //No estaban los corchetes.
  {
    EEPROM.write(EE++, *p++);          //En cada celda del la memoria EEPROM escrive el valor en bytes. Ambas condiciones con postincremento.
  }
  
}

//Pulsamos tecla para envio de datos al ordenador.
void Boton()
{
  if (digitalRead(7)==LOW)                //Boton pulsado.
  {
    int cnt=0;
    
    //Serial.println("Boton pulsado");
    while(cnt<500 && digitalRead(7)==LOW) //Antirrebote del boton. 
    { 
      delay(1); 
      cnt++; 
    } 
    new_ref();
    rs++;
    
    //Si mantenemos pulsado 3s se resetea el punto de referencia.
    if(rs==6)
    {
      reset();
      delay(3000);
    }
      
  }
  
}

//Reseteamos el punto de referencia.
void reset()
{
    Serial.println("Referencia puesta a cero");
    nr=0;
    EEPROM_wf(0,&nr);
    rs=0;
}
    
/*
//Funcion filtro.
float Filter(float X, float *Y_1)
{
  float fY_1;
  
  fY_1=*Y_1+a*(X-*Y_1);
  *Y_1=fY_1;
  
  return *Y_1;
  
}
*/
