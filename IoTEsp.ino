/*
  Programa para el manejo de la familia ESP para la plataforma IoTView
  Esp32: ok

  Desarrollado por: César Augusto Álvarez Gaspar
  Fecha: 2 de enero de 2019

  Versión: 0.0.4
  Descripción: Programa para el monitoreo de humedad y temperatura
*/


#include <dummy.h> //Libreria para identificar los pines del EPS32
#include "DHT.h"  //Libreria para el DHT11


#define LED_BUILTIN 27 
#define LED_TEST 0
#define TAZA_SERIAL 115200  //Velocidad por defecto en el ESP32
#define TAZA_MUESTREO 5000 //Taza minima para el sensor

#define DTHPIN 26      //Pin al que se conecto el sensor
#define DTHTYPE DHT11 //Tipo de sensor

DHT dht(DTHPIN, DTHTYPE); //Declaración del Objeto DHT


void setup() {
  // Inicialización de los pines.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_TEST, OUTPUT);
  //Inicialización de la comunicación serial
  Serial.begin(TAZA_SERIAL);
  Serial.println("\nPrograma para monitoreo de humedad y temperatura");
  //Inicialización del sensor
  dht.begin();
  Serial.print(0);
  Serial.print(",");
  Serial.println(0);
}


float h=0;//Humedad
float t=0;//Temperatura


void loop() {
  //Lectura del sensor
  h=dht.readHumidity();
  t=dht.readTemperature();
  //Visualización de las lecturas
  Serial.print(h);
  Serial.print(",");
  Serial.println(t);
  //Muestreo
  delay(TAZA_MUESTREO);  
}
