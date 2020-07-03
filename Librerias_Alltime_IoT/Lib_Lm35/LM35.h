
#ifndef LM35_h
#define LM35_h
#include "Arduino.h"


class LM35
{
   public:
       LM35(int pin);
       float cel_ard();
       float cel_esp();
       float cel_esp32();

   private:
       int _pin;

};


#endif

