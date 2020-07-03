#ifndef GSMshieldhttp_h
#define GSMshieldhttp_h
#include <SoftwareSerial.h>
#include "Arduino.h"


class GSMshield_Sim900 //Definicion de la clase
{
  public:
    //Constructor de la clase

    void setup(const char apn [],const char usuario [], const char password [],const char* id, const char* user, const char* pass);
        
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
    void triagulacion_GPS ();
    void gp(int pintx,int pinrx);

    
    String Leer(String var);
    void Enviar(String data ,String outtopic);
    void suscripcion(String suscripcion,byte salida);
    
    String Lectura_serial();
    


  private:
    void resuscripcion();
    void Sim900power();
    String motores ;
    void Reconexion();
    

};
#endif
