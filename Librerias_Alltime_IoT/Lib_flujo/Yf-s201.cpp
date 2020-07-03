
#include "Arduino.h"
#include "Yf-s201.h"

int PinSensor = 2;    //Sensor conectado en el pin 2
float factor_conversion = 7.11; //para convertir de frecuencia a caudal
float volumen = 0;
long dt = 0; //variación de tiempo por cada bucle
long t0 = 0; //millis() del bucle anterior


String Yfs201::flujo()
{
  int frecuencia;
  NumPulsos = 0;   //Ponemos a 0 el número de pulsos
  interrupts();    //Habilitamos las interrupciones
  delay(1000);   //muestra de 1 segundo
  noInterrupts(); //Desabilitamos las interrupciones
  frecuencia = NumPulsos; //Hz(pulsos por segundo)

  float caudal_L_m = frecuencia / factor_conversion; 
  dt=millis()-t0; //calculamos la variaci�n de tiempo
  t0=millis();
  volumen=volumen+(caudal_L_m/60)*(dt/1000);

  return String (volumen);

}

Yfs201::Yfs201(int pin)
{
  pinMode(pin, INPUT);



}
