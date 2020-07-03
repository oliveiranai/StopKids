
//**********************************Declaracion de librerias****************************************************************

#define TINY_GSM_MODEM_SIM900
#include "Arduino.h"
#include "GSM_Sim900_shield_UNO.h"
#include <TinyGPS.h>
#include <TinyGsmClient.h>
#include <PubSubClient.h>
#include <FlexiTimer2.h>

SoftwareSerial Sim900(7, 8); // Declaracion de los pines serial del modulo gms
TinyGsm modem(Sim900);
TinyGsmClient cliente(modem);
PubSubClient mqtt(cliente);
TinyGPS gps;


//***********************************Configuracion del sistema****************************************************************
//-----------------declaracion de variables -------------------------------


String Change1 = "";
String Change2 = "";
String Change3 = "";

String cadena; //variable donde se almacena la cadena a enviar

String response;//variable del sistema
//const char* mqtt_server = "199.89.54.191";
const char* mqtt_server = "alltimetech.com.co";
String operador = "" ; //variable para almacenar el operador movil
byte a = 0 ;
float flat, flon ; // Declaracion de variables a usar latitud, longitud ,altura y precision
String idcliente;
String idcliente2;
const char* usuarios;
const char* pass2;
const char* ap;
const char* us;
const char* pas;
int flag;
int conex=0;
String compara[7];
String comparar;
String datain[7];
int bandera = 1;
int bandera2 = 2;
byte cont ;
int cont2 = 0 ;

String entrada;
String enviado[7];
int envios;

int  inpin1;
int  inpin2;
int  inpin3;
int  inpin4;

int pintxx = 0;
int pinrxx = 0;

void flash() {


  bandera = 1;
  bandera2++;
  envios = 0;
  if (envios == 0) {

    enviado[0] = "";
    enviado[1] = "";
    enviado[2] = "";
    enviado[3] = "";
    enviado[4] = "";
    enviado[6] = "";
    enviado[7] = "";

  }


}


//****************************rutina de recepcion de datos mqtt************************************

void mqttCallback(char* topic, byte* payload, unsigned int length) {

  response = "";

  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    char c = (char)payload[i];  //lecturas del modulo client
    response += c ;
  }

  comparar = topic;
  //Serial.print(comparar);

  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = comparar.length() - 1;

  for (int i = 0; i <= maxIndex && found <= 4; i++) {
    if (comparar.charAt(i) == '/' || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  comparar = comparar.substring(strIndex[0], strIndex[1]);


  for (int i = 0; i <= cont; i++) {
    if (comparar == compara[i]) {

      datain[i] = response;
      //Serial.print(datain[i]);

    }
  }

}


//------------------Rutina de setup-------------------------

void GSMshield_Sim900::setup(const char apn [], const char usuario [], const char password [], const char* key, const char* user, const char* pass) {

  Serial.begin(9600); // inicio de puero serial

  FlexiTimer2::set(30000, 1.0 / 1000, flash);



  delay(1000);
  Sim900.begin(9600); //inicio del modulo
  delay(3000);
  idcliente2 = key;
  usuarios = user;
  pass2 = pass;
  ap = apn;
  us = usuario;
  pas = password;

  Serial.println(F("Bienvenido.. al sistema Alltime IOT (www.alltimetech.com.co)"));
  Serial.println(F("************************************************************"));

  for (double i = -1; i <= 13; i++) { // pone todos los led en cero de los puertos
    digitalWrite(i, LOW);
  }

  Serial.println (F("1- Buscando red Movil "));
  Serial.println();

  do
  {

    Sim900power();

  } while (modem.getSignalQuality() > 50);

  modem.restart();
  
  do
  { conex++;
   
   
  if (conex==30) {
    Serial.println();
    Serial.println();
    Serial.println(F("1.2-Falla en la conexion con la red movil, revise su simcard"));
    do  {

    } while (a <= 0);
    while (true);
  }


  } while (!modem.waitForNetwork());

    
  Serial.print (F("2- Conectando a la red del operador: "));
  Serial.println(modem.getOperator());
  Serial.println();

  conex=0;
 
  do
  { 
    conex++;


  if (conex==30) {
    Serial.println(F(" 2.1- Fallo en la conexion revise apn, user ,password "));
    int a = 0 ;
    do  {

    } while (a <= 0);
  }

  } while (!modem.gprsConnect(apn, usuario, password));


  Serial.println(F("3- Equipo conectado a la red movil"));
  Serial.println();


  Serial.println(F("4- Conectando a la plataforma Alltime IOT"));
  Serial.println();

  char buffer1[10];

  do
  { 

   do
  { 
    
  } while (!modem.gprsConnect(apn, usuario, password));



   Serial.print(".");
  mqtt.setServer(mqtt_server, 11000);
  mqtt.setCallback(mqttCallback);

  idcliente = key + String (random(99999));

  

  idcliente.toCharArray(buffer1, 10);
  

} while (!mqtt.connect(buffer1, user, pass));
  

  if (mqtt.connect(buffer1, user, pass)) {

    Serial.println(F("4.1- Conectado"));
    Serial.println();

    Serial.println(F("5- Bienvenido.. esta usted conectado a Alltime IOT"));
    FlexiTimer2::start();

  }

  else {
    Serial.println(F("4.1- Falla en conexion con el servidor Alltime IoT... reinicie arduino"));

    do  {

    } while (a <= 0);
    while (true);
  }


}



//***********************************Envio de datos ****************************************************************


//-------------------Rutina para envio GPS ---------------------

void GSMshield_Sim900::enviarGPS(String outtopic)
{    
   

  if (flag==1) {
     if (Change1 != latitud || Change2 != longitud ) { // compara si existe un cambio de estado
     if (!mqtt.connected()) {
      Reconexion ();
    }
    bandera2=0;
    flag=0;

    char buffer1[50];
    String cadena;

    cadena = "";
    cadena = ( "{""\"dato\""  + String (":") + "{""\"lat\""  + String (":") + "\"" + latitud + "\"" + String (",") + "\"lon\"" + String (":") + "\"" + longitud + "\"" + "}" + "}");

    cadena.toCharArray(buffer1, 50);

    String envio = ("pub/") + idcliente2 + ("/") + usuarios + ("/") + outtopic;

    char buffer[30];
    envio.toCharArray(buffer, 30);
    //Serial.println(buffer);
    //Serial.println(buffer1);

    mqtt.publish(buffer, buffer1 );
    Serial.flush();
    Sim900.flush();


    }

    
    Change1 = latitud;
    Change2 = longitud;
  }
}


//*****************************************************************************************************************


//---------------------------------Rutina para encender el modulo ------------------------------------

void GSMshield_Sim900::Sim900power()
// Encendido por software del mySerial, es equivalente a precionar el boton de encendido
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(2000);
}


