/*
  Programa para el manejo de la familia ESP para la plataforma IoTView
  Esp32: ok

  Desarrollado por: César Augusto Álvarez Gaspar
  Fecha: 15 de enero de 2019

  Versión: 0.0.6
  Descripción: Programa para el monitoreo de humedad y temperatura, visualizado por medio de un pantalla OLED
               Prueba de paralelismo con los led LED_TEST y LED_BUILTIN
*/


#include <dummy.h> //Libreria para identificar los pines del EPS32
#include "DHT.h"  //Libreria para el DHT11
#include <Wire.h> //Libreria para el manejo del puerto I2C
#include "SSD1306Wire.h"//Libreria para el manejo de la pantalla OLED
#include "IotViewOled.h"//Libreria con interfaz grafica implementada en la pantalla OLED
#include <Ticker.h>//Libreria para el manejo de las tareas paralelas

#define LED_BUILTIN 27 
#define LED_TEST 0
#define TAZA_SERIAL 115200  //Velocidad por defecto en el ESP32
#define TAZA_MUESTREO 5000 //Taza minima para el sensor


#define DTHPIN 25      //Pin al que se conecto el sensor
#define DTHTYPE DHT11 //Tipo de sensor

//Declaración de objetos usados

DHT dht(DTHPIN, DTHTYPE); //Declaración del Objeto DHT
IotViewPantalla Figura;//Declaración del Objeto Figura
SSD1306Wire  display(0x3c, 21, 22);//Declaración del Objeto display

Ticker TickerLedBuiltin;//Declaración de la tarea para refrescar el pin LED_BUILTIN 
Ticker TickerLedTest;//Declaración de la tarea para refrescar el pin LED_TEST 

//Tazas de refresco de las tareas

float tazaRefrescoLedBuiltin =0.1;//Tiempo en segundos
float tazaRefrescoLedTest =0.5;//Tiempo en segundos

//Definición de las tareas de refresco
void refrescarLedBuiltin() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void refrescarLedTest() {
  digitalWrite(LED_TEST, !digitalRead(LED_TEST));
}



void setup() {
  // Inicialización de los pines.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_TEST, OUTPUT);
  
  //Inicialización de la comunicación serial
  Serial.begin(TAZA_SERIAL);
  Serial.println("\nPrograma para monitoreo de humedad y temperatura");
  
  
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

  //Inicialización del sensor
  dht.begin();
   
  //Inicialización del Serial Ploter
  Serial.print(0);
  Serial.print(",");
  Serial.println(0);

  //Inicialización del parapadeo de los leds
  TickerLedBuiltin.attach(tazaRefrescoLedBuiltin, refrescarLedBuiltin);
  TickerLedTest.attach(tazaRefrescoLedTest, refrescarLedTest);
  
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
