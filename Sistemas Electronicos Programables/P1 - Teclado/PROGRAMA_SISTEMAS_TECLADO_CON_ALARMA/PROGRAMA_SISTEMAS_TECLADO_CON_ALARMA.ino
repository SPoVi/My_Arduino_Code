
int buttonState;
char code [5]="1234";
char pass[5];
int error=0;
int bloqueo = 0;
int ONOFF=0;
int sec=0;
int bep=0;
int pit=0;



void setup() 
{
Serial.begin (9600);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,INPUT);
pinMode(7,INPUT);
pinMode(8,INPUT);
pinMode(9,INPUT);

digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
pinMode (12,OUTPUT); // la "pata" 12 es una salida ZUMBADOR
digitalWrite(12,LOW); // esta apagado inicialmente
pinMode (11,OUTPUT); // Salida de LED ROJO
digitalWrite(11,LOW);
pinMode (10,OUTPUT);// Salida de LED Verde
digitalWrite(10,LOW);
}

void pitido(){
  delay(1);
  if(pit==1){
    digitalWrite(12,HIGH);
    digitalWrite(10,HIGH);
  }
  if(pit==11){
    digitalWrite(12,LOW);
    digitalWrite(10,LOW);
  }
}

void beep(){
  delay(1);
  bep++;
  if(bep==1){
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);
  }
  if(bep==7){
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
  }
  if(bep==13){
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);
  }
  if(bep==19){
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
  }
}
  
void Activacion (){ 
 delay(1);
 sec++;
 Serial.println(sec);// quitar esta linea solo de comprobacion.
 if(sec==220){
   digitalWrite(12,HIGH);//pitido a los 10 seg
   }
 if(sec==225){
   digitalWrite(12,LOW);
   }
 if(sec==330){
   digitalWrite(12,HIGH);//pitido a los 15 seg
   }
 if(sec==335){
   digitalWrite(12,LOW);
   }
 if(sec==440){
   digitalWrite(12,HIGH);//pitido a los 20 seg
   }
 if(sec==450){
   digitalWrite(12,LOW);  
   }
 if(sec==462){
   digitalWrite(12,HIGH);//pitido a los 21 seg
   }
 if(sec==470){
    digitalWrite(12,LOW);
   }
 if(sec==484){
   digitalWrite(12,HIGH);//pitido a los 22 seg
   }
 if(sec==494){
    digitalWrite(12,LOW);
   }
 if(sec==506){
   digitalWrite(12,HIGH);//pitido a los 23 seg
   }
 if(sec==516){
    digitalWrite(12,LOW);
   }
 if(sec==528){
   digitalWrite(12,HIGH);//pitido a los 24 seg
   }
 if(sec==539){
    digitalWrite(12,LOW);
   }
 if(sec==550){
   digitalWrite(12,HIGH);//pitido a los 25 seg
   }
 if(sec==561){
    digitalWrite(12,LOW);
   }
 if(sec==572){
   digitalWrite(12,HIGH);//pitido a los 26 seg
   }
 if(sec==584){
    digitalWrite(12,LOW);
   }
 if(sec==594){
   digitalWrite(12,HIGH);//pitido a los 27 seg
   }
 if(sec==605){
    digitalWrite(12,LOW);
   }
 if(sec==616){
   digitalWrite(12,HIGH);//pitido a los 28 seg
   }
 if(sec==624){
    digitalWrite(12,LOW);
   }  
 if(sec==638){
   digitalWrite(12,HIGH);//pitido a los 29 seg
   }
 if(sec==651){
    digitalWrite(12,LOW);
   }   
  if(sec==660){
   digitalWrite(12,HIGH);//pitido a los 30 seg
   }
  if(sec==672){
    digitalWrite(12,LOW);
    ONOFF=2; // 
    Serial.println("SEGURIDAD ACTIVADA");
   }
}
 
