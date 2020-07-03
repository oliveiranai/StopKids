#ifndef Sensor_de_pulso_cardiaco
#define Sensor_de_pulso_cardiaco
#include <SoftwareSerial.h>
#include "Arduino.h"


class Sensorcardiaco //Definicion de la clase
{
  public:

    void leer_pulso_cardiaco();
    void configuracion(int);
    int cardiaco;  
    
  private:

    void ledFadeToBeat();
    void serialOutput();
    void serialOutputWhenBeatHappens();
    void arduinoSerialMonitorVisual(char, int);
    void sendDataToSerial (char,int);
    

};
#endif
