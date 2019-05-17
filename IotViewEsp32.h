/*
 * Libreria con la configuración básica del esp32
 * Desarrollado por: César Augusto Álvarez
 * Esp32: Ok
 * Versión: 0.1
*/ 


#ifndef __IOTVIEWESP32_H__
#define __IOTVIEWESP32_H__



//Definiciones de los datos del ESP32

#define LED_BUILTIN 27 
#define LED_TEST 0
#define TAZA_SERIAL 115200  //Velocidad por defecto en el ESP32


#define DTHPIN 26      //Pin al que se conecto el sensor
#define DTHTYPE DHT11 //Tipo de sensor


#define TAZA_REFRESCO_PANTALLA 1000//Taza de refresco de la pantalla


//Sensores creados en la plataforma IotView
#define DirVarTrabajo1 1
#define DirVarTrabajo2 2

#endif
