
#ifndef luz_ldr_h
#define luz_ldr_h
#include "Arduino.h"


class luz_ldr
{
   public:
       luz_ldr(int pin);
       float luz_ard();
       float luz_esp();
       float luz_esp32();

   private:
       int _pin;

};


#endif

