
#include "Arduino.h"
#include "LM35.h"

float temp_promedio=0;
float tempC=0;

LM35::LM35(int pin)
{
    //pinMode(pin, OUTPUT);
    _pin = pin;
}

float LM35::cel_ard()
{

   temp_promedio=0;
   tempC=0;
   for (int i = 0; i <= 255; i++) {
   tempC = ((analogRead(_pin))*5*100.0)/1023.0;
   temp_promedio= temp_promedio+tempC;
   }
   
   tempC= temp_promedio/255;

   return tempC;
}



float LM35::cel_esp()
{
   temp_promedio=0;
   tempC=0;
   for (int i = 0; i <= 255; i++) {
   tempC = (float(analogRead(_pin))*2.9*100.0)/1023.0;
   temp_promedio= temp_promedio+tempC;
   }
   
   tempC= temp_promedio/255;

   return tempC;
}


float LM35::cel_esp32()
{
   temp_promedio=0;
   tempC=0;
   for (int i = 0; i <= 255; i++) {
   float tempC = (float(analogRead(_pin))*3.3*100.0)/4095.0;
   temp_promedio= temp_promedio+tempC;
   }
   
   tempC= temp_promedio/255;
}