char getkey(void){
char tecla=0;

int y;  
  for(y=0;y<=3;y++){
    
    if(y==0)
        {
          digitalWrite(2,LOW);digitalWrite(3,HIGH);digitalWrite(4,HIGH);digitalWrite(5,HIGH);
          delay(10);
          buttonState = digitalRead(6);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("C");
          tecla='C';

          } 
          buttonState = digitalRead(7);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("B");
          tecla='B';
          } 
          buttonState = digitalRead(8);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("0");
          tecla='0';
          } 
          buttonState = digitalRead(9);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("A");
          tecla='A';
          } 
          }

    if(y==1)
          {
          digitalWrite(2,HIGH);digitalWrite(3,LOW);digitalWrite(4,HIGH);digitalWrite(5,HIGH);
          delay(10);
          buttonState = digitalRead(6);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("D");
          tecla='D';
          } 
          buttonState = digitalRead(7);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("9");
          tecla='9';
          } 
          buttonState = digitalRead(8);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("8");
          tecla='8';
          } 
          buttonState = digitalRead(9);
          if (buttonState == LOW) {
          delay(250);
          //Serial.println("7");
          tecla='7';
          } 
          }
          
    if(y==2){
          digitalWrite(2,HIGH);digitalWrite(3,HIGH);digitalWrite(4,LOW);digitalWrite(5,HIGH);
          delay(10);
          buttonState = digitalRead(6);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("E");
          tecla='E';
          } 
          buttonState = digitalRead(7);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("6");
          tecla='6';
          } 
          buttonState = digitalRead(8);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("5");
          tecla='5';
          } 
          buttonState = digitalRead(9);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("4");
          tecla='4';
          } 
          }
          
    if(y==3){
          digitalWrite(2,HIGH);digitalWrite(3,HIGH);digitalWrite(4,HIGH);digitalWrite(5,LOW);
          delay(10);
          buttonState = digitalRead(6);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("F");
          tecla='F';
          } 
          buttonState = digitalRead(7);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("3");
          tecla='3';
          } 
          buttonState = digitalRead(8);
          if (buttonState == LOW) 
          {
          delay(250);
          //Serial.println("2");
          tecla='2';
          } 
          buttonState = digitalRead(9);
          if (buttonState == LOW) {
          delay(250);
          //Serial.println("1");
          tecla='1';
          } 
          }
          }

  
  return tecla;
}
void loop() {
  if (error == 3) {
    Serial.println("TELCADO BLOQUEADO");
    delay(1);
    bloqueo++;
    Serial.print("Tiempo de bloqueo: ");
    int temp = 1320 - bloqueo;
    Serial.println(temp);
  }
  
  if(bloqueo == 1320) {
    error = 0;
    bloqueo = 0;
    Serial.println("TELCADO DESBLOQUEADO");
  }
  
  static char index = 0;
  char t;
  t = getkey();
  if (t != 0 && bloqueo == 0 && t != 'A' && t != 'B' && t != 'C' && t != 'D' && t != 'E' && t !='F' ) {
    pass[index] = t;
    Serial.print("*");
    index++;
    
    if (index == 4 && error != 3) {
      pass[index]='\0';
      //Serial.print("El codigo es: ");
      //Serial.println(pass);
      index = 0;
      
      if (strcmp (pass,code)==0) {
        Serial.println("Codigo correcto");
        error = 0;
        pit=0;
      }
      else {
        Serial.println("Codigo incorrecto");
        error++;
        bep=0;
      }
    }
  }
  if(t == 'A' && strcmp (pass,code) == 0 && ONOFF == 0){
  Serial.println("Alarma ACTIVADA");
  sec=0;
  ONOFF=1;
  memset(pass,0,5);
  error=0; //pulsando al final la A en el teclado una vez metido el codigo correcto nos dira que esta activada
  }
 if(t == 'F' && strcmp (pass,code) == 0 && (ONOFF == 1 || ONOFF == 2)){
  Serial.println("Alarma DESACTIVADA"); 
  ONOFF=0;
  memset(pass,0,5); 
  error=0; // se mete el codigo y se pulsa la F, nos dice que la alarma se desactiva
  pit=0;
 
  }
  if(ONOFF==1){
  Activacion();
  }
 
 if((error==1 || error==2 || error==3) && error!=0){
   beep();
  }
 if((t == 'F' && strcmp (pass,code) == 0) && error==0 ){
   pit++;
   pitido();
  
 }
}

