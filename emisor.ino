#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10
#define PIN_VRx A0
#define PIN_VRy A1
 
//Variable con la dirección del canal por donde se va a transmitir
byte direccion[5] ={'r','e','s','c','u'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector con los datos a enviar
int datos[1];

int x, y;
int x_ang, y_ang;
void setup()
{
  //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
 
radio.setChannel(100);
radio.setPALevel(RF24_PA_MIN);
//Abrimos un canal de escritura
 radio.openWritingPipe(direccion);
 
}
 
void loop()
{ 
 x = analogRead(PIN_VRx);
  y = analogRead(PIN_VRy);

  x_ang = map( x, 0, 1023, 0, 1000 );
 
  y_ang = map( y, 0, 1023, 0, 1000 );

   //cargamos los datos en la variable datos[]
if(y_ang>=800 && 300<=x_ang<=800 )//adelante
 {
  datos[0]=1;
 // Serial.println("1");
 }
 else
 {
  if(y_ang<=300 && 300<=x_ang<=800)//atras
  {
     datos[0]=3;
    //Serial.println("3");

  }
  else{
    if(x_ang>=800 && 300<=y_ang<=800 )//derecha
    {
       datos[0]=4;
     // Serial.println("4");

    }
    else{
     if(x_ang<=300 && 300<=y_ang<=800 )//izquierda
     {
       datos[0]=5;
    //  Serial.println("5");

     }
     else//quieto
     {
       datos[0]=2;
 //Serial.println("2");
     }
    }
  }
 }

 

//  bool ok = radio.write(datos, sizeof(datos));
radio.write(datos, sizeof(datos));
  //reportamos por el puerto serial los datos enviados 
  // if(ok)
  // {
  //    Serial.println("Datos enviados: "); 
  //    Serial.println(datos[0] ); 
     

  // }
  // else
  // {
  //    Serial.println("no se ha podido enviar");
  // }
  //delay(500);
}
 
