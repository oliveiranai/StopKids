
//**********************************Declaracion de librerias****************************************************************
#include "Arduino.h"
#include "Ethernetshield_UNO.h"
#include <SPI.h>
#include <Ethernet.h>
#include <FlexiTimer2.h>



#include <TinyGPS.h>



//*********************************Declaracion de instancias*****************************************************************

TinyGPS gps;

Ethernetshieldws IOT;
EthernetClient client;
PubSubClient cliente(client);


//IPAddress mqtt_server(199,89,54,191);
const char* mqtt_server = "alltimetech.com.co";
//IPAddress mqtt_server(alltimetech.com.co);
IPAddress ip(192, 168, 0, 152);

//***********************************Configuracion del sistema****************************************************************
//----------------------------------------------------------------

String Change1 = "";
String Change2 = "";
String Change3 = "";

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };// declaracion de macc del dispositivo ethernet
String response;//variable del sistema
int a;
float flat, flon ; // Declaracion de variables a usar latitud, longuitud ,altura y precision
String idcliente;
String idcliente2;
const char* usuarios;
const char* pass2;
String compara[7];
String comparar;
String datain[7];
int bandera=1;
int bandera2=2;
int cont ;
int cont2 ;
int cont3 ;
int flag = 0;
String entrada;
int envios;
String enviado[7];

int  inpin1;
int  inpin2;
int  inpin3;
int  inpin4;

int pintxx=0;
int pinrxx=0;


void flash() {

  bandera=1;
  bandera2++;
envios=0;
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

//***********************************rutina para escuchar  los mensajes que llegan desde el servidor Mqtt

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
      //Serial.println (datain[i]);

    }
  }

  if (response == "exec600") {
    Serial.println ("Nota : has Alcanzado el numero maximo de envios gratis diarios ");
    do  {

    } while (a <= 0);
  }

}

//***************************************Configuracion del sistema****************************************

void Ethernetshieldws::setup(const char* key, const char* usuario, const char* pass) {

  
  Serial.begin(9600); // inicio de puero serial

  FlexiTimer2::set(30000, 1.0/1000, flash);
  FlexiTimer2::start();

  //cliente.setServer(mqtt_server, 1883); //srvidor de prueba
  cliente.setServer(mqtt_server, 11000);
  idcliente2=key;
  usuarios = usuario;
  pass2 = pass;

  cliente.setCallback(callback);

  Serial.println(F("Bienvenido.. al sistema Alltime IOT (www.alltimetech.com.co)"));
  Serial.println(F("************************************************************"));
  Serial.println();
  delay(5000);
  Serial.println(F("1- Por favor conecte el cable de red"));
  Serial.println();

  // Comienza la conexion

  if (Ethernet.begin(mac) == 0) {
    Serial.println("1.1- Error en conexion ");
    Ethernet.begin(mac, ip);
  }

  Serial.println(F("2- Cable de red conectado"));
  Serial.println();

  Serial.println(F("3- Conectando a la plataforma Alltime IOT"));
  Serial.println();

  idcliente=key+String (random(99999));

  char buffer1[10];

  idcliente.toCharArray(buffer1, 10);


  if (cliente.connect(buffer1, usuario, pass)) {

    Serial.println(F("3.1- Conectado"));
    Serial.println();

    //-------------Rutina para autenticacion del servidor-------

    Serial.println(F("4- Bienvenido.. esta usted conectado a Alltime IOT"));
    Serial.println();
  }

  else {
    Serial.println(F("3.1- Falla en conexion con el servidor Alltime IoT"));

do  {

    } while (a <= 0);

  }
}


//***********************************Envio de datos ****************************************************************

//----------------------------------------------------------------

void Ethernetshieldws::enviarGPS(String outtopic)
{

  if (flag==1) {

  if (!client.connected()) {

    Reconexion();

  }


  if (Change1 != latitud || Change2 != longitud ) { // compara si existe un cambio de estado
   
        
   
   data="gps";
   Enviar(data,outtopic );
   

  }

  Change1 = latitud;
  Change2 = longitud;
}}



//*****************************************************************************************************************

//-----------rutina para cerrar conexion--------------------------

void Ethernetshieldws::CloseEthernet ()
{
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    response = "";
  }
}


//********************************Rutina de entrada de datos mqtt****************************
String Ethernetshieldws::Leer(String var)

{

     
    if (!cliente.connected()) {
    Reconexion ();
    resuscripcion();
  }
      
    for (int i = 0; i <= cont; i++) {
      
            
      if (var == compara[i]) {
                  
              
        data = datain[i];

      }

    }

    cliente.loop();
    delay(200);
    
    return data;
 }


