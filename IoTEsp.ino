/*
  Programa para el manejo de la familia ESP para la plataforma IoTView
  Esp32: ok

  Desarrollado por: César Augusto Álvarez Gaspar
  Fecha: 2 de enero de 2019

  Versión: 0.0.3
  Descripción: Programa para el uso del puerto serial y graficación de 2 señales
*/


#include <dummy.h> //Libreria para identificar los pines del EPS32


#define LED_BUILTIN 27 
#define LED_TEST 0
#define TAZA_SERIAL 115200  //Velocidad por defecto en el ESP32
#define TAZA_MUESTREO 1000



void setup() {
  // Inicialización de los pines.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_TEST, OUTPUT);
  //Inicialización de la comunicación serial
  Serial.begin(TAZA_SERIAL);
  Serial.println("\nPrueba de puerto serial para ESP32");
}

int i=0;
float j=0;

void loop() {
  Serial.print(i++);
  Serial.print(",");
  j=i+random(-5,5);
  Serial.println(j++);
  delay(TAZA_MUESTREO);  
}
