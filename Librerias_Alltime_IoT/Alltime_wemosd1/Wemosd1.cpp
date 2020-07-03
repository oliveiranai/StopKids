#include "Arduino.h"
#include "Wemosd1.h"
#include <TinyGPS.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>  //Ticker Library

#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

Ticker blinker;
TinyGPS gps;
WiFiClient espclient;
PubSubClient client(espclient);


//***********************************Configuracion del sistema****************************************************************

String Change1 = ""; 
String Change2 = ""; 
String Change3 = ""; 

//-------------------------------------Declaracion de variables ------------------------

String response;//variable del sistema
int a = 0 ;
int status = WL_IDLE_STATUS;     // the Wifi radio's status
//const char* mqtt_server = "199.89.54.191";
const char* mqtt_server = "alltimetech.com.co";
float flat, flon ; // Declaracion de variables a usar latitud, longuitud ,altura y precision
String idcliente;
String idcliente2;
const char* usuarios;
const char* pasw2;
String compara[5];
String comparar;
String datain[5];
int bandera=1;
int bandera2=2;
int cont ;
int cont2 ;
int cont3 ;
int flag = 0;
String entrada;
const char* red2 ;
const char* pass2 ;
int envios;

int inpin[4]={1,2,3,4};
String enviado[7];
int pintxx=0;
int pinrxx=0;


void changeState()
{
  bandera=1;
  bandera2++;
  envios=0;
  
}



//****************************rutina de recepcion de datos mqtt************************************

