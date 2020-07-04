/*Realizado por  :Alltime Tech (www.alltimetech.com.co)

  Descripcion : Con este programa podra manipular todos tus sensores y actuadores en conjunto con el mismo controlador , a continuacion el sistema genera automaticamenta cada una
                de las variables y funciones para garantizar la conexion satisfactoria con la platafoma

      Hardware necesario :

      -Tarjeta Wemos R1 D1. https://www.prometec.net/wemos-d1-esp8266-wifi/ */

//*******************************************************Configuracion del sistema****************************************************

//-----------------------------------Declaracion de librerias--------------------------------

//Nota liberias: en esta seccion se deben declarar cada una de las librerias teniendo en cuenta las instrucciones dadas en el manual en la seccion multiwidget

#include "Wemosd1.h"
Wemosd1_r1 Alltime;//instacia de la libreria

//Aqui incluye tus librerias

//-----------------------------------Aqui se declaran los pines-------------------------------


//-----------------------------------Declaracion de variables--------------------------------
/*Nota pines: en esta seccion se declararn los pines de los sensores y actuadores que controlara el sistema .se debe tener en cuenta que algunos pines especiales 
              deben ser declarados de forma manual segun como dice el manual en la seccion multiwidget.*/

// byte Outpins[1] = {D0}; byte Inpins[1] = {D2}; const char* susc[1] = {"Lbv"};
 
const char* key = "ukxEV";const char* usuario = "irtSb";const char* pasw = "irtSb_iotalltime"; // datos de conexion con la plataforma

char ssid[] = "xxxxx"; char pass[] = "xxxxx"; // datos de conexion WIFI

//nombre de los Widgets para enviar datos desde el controlador hacia la plataforma (Sensores)
// apontador único e individual de conexão com widget sensor da plataforma
 #define sensor  "Yj"


//nombre de los Widgets para recibir datos desde la plataforma en el controlador (Actuadores)
//apontador único e individual de conexão com widget alarme da plataforma  
 #define Alarme  "Lbv"


//------Pin de salida digital -------------------

int Pin_reflexivo = D7; //Declaração do pino digital do sensor 
int buzzer = D3; //Declaração do pino digital do buzzer

//-----------------------------------Setup --------------------------------

void setup() {

  Alltime.setup (ssid, pass, key, usuario, pasw); //Rotina padrão de configuração da plataforma e conexão wifi , conexão mqtt

  Alltime.suscripcion(Alarme, buzzer); // subscriber mqtt e declaração de pino do buzze como saída
  
  pinMode(Pin_reflexivo, INPUT);//Declaração como entrada do pino em que o sensor está conectado
}

//*****************************************************inicio del programa**************************************************************

//-----------------------------------Programa principal----------------------------------------

void loop() {
      
if (Alltime.Leer(Alarme) == "1")//  envia 1 para ativar todo o sistema
  {
    
   if (digitalRead(Pin_reflexivo) == LOW) { // verifica o status do sensor e entra no "if" quando altera seu estado para LOW.
    
      digitalWrite(buzzer, HIGH); //ativa o buzzer

      Alltime.Enviar("1", sensor); // publica "1" para status do sensor e torna ON na plataforma 
      delay (1000);//Tempo de espera

      Alltime.Enviar("0", sensor; //publica "0" para status do sensor e torna Off na plataforma 
    }
    digitalWrite(buzzer, LOW); //desliga o buzzer
}

}

  


//*******************************************************fin del programa**************************************************************