//********************************Rutina de suscripciones****************************
void Ethernetshieldws::suscripcion(String suscripcion,byte salida)
{ delay(500);
  cont++;
  
  compara[cont] = suscripcion;
  
  entrada = ("sub/") + idcliente2 + ("/") + usuarios + ("/") + suscripcion;

  pinMode(salida, OUTPUT);
    
  char buffer[30];
  entrada.toCharArray(buffer, 30);
  
  cliente.subscribe(buffer);

}


//********************************Rutina de envio de datos mqtt****************************
void Ethernetshieldws::Enviar(String data, String outtopic )
{ cliente.loop();
  
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

  

  
  if (!cliente.connected()) {
    Reconexion ();
  }

  

  String cadena;
  cliente.loop();
  char buffer1[48];

  if (flag == 0) {
    cadena = "{""\"dato\"" + String (":") + "\"" + data + "\"" + "}";
    cadena.toCharArray(buffer1, 40);
  }
  else
  {
    data = ( "{""\"dato\""  + String (":") + "{""\"lat\""  + String (":") + "\"" + latitud + "\"" + String (",") + "\"lon\"" + String (":") + "\"" + longitud + "\"" + "}" + "}");
    cadena = data;
    cadena.toCharArray(buffer1, 48);
  
    }

    

      String envio = ("pub/") + idcliente2 + ("/") + usuarios + ("/") + outtopic;

      
      char buffer[30];
      envio.toCharArray(buffer, 30);
      //Serial.println(buffer);
      //Serial.println(buffer1);
      
      cliente.publish(buffer, buffer1 );
      cliente.loop();
      

  
    flag = 0;
    bandera=0;
    bandera2=0;
    enviado[envios]=outtopic;


}  

  

}


//--------------------GPS-------------------------

void Ethernetshieldws:: datosGPS() {

  cliente.loop();

  if (bandera2 >= 2) {

  SoftwareSerial Gps(pintxx,pinrxx); // TX| RX
  
  Gps.begin(9600); // inicio del serial del gps
  Serial.println(F("GPS- Esperando conexion con los satelites"));//Muestra en el puerto serial
  do {
    latitud = "0";
    longitud = "0";

    //Serial.println("entre ");//Muestra en el puerto serial
    bool newdata = false;
    unsigned long start = millis();
    while (millis() - start < 5000) {//5g para leer los datos del gps
      if (Gps.available()) {
        char c = Gps.read();
        if (gps.encode(c)) {
          newdata = true;
        }
      }
    }
    if (newdata) {
      //Serial.println("Capturando datos ");//Muestra en el puerto serial
      gps.f_get_position(&flat, &flon);//llama la latitud y longitud
      latitud = String(flat, 5);
      //Serial.println (latitud);
      longitud = String(flon, 5);
      //Serial.println (longitud);

    }
  } while (flat <= 0); // sale de la rutina cuando el modulo toma datos gps

  Gps.end();
  flag=1;
}}

//-------------control de motores -----------------

void Ethernetshieldws::Robot(String motor)
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
Change3=motor;
}

}

//-----------rutina para pines de robot--------------------------

void Ethernetshieldws::robot_pin(int pinr1,int pinr2,int pinr3,int pinr4)
{
inpin1=pinr1;
inpin2=pinr2;
inpin3=pinr3;
inpin4=pinr4;

pinMode(inpin1, OUTPUT);
pinMode(inpin2, OUTPUT);
pinMode(inpin3, OUTPUT);
pinMode(inpin4, OUTPUT);



}

//-----------rutina para pines de robot--------------------------

void Ethernetshieldws::gp(int gpintx,int gpinrx)
{

 pintxx= gpintx;
 pinrxx= gpinrx;


}

//-----------rutina para lectura serial--------------------------

String Ethernetshieldws::Lectura_serial()
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

void Ethernetshieldws::Reconexion ()
{
  while (!client.connected()) {   

  if (Ethernet.begin(mac) == 0) {
    Serial.println("1.1- Error en reconexion");
    Ethernet.begin(mac, ip);
  }


  while (!client.connected()) {

   char buffer1[10];

   idcliente.toCharArray(buffer1, 10);


   if (cliente.connect(buffer1, usuarios, pass2)) {

    
   // Serial.println();

   }
    //Serial.print(".");
  } }

}

//----------------resucripcion-------------

void Ethernetshieldws::resuscripcion()

{

  for (int i = 0; i < cont; i++) {


    entrada = ("sub/") + idcliente2 + ("/") + usuarios + ("/") + compara[cont];

    // Serial.println(entrada);

    char buffer[30];
    entrada.toCharArray(buffer, 30);
    //Serial.println(buffer);
    cliente.subscribe(buffer);

  }

}



