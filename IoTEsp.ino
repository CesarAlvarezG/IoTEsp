/*
  Programa para el manejo de la familia ESP para la plataforma IoTView
  Esp32: ok

  Desarrollado por: César Augusto Álvarez Gaspar
  Fecha: 15 de enero de 2019

  Versión: 0.0.7
  Descripción: Programa para el monitoreo de humedad y temperatura, visualizado por medio de una pantalla OLED
               Prueba de paralelismo con los leds LED_TEST y LED_BUILTIN
               Paralelismo de la lectura del sensor y el refresco de la pantalla


               Nota: Encontré dificultades para usar Ticker y el Objeto Figura, por lo cual lo dejo en el loop()
*/


#include <dummy.h> //Libreria para identificar los pines del EPS32
#include <Wire.h> //Libreria para el manejo del puerto I2C
#include <Ticker.h>//Libreria para el manejo de las tareas paralelas
#include "DHT.h"  //Libreria para el DHT11
#include "SSD1306Wire.h"//Libreria para el manejo de la pantalla OLED
#include "IotViewOled.h"//Libreria con interfaz grafica implementada en la pantalla OLED

#define LED_BUILTIN 27 
#define LED_TEST 0
#define TAZA_SERIAL 115200  //Velocidad por defecto en el ESP32
#define TAZA_REFRESCO_PANTALLA 100//Taza de refresco de la pantalla


#define DTHPIN 25      //Pin al que se conecto el sensor
#define DTHTYPE DHT11 //Tipo de sensor

//Declaración de objetos usados

DHT dht(DTHPIN, DTHTYPE); //Declaración del Objeto DHT
IotViewPantalla Figura;//Declaración del Objeto Figura
SSD1306Wire  display(0x3c, 21, 22);//Declaración del Objeto display

Ticker TickerSensorDHT;//Declaración de la tarea de leer el sensor

//Taza de refresco de la tarea
float tazaRefrescoSensorDHT =5;//Tiempo en segundos

float h=0;//Humedad
float t=0;//Temperatura
int i=0;//Numero de iteracción

void leerSensorDHT() {
  
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
}

void refrescarPantalla() {
  Figura.Display();  //Función encargada de refrescar la pantalla
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
  Figura.SetApoyoVar1(tazaRefrescoSensorDHT);
  Figura.SetApoyoVar2(0);
  Figura.SetTrabajoVar1(0);
  Figura.SetTrabajoVar2(0); 

  //Inicialización del sensor
  dht.begin();
   
  //Inicialización del Serial Ploter
  Serial.print(0);
  Serial.print(",");
  Serial.println(0);

  //Inicialización de la tarea de refresco
  TickerSensorDHT.attach(tazaRefrescoSensorDHT, leerSensorDHT);
}



void loop() 
{
 Figura.Display();
 delay(TAZA_REFRESCO_PANTALLA);
}
