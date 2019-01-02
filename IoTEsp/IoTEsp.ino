/*
  Programa para el manejo de la familia ESP para la plataforma IoTView
  Esp32: ok

  Desarrollado por: César Augusto Álvarez Gaspar
  Fecha: 2 de enero de 2019

  Versión: 0.0.1
  Descripción: Programa Blink para la tarjeta de desarrollo Geekworm
*/


#include <dummy.h> //Libreria para identificar los pines del EPS32

#define LED_BUILTIN 27 
#define LED_TEST 0
//#define LED_PIN 35 


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_TEST, OUTPUT);
}


void loop() {
  //Encender los led
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED_TEST, HIGH);
  delay(1000);//Esperar 1 segundo
  //Apagar los led
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_TEST, LOW);
  delay(1000);//Esperar 1 segundo
}