void callback(char* topic, byte* payload, unsigned int length) {
  int i = 0;
  response = "";

  for (i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    char c = (char)payload[i];  //lecturas del modulo client
    response += c ;
  }

  

  comparar = topic;
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = comparar.length()-1;

  for(int i=0; i<=maxIndex && found<=4; i++){
    if(comparar.charAt(i)=='/' || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  comparar= comparar.substring(strIndex[0], strIndex[1]);


  for (int i = 0; i <= cont; i++) {
    if (comparar == compara[i]) {

      datain[i] = response;
      //Serial.println(datain[i]);

    }
  }

  if (response == "exec600") {
    Serial.println ("Nota : has Alcanzado el numero maximo de envios gratis diarios ");
    do  {

    } while (a <= 0);
  }

}



//-----------------------Rutina de setup------------------------

void Wemosd1_r1::setup(const char* red , const char* pass, const char* key, const char* usuario, const char* pasw) {

  Serial.begin(9600);

  
  blinker.attach(1,changeState);
  ArduinoOTA.setPassword((const char *)"alltimeiot");//Clave para acceso reprogramaci n

  
   WiFi.mode(WIFI_STA); // Tipo de seguridad
  

  idcliente2=key;
  
  usuarios = usuario;
  pasw2 = pasw;
  red2= red;
  pass2= pass;

  delay(3000);

  Serial.println(F("Bienvenido.. al sistema Alltime IOT (www.alltimetech.com.co)"));
  Serial.println(F("************************************************************"));
  
  delay(5000);
  Serial.println(F("1 -Esperando conexion Wifi"));
  Serial.println();
  Serial.print(F("    1.1 -Su red wifi es :"));
  Serial.println(red);
  Serial.println();
  Serial.print(F("    1.2 -Password de red :"));
  Serial.println(pass);
  Serial.println();
  Serial.print(F("    1.3 -Conectando"));

  WiFi.begin(red, pass);

  //---------------Espera de conexion WIfi--------------------------------

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    cont3++;
    Serial.print(".");
    if (cont3>15){
    Serial.println();
    Serial.println();
    Serial.print(F("    1.4 -Error en conexion Wifi"));
    while (cont3>15){

     delay(1000);

     }
     

     }
  }

  

  Serial.println();
  Serial.println();
  Serial.println(F("2- Conectado a la red Wifi"));
  Serial.println();

  client.setServer(mqtt_server, 11000);
  client.setCallback(callback);

  delay(500);


  Serial.println(F("3- Conectando a la plataforma Alltime IOT"));
  Serial.println();

  idcliente=key+String (random(99999));

  char buffer1[10];
  ArduinoOTA.setHostname("Mi IoT temperatura");

  idcliente.toCharArray(buffer1, 10);


  if (client.connect(buffer1, usuario, pasw)) {

    delay(500);
    Serial.println("3.1- Conectado");
    Serial.println();

    //-------------Rutina para autenticacion del servidor-------

    Serial.println(F("4- Bienvenido.. esta usted conectado a Alltime IOT"));
    Serial.println();
    ArduinoOTA.begin();
    
  }

  else {
    Serial.println("3.1- Falla en conexion con el servidor Alltime IoT");

  if (client.connect(buffer1, usuario, pasw)) {

    delay(500);
    Serial.println("3.1- Reconectado");
    Serial.println();

    //-------------Rutina para autenticacion del servidor-------

    Serial.println(F("4- Bienvenido.. esta usted conectado a Alltime IOT"));
    Serial.println();
    ArduinoOTA.begin();

}

  }

}

//***********************************Envio de datos ****************************************************************


//-------------------Rutina para envio GPS ---------------------

void Wemosd1_r1::enviarGPS(String outtopic)
{
  if (flag>=1) {

     
  if (!client.connected()) {

    Reconexion();

  }


  if (Change1 != latitud || Change2 != longitud ) { // compara si existe un cambio de estado
   
        
   
   data="gps";
   Enviar(data,outtopic );
   yield();

  }

  Change1 = latitud;
  Change2 = longitud;
}}



//*****************************************************************************************************************

//-----------rutina para cerrar conexion--------------------------

void Wemosd1_r1::CloseWIFI( )
{
  Serial.println("AT+CIPCLOSE");
  delay(1000);//retardo
  //readS();
}

//********************************Rutina de entrada de datos mqtt****************************
String Wemosd1_r1::Leer(String var)
{
  
  ArduinoOTA.handle();

  if (WiFi.status() != WL_CONNECTED){

    Reconexion();
    resuscripcion();

  }

  if (!client.connected()) {
    Reconexion ();
    resuscripcion();
  }

  

    for (int i = 0; i <= cont; i++) {

      if (var == compara[i]) {

        data = datain[i];

      }

    }

    client.loop();
    delay(200);
    ArduinoOTA.handle();
    return data;
  
}

//*****************************************************************************************************************

//-----------rutina para cerrar conexion--------------------------

void Wemosd1_r1::suscripcion(String suscripcion,byte salida)
{ delay(500);
  cont++;

  compara[cont] = suscripcion;


  entrada = ("sub/") + idcliente2 + ("/") + usuarios + ("/") +   suscripcion;

  pinMode(salida, OUTPUT);
  
  //Serial.println(entrada);

  char buffer[30];
  entrada.toCharArray(buffer, 30);
  //Serial.println(buffer);
  client.subscribe(buffer);

}



//********************************Rutina de envio de datos mqtt****************************
void Wemosd1_r1::Enviar(String data, String outtopic)
{

ArduinoOTA.handle();
client.loop();


 if (envios<=7){ 


for (int i = 0; i <= envios; i++) {

if (enviado[i]!=outtopic){

bandera=1;


}

if (enviado[i]==outtopic){ 

bandera=0 ;

break;

}

}


envios++;

}

activado=bandera;

if (bandera == 1) {


  

  if (WiFi.status() != WL_CONNECTED){

    Reconexion();

  }


  if (!client.connected()) {

    Reconexion();

  }

  
  String cadena;
  char buffer1[50];

  if (flag == 0) {
    cadena = "{""\"dato\"" + String (":") + "\"" + data + "\"" + "}";
    cadena.toCharArray(buffer1, 30);
  }
  else
  {
    data = ( "{""\"dato\""  + String (":") + "{""\"lat\""  + String (":") + "\"" + latitud + "\"" + String (",") + "\"lon\"" + String (":") + "\"" + longitud + "\"" + "}" + "}");
    cadena = data;
    cadena.toCharArray(buffer1, 50);

  }

  

    

      String envio = ("pub/") + idcliente2 + ("/") + usuarios + ("/") + outtopic;
      char buffer[30];
      envio.toCharArray(buffer, 30);
      //Serial.println(buffer);
      //Serial.println(buffer1);

      client.publish(buffer, buffer1 );

          
   enviado[envios]=outtopic;

    flag = 0;
    bandera=0;
    bandera2=0;


    if (envios==0){

enviado[0]="";
enviado[1]="";
enviado[2]="";
enviado[3]="";
enviado[4]="";
enviado[6]="";
enviado[7]="";


}

} 

}

//----------------------Rutina de datos GPS----------------------

void Wemosd1_r1:: datosGPS() {

   client.loop();  
   if (bandera2 >= 2) {

   Serial.println(F("GPS- Esperando conexion con los satelites"));//Muestra en el puerto serial
    
  delay(5000);
  Serial.end();
  
  delay(1000);
  SoftwareSerial Gps(pintxx,pinrxx); // TX| RX
  Gps.begin(9600); // inicio del serial del gps
  delay(5000);
  yield();

    
  latitud = "0";
  longitud = "0";
  

  do {
    bool newdata = false;
    yield();
    unsigned long start = millis();
    while (millis() - start < 5000) {//5g para leer los datos del gps
      
      yield();
      if (Gps.available()) {
        char c = Gps.read();
        if (gps.encode(c)) {
          newdata = true;
        }
      }
    }



    if (newdata) {
       yield();
      //Serial.println("Capturando datos ");//Muestra en el puerto serial
      gps.f_get_position(&flat, &flon);//llama la latitud y longuitud
      latitud = String(flat, 5);
      //Serial.println (latitud);
      longitud = String(flon, 5);
      //Serial.println (longitud);

    }
  } while (flat <= 0); // sale de la rutina cuando el modulo toma datos gps

  Gps.end();
  delay(200);
  Serial.begin(9600);//inicia  wifi esp8622
  flag=1;
  
}}

//-------------control de motores -----------------

void Wemosd1_r1::Robot(String motor)
{
  
  if (Change3 != motor) {

  if  (motor == ("\"sto\"")) {

    digitalWrite (inpin[1], LOW);
    digitalWrite (inpin[2], LOW);

    digitalWrite (inpin[3], LOW);
    digitalWrite (inpin[4], LOW);
  }
  if  (motor == ("\"atr\"")) {

    digitalWrite (inpin[1], HIGH);
    digitalWrite (inpin[2], LOW);
    

    digitalWrite (inpin[4], HIGH);
    digitalWrite (inpin[3], LOW);
  }
  if  (motor == ("\"ade\"")) {

    digitalWrite (inpin[2], HIGH);
    digitalWrite (inpin[1], LOW);
    

    digitalWrite (inpin[3], HIGH);
    digitalWrite (inpin[4], LOW);
  }
  if  (motor == ("\"der\"")) {

    digitalWrite (inpin[1], LOW);
    digitalWrite (inpin[2], HIGH);

    digitalWrite (inpin[3], LOW);
    digitalWrite (inpin[4], LOW);


  }
  if  (motor == ("\"izq\"")) {

    digitalWrite (inpin[1], LOW);
    digitalWrite (inpin[2], LOW);

    digitalWrite (inpin[3], HIGH);
    digitalWrite (inpin[4], LOW);


  }

  if  (motor == ("\"m1d\"")) {

    digitalWrite (inpin[1], HIGH);
    digitalWrite (inpin[2], LOW);

  }


  if  (motor == ("\"m1i\"")) {

    digitalWrite (inpin[2], HIGH);
    digitalWrite (inpin[1], LOW);


  }


  if  (motor == ("\"m1s\"")) {

    digitalWrite (inpin[2], LOW);
    digitalWrite (inpin[1], LOW);


  }


  if  (motor == ("\"m2d\"")) {

    digitalWrite (inpin[3], HIGH);
    digitalWrite (inpin[4], LOW);

  }


  if  (motor == ("\"m2i\"")) {

    digitalWrite (inpin[4], HIGH);
    digitalWrite (inpin[3], LOW);


  }

  if  (motor == ("\"m2s\"")) {

    digitalWrite (inpin[4], LOW);
    digitalWrite (inpin[3], LOW);

  }
Change3=motor;
}
  
}


//-----------rutina para pines de robot--------------------------

void Wemosd1_r1::robot_pin(int pin)
{
 cont2++;

inpin[cont2]=pin;
pinMode(inpin[cont2], OUTPUT);



}

//-----------rutina para pines de robot--------------------------

void Wemosd1_r1::gp(int gpintx,int gpinrx)
{

 pintxx= gpintx;
 pinrxx= gpinrx;
 




}

//-----------rutina para lectura serial--------------------------

String Wemosd1_r1::Lectura_serial()
{

char c ;
String console;
console="";

 while (Serial.available()) 
  {
  

do{
    c = Serial.read();

    if (c!='\n'){
    console += c;
    }


} while (c=!'\n');
   
  }

data1=console;
return data1;


}






//-----------rutina para reconexion--------------------------

void Wemosd1_r1::Reconexion ()
{





while (WiFi.status() != WL_CONNECTED) {
    

//Serial.println("Reconexion Wifi");    
delay(3000);



  }
  
client.setServer(mqtt_server, 11000);
client.setCallback(callback);

 
delay(5000);

idcliente=idcliente+String (random(99999));

char buffer1[10];

idcliente.toCharArray(buffer1, 10);

//Serial.println("Reconexion mqtt");    


if (client.connect(buffer1, usuarios, pasw2)) {

    delay(1000);
   
}



}

//----------------resucripcion-------------

void Wemosd1_r1::resuscripcion()

{

  for (int i = 0; i < cont; i++) {


    entrada = ("sub/") + idcliente2 + ("/") + usuarios + ("/") + compara[cont];

    // Serial.println(entrada);

    char buffer[30];
    entrada.toCharArray(buffer, 30);
    //Serial.println(buffer);
    client.subscribe(buffer);

  }

}