//******************************************************************

String GSMshield_Sim900::Leer(String var)
{
  if (!mqtt.connected()) {
    Reconexion ();
    resuscripcion();
  }



  for (int i = 0; i <= cont; i++) {

    if (var == compara[i]) {

      data = datain[i];

    }

  }

  mqtt.loop();
  delay(50);
  return data;

}

//********************************Rutina de suscripciones****************************
void GSMshield_Sim900::suscripcion(String suscripcion, byte salida)
{ delay(500);
  cont++;

  compara[cont] = suscripcion;


  entrada = ("sub/") + idcliente2 + ("/") + usuarios + ("/") + suscripcion;

  pinMode(salida, OUTPUT);

  //Serial.println(entrada);

  char buffer[30];
  entrada.toCharArray(buffer, 30);
  //Serial.println(buffer);
  mqtt.subscribe(buffer);

}


//*****************************************************************

void GSMshield_Sim900::Enviar(String data, String outtopic)
{   mqtt.loop();

  if (envios <= 7) {

    for (int i = 0; i <= envios; i++) {

      if (enviado[i] != outtopic) {

        bandera = 1;

      }

      if (enviado[i] == outtopic) {

        bandera = 0 ;

        break;

      }

    }
    envios++;

  }



  if (bandera == 1) {

    delay(200);



    if (!mqtt.connected()) {
      Reconexion ();
    }


    char buffer1[50];
    String cadena;


    cadena = "";
    cadena = "{""\"dato\"" + String (":") + "\"" + data + "\"" + "}";
    cadena.toCharArray(buffer1, 30);


    String envio = ("pub/") + idcliente2 + ("/") + usuarios + ("/") + outtopic;

    char buffer[30];
    envio.toCharArray(buffer, 30);
    //Serial.println(buffer);
    //Serial.println(buffer1);

    mqtt.publish(buffer, buffer1 );


    data = "";


    Serial.flush();
    Sim900.flush();

    bandera = 0;
    bandera2 = 0;

    enviado[envios] = outtopic;

  }

}

//-------------------Rutina de datos GPS----------------------


void GSMshield_Sim900:: datosGPS() {


   mqtt.loop();
    
  if (bandera2 >= 2) {
    Sim900.end();
    delay(1000);
    SoftwareSerial Gps(pintxx, pinrxx); // TX| RX
    Gps.begin(9600); // inicio del serial del gps

    Serial.println ();
    Serial.println(F(" GPS- Esperando conexion con los satelites"));//Muestra en el puerto serial
    do {
      latitud = "0";
      longitud = "0";

      
      bool newdata = false;
      unsigned long start = millis();
      while (millis() - start < 5000) {//5g para leer los datos del gps
        mqtt.loop();
        if (Gps.available()) {
          char c = Gps.read();
          if (gps.encode(c)) {
            newdata = true;
          }
        }
      }
      if (newdata) {
        Serial.println(F("Capturando datos GPS"));//Muestra en el puerto serial
        gps.f_get_position(&flat, &flon);//llama la latitud y longitud

        latitud = String(flat, 5 );
        longitud = String(flon, 5);
        //Serial.println ("He capturado los datos");
        //Serial.println (longitud);



      }
    } while (flat <= 0); // sale de la rutina cuando el modulo toma datos gps





    Gps.end();




    delay(1000);
    Sim900.begin(9600);//inicia  Sim900

    if (gps.f_speed_kmph()<=5){

      cont2++;
       }
    else {

      cont2=0;
      }
          
      

      if (latitud!="0" && cont2<=1 ) {
      flag = 1;
      
    
    }

  }


}



