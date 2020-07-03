
#include "Arduino.h"
#include "luz_ldr.h"

float temp_promedio=0;
float tempC=0;

luz_ldr::luz_ldr(int pin)
{
    //pinMode(pin, OUTPUT);
    _pin = pin;
}

float luz_ldr::luz_ard()
{

   temp_promedio=0;
   tempC=0;
   for (int i = 0; i <= 255; i++) {
   tempC = analogRead(_pin);
   temp_promedio= temp_promedio+tempC;
   }
   
   tempC= temp_promedio/255;
   tempC = map(tempC, 0, 1023, 100, 0); // conversion de datos del sensor a porcentaje

   delay(100);
   return tempC;
}



float luz_ldr::luz_esp()
{
   temp_promedio=0;
   tempC=0;
   for (int i = 0; i <= 255; i++) {
   tempC = analogRead(_pin);
   temp_promedio= temp_promedio+tempC;
   }
   
   tempC= temp_promedio/255;
   tempC = map(tempC, 0, 1023, 100, 0); // conversion de datos del sensor a porcentaje

   delay(100);
   return tempC;
}


float luz_ldr::luz_esp32()
{
   temp_promedio=0;
   tempC=0;
   for (int i = 0; i <= 255; i++) {
   float tempC = analogRead(_pin);
   temp_promedio= temp_promedio+tempC;
   }
   
   tempC= temp_promedio/255;
   tempC = map(tempC, 0, 4095, 100, 0); // conversion de datos del sensor a porcentaje

   delay(100);
   return tempC;
}




