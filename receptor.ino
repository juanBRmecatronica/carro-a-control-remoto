#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
//Declaremos los pines CE y el CSN
#define CE_PIN 8
#define CSN_PIN 10
#define PWMA 5
#define PWMB 6
#define STBY 7
#define AIN1 4
#define AIN2 3
#define BIN1 2
#define BIN2 9  



  
//Variable con la dirección del canal que se va a leer  
byte direccion[5] ={'r','e','s','c','u'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector para los datos recibidos
int datos[1]; 

void setup()
{
   pinMode(PWMA, OUTPUT);
   pinMode(PWMB, OUTPUT);
   pinMode(STBY, OUTPUT);
   pinMode(AIN1, OUTPUT);
   pinMode(AIN2, OUTPUT);
   pinMode(BIN1, OUTPUT);
   pinMode(BIN2, OUTPUT);
 //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
  radio.setChannel(100);
 //radio.setPALevel(RF24_PA_MIN);
  //Abrimos el canal de Lectura
  radio.openReadingPipe(1, direccion);
  
    //empezamos a escuchar por el canal
  radio.startListening();

 
}
 
void loop() {
 uint8_t numero_canal;
 //if ( radio.available(&numero_canal) )
 if ( radio.available() )
 {    
     //Leemos los datos y los guardamos en la variable datos[]
     radio.read(datos,sizeof(datos));
     
     //reportamos por el puerto serial los datos recibidos
    // Serial.print("Dato0= " );
     //Serial.println(datos[0]);

      

    if(datos[0]==1){//adelante
   digitalWrite(STBY,HIGH );

          analogWrite(PWMA,255);
          analogWrite(PWMB,255);


    digitalWrite(AIN1,HIGH );
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);

    
    }
    if(datos[0]==2){//queto 
   digitalWrite(STBY,HIGH );

          analogWrite(PWMA,255);
          analogWrite(PWMB,255);

digitalWrite(AIN1,LOW);
digitalWrite(AIN2,LOW);
digitalWrite(BIN1,LOW);
digitalWrite(BIN2,LOW);
     }
    if(datos[0]==3){//atras
       digitalWrite(STBY,HIGH );

          analogWrite(PWMA,255);
          analogWrite(PWMB,255); 

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    }
     if(datos[0]==4){//derecha
   digitalWrite(STBY,HIGH );

          analogWrite(PWMA,255);
          analogWrite(PWMB,255);
    digitalWrite(AIN1,HIGH );
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    }
     if(datos[0]==5){//izquierda
       digitalWrite(STBY,HIGH );

          analogWrite(PWMA,255);
          analogWrite(PWMB,255);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    }
    
     if(datos[0]==6){//penal
       digitalWrite(STBY,HIGH );

          analogWrite(PWMA,255);
          analogWrite(PWMB,255);
    analogWrite(9,HIGH);
    analogWrite(10,LOW);
    analogWrite(5,HIGH);
    analogWrite(6,LOW);
    delay(3000);
   
    } 
  

   
 }
 else
 {
     Serial.println("No hay datos de radio disponibles!!!");
 }
}
