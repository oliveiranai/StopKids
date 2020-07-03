#ifndef Wemosd1
#define Wemosd1
#include <SoftwareSerial.h>
#include "Arduino.h"


class Wemosd1_r1//Definicion de la clase
{
  public:
    //Constructor de la clase

    void setup(const char* red , const char* pass, const char* key, const char* usuario, const char* pasw);
    String data;
    String data1 ;
    int activado;
    //--------Robot

    void Robot (String motor);
    void robot_pin(int pin);
    

    //--------GPS
    String latitud = "null"; //variable de almacenamiento de la latitud
    String longitud = "null"; //variable de almacenamiento de la longitud
    void enviarGPS(String outtopic);
    void datosGPS();
    void gp(int pintx,int pinrx);

    
     //------------conexiones mqtt
    String Leer(String var);
    void Enviar(String data ,String outtopic);
    void suscripcion(String suscripcion,byte salida);
    void resuscripcion();
    String Lectura_serial();


  private:
       void CloseWIFI( );
       String motores ;
       void Reconexion();
       

};
#endif
