#ifndef Ethernetshield_UNO
#define Ethernetshield_UNO
#include <SoftwareSerial.h>
#include <PubSubClient.h>
#include "Arduino.h"
#include <TinyGPS.h>

class Ethernetshieldws //Definicion de la clase
{
  
  public:

    void setup(const char* key,const char* usuario,const char* pass );
    String data ;
    String data1 ;
    int activado;
    
    //--------Robot
    void Robot (String motor);
    
    void robot_pin(int pin1,int pin2,int pin3,int pin4);
     
    //--------GPS
    String latitud = ""; //variable de almacenamiento de la latitud
    String longitud = ""; //variable de almacenamiento de la longitud
    void enviarGPS(String outtopic);
    void datosGPS();
    void gp(int pintxx,int pinrxx);
        
    //------------conexiones mqtt
    String Leer(String var);
    void Enviar(String data ,String outtopic);
    void suscripcion(String suscripcion,byte salida);
    void resuscripcion();
    String Lectura_serial();
    
 
  private:
    void CloseEthernet ();
    void Reconexion();
    String motores ;
    


};
#endif


  


