
//*******************************************************Configuracion del sistema****************************************************

//-----------------------------------Declaracion de librerias--------------------------------

#include "Wemosd1.h"
Wemosd1_r1 Alltime;//instacia de la libreria

//-----------------------------------Declaracion de variables--------------------------------

 
const char* key = "ukxEV";const char* usuario = "irtSb";const char* pasw = "irtSb_iotalltime"; // datos de conexion con la plataforma

char ssid[] = "AP 36"; char pass[] = "002002Gi"; // datos de conexion WIFI



#define swicht "Lbv" //apuntador de conexion a widget en la plataforma swicht 
#define sensordata  "Yj" // apuntador de conexion a widget en la plataforma sensor



//------Pin de salida digital -------------------

int Pin_reflexivo = D7; //Declaração de pinos do sensor 
int buzzer = D3; //Declaração de entrada digital buzzer

//-----------------------------------Setup --------------------------------

void setup() {

  Alltime.setup (ssid, pass, key, usuario, pasw); //Rotina padrão de configuração da plataforma e conexão wifi ,  conexão mqtt

  Alltime.suscripcion(swicht, buzzer); // subscriber mqtt e declaração de pino do buzze como saída
  
  pinMode(Pin_reflexivo, INPUT);//Declaração como entrada do pino em que o sensor está conectado
}

//*****************************************************inicio del programa**************************************************************

//-----------------------------------Programa principal----------------------------------------

void loop() {
      
if (Alltime.Leer(swicht) == "1")//  envia 1 para ativar todo o sistema
  {
    
   if (digitalRead(Pin_reflexivo) == LOW) { // verifica o status do sensor e somente entra no "if" quendo altera seu estado para alto.
    
      digitalWrite(buzzer, HIGH); 

      Alltime.Enviar("1", sensordata); // envia o status do sensor para a plataforma ON
      delay (1000);//Tempo de espera

      Alltime.Enviar("0", sensordata); //envia o status do sensor para a plataforma OFF

    }
    digitalWrite(buzzer, LOW); //desliga o buzzer
}

}

  


//*******************************************************fin del programa**************************************************************
