/*
 * Libreria para la conexión a la plataforma IotView
 * Desarrollado por: César Augusto Álvarez
 * Esp32: Ok
 * Versión: 0.1
 *
 *
 *El token posee la siguiente esctructura
 *
 *IdSistema : NumeroSensores ; IdSensor1 / TokenSensor1 & IdSensor2 / TokenSensor2 & ......
 */




//Archivo IotView.h
#include "IotViewSistema.h"
//Declaración del objeto

#ifndef __IOTVIEW_H__
#define __IOTVIEW_H__

//Librerias
#include <dummy.h>
#include <WiFi.h>//Libreria para el manejo del WiFi
#include <Wire.h> //Libreria para el manejo del puerto I2C

#include <ArduinoJson.h>
#include "SSD1306Wire.h"//Libreria para el manejo de la pantalla OLED
#include "IotViewEsp32.h"//Libreria con las configuraciones básicas del ESP32
#include "IotViewOled.h"//Libreria con interfaz grafica implementada en la pantalla OLED
#include "urlEncodeDecode.h"//Libreria para codificar la url


class TIotView
{
  private:
    String Host;
    String Token;
    int  httpPort;
    bool status;
    WiFiClient *cliente;
    bool conexionServidor;
    //Datos de conexión al sistema
    //Datos de configuración de la pagina
    int idSistema;
    int nSensores;
    String Respuesta;
    //Funciones privadas
    String Conexion(String, String, String);
  public:
    //Constructores
    TIotView(String host,String token, int port, WiFiClient *clie);
    TIotViewSistema Sistema;
    //Funciones Set
    //Funciones Get conexión
    String extraerJson(String);
    String GetHost(void);
    String GetToken(void);
    int GetHttpPort(void);
    bool GetStatus(void);
    bool GetConectServidor(void);
    //Funciones Get configuración de IotView
     void GetConfiguracion(void);
    String GetRespuesta(void);
    //Funciones varias
    bool Conectar();
    void EnviarDato(int,float);
    float RecibirDato(int);
    void Pull(void);
    String Push(void);
};



#endif