//-------------control de motores -----------------

void GSMshield_Sim900::Robot(String motor)
{

  if (Change3 != motor) {

    if  (motor == ("\"sto\"")) {

      digitalWrite (inpin1, LOW);
      digitalWrite (inpin2, LOW);

      digitalWrite (inpin3, LOW);
      digitalWrite (inpin4, LOW);
    }
    if  (motor == ("\"atr\"")) {

      digitalWrite (inpin1, HIGH);
      digitalWrite (inpin2, LOW);


      digitalWrite (inpin4, HIGH);
      digitalWrite (inpin3, LOW);
    }
    if  (motor == ("\"ade\"")) {

      digitalWrite (inpin2, HIGH);
      digitalWrite (inpin1, LOW);


      digitalWrite (inpin3, HIGH);
      digitalWrite (inpin4, LOW);
    }
    if  (motor == ("\"der\"")) {

      digitalWrite (inpin1, LOW);
      digitalWrite (inpin2, HIGH);

      digitalWrite (inpin3, LOW);
      digitalWrite (inpin4, LOW);


    }
    if  (motor == ("\"izq\"")) {

      digitalWrite (inpin1, LOW);
      digitalWrite (inpin2, LOW);

      digitalWrite (inpin3, HIGH);
      digitalWrite (inpin4, LOW);


    }

    if  (motor == ("\"m1d\"")) {

      digitalWrite (inpin1, HIGH);
      digitalWrite (inpin2, LOW);

    }


    if  (motor == ("\"m1i\"")) {

      digitalWrite (inpin2, HIGH);
      digitalWrite (inpin1, LOW);


    }


    if  (motor == ("\"m1s\"")) {

      digitalWrite (inpin2, LOW);
      digitalWrite (inpin1, LOW);


    }


    if  (motor == ("\"m2d\"")) {

      digitalWrite (inpin3, HIGH);
      digitalWrite (inpin4, LOW);

    }


    if  (motor == ("\"m2i\"")) {

      digitalWrite (inpin4, HIGH);
      digitalWrite (inpin3, LOW);


    }

    if  (motor == ("\"m2s\"")) {

      digitalWrite (inpin4, LOW);
      digitalWrite (inpin3, LOW);

    }
    Change3 = motor;
  }

}

//-----------rutina para pines de robot--------------------------

void GSMshield_Sim900::robot_pin(int pinr1, int pinr2, int pinr3, int pinr4)
{
  inpin1 = pinr1;
  inpin2 = pinr2;
  inpin3 = pinr3;
  inpin4 = pinr4;

  pinMode(inpin1, OUTPUT);
  pinMode(inpin2, OUTPUT);
  pinMode(inpin3, OUTPUT);
  pinMode(inpin4, OUTPUT);


}

//-----------rutina para pines gps--------------------------

void GSMshield_Sim900::gp(int gpintx, int gpinrx)
{
  pintxx = gpintx;
  pinrxx = gpinrx;


}

//-----------rutina para lectura serial--------------------------

String GSMshield_Sim900::Lectura_serial()
{


  char c ;
  String console;
  console = "";

  while (Serial.available())
  {


    do {
      c = Serial.read();
      if (c!='\n'){
    console += c;
    }


    } while (c = !'\n');
    

  }
  data1 = console;
  return data1;


}



//-----------rutina para reconexion--------------------------

void GSMshield_Sim900::Reconexion ()
{

  
 Serial.println("reconexion");
 

  
  while (!mqtt.connected()) {

    
    

    mqtt.setServer(mqtt_server, 11000);
    mqtt.setCallback(mqttCallback);

    idcliente = usuarios + String (random(99999));
    char buffer1[10];

    idcliente.toCharArray(buffer1, 10);

    if (modem.gprsConnect(ap, us, pas)){
    mqtt.connect(buffer1, usuarios, pass2);
    
}

  }



}

//----------------resucripcion-------------

void GSMshield_Sim900::resuscripcion()

{

  for (int i = 0; i < cont; i++) {


    entrada = ("sub/") + idcliente2 + ("/") + usuarios + ("/") + compara[cont];

    // Serial.println(entrada);

    char buffer[30];
    entrada.toCharArray(buffer, 30);
    //Serial.println(buffer);
    mqtt.subscribe(buffer);

  }

}


//----rutina para Gps por triangulacion---------------

void GSMshield_Sim900::triagulacion_GPS()

{   mqtt.loop();

  if (bandera2 > 1) {

    Serial.println(F("Gps por triangulacion de antenas"));

    String tri = modem.getGsmLocation();

    longitud = tri.substring(2, 11);

    latitud = tri.substring(13, 20);

    flag=1;
       

    

    
  }

}
