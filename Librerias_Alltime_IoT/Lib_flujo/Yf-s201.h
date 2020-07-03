
#ifndef Yfs201_h
#define Yfs201_h
#include "Arduino.h"


class Yfs201
{
  public:
    void ContarPulsos();

    Yfs201(int pin);
    String flujo();
    volatile int NumPulsos; //variable para la cantidad de pulsos recibidos
  private:


};


#endif
