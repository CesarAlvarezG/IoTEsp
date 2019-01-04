/*
  Programa para el manejo de la familia ESP para la plataforma IoTView
  Esp32: ok

  Desarrollado por: César Augusto Álvarez Gaspar
  Fecha: 4 de enero de 2019

  Versión: 0.0.5
  Descripción: Programa para el monitoreo de humedad y temperatura, visualizado por medio de un pantalla OLED
*/


#include <dummy.h> //Libreria para identificar los pines del EPS32
#include "DHT.h"  //Libreria para el DHT11
#include <Wire.h>
#include "SSD1306Wire.h"//Libreria para el manejo de la pantalla OLED
#include "IotViewOled.h"//Libreria con interfaz grafica implementada en la pantalla OLED


#define LED_BUILTIN 27 
#define LED_TEST 0
#define TAZA_SERIAL 115200  //Velocidad por defecto en el ESP32
#define TAZA_MUESTREO 5000 //Taza minima para el sensor


#define DTHPIN 26      //Pin al que se conecto el sensor
#define DTHTYPE DHT11 //Tipo de sensor

//Declaración de objetos usados

DHT dht(DTHPIN, DTHTYPE); //Declaración del Objeto DHT
IotViewPantalla Figura;
SSD1306Wire  display(0x3c, 21, 22);


void setup() {
  // Inicialización de los pines.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_TEST, OUTPUT);
  
  //Inicialización de la comunicación serial
  Serial.begin(TAZA_SERIAL);
  Serial.println("\nPrograma para monitoreo de humedad y temperatura");
  
  //Inicialización del sensor
  dht.begin();
  
  //Inicialización de la pantalla OLED
  Figura.SetDisplay(&display);
  Figura.Maqueta();
  Figura.Display();
  Figura.SetTrabajoEtiqueta1("T [°C]");
  Figura.SetTrabajoEtiqueta2("H [%]"); 
  Figura.SetApoyoEtiqueta1("Ts");
  Figura.SetApoyoEtiqueta2("Iteracción");
  Figura.SetApoyoVar1(TAZA_MUESTREO);
  Figura.SetApoyoVar2(3);
  Figura.SetTrabajoVar1(2);
  Figura.SetTrabajoVar2(3); 
  
  //Inicialización del Serial Ploter
  Serial.print(0);
  Serial.print(",");
  Serial.println(0);
}


float h=0;//Humedad
float t=0;//Temperatura
int i=0;//Numero de iteracción

void loop() {
  //Lectura del sensor
  h=dht.readHumidity();
  t=dht.readTemperature();
  
  //Visualización de las lecturas
  Serial.print(h);
  Serial.print(",");
  Serial.println(t);
  
  //Visualización en la pantalla OLED
  Figura.SetTrabajoVar1(t);
  Figura.SetTrabajoVar2(h);
  Figura.SetApoyoVar2(i++);
  Figura.Display();  
  
  //Muestreo
  delay(TAZA_MUESTREO);  
}
