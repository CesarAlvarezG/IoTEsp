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


class IotView
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
    String Nombre;
    String Descripcion;
    String Nvar;
    float Var;
    String NMensaje;
    String Mensaje;
    int nSensores;
    int idSensor1;
    int idSensor2;
    String TokenSensor1;
    String TokenSensor2;
    String Respuesta;
    //Funciones privadas
  public:
    //Constructores
    IotView(String host,String token, int port, WiFiClient *clie);
    //Funciones Set
    //Funciones Get conexión
    String GetHost(void);
    String GetToken(void);
    int GetHttpPort(void);
    bool GetStatus(void);
    bool GetConectServidor(void);
    //Funciones Get configuración de IotView
     void GetConfiguracion(void);
    String GetNombre(void);
    String GetDescripcion(void);
    String GetNvar(void);
    float GetVar(void);
    String GetNMensaje(void);
    String GetMensaje(void);
    String GetRespuesta(void);
    //Funciones varias
    bool Conectar();
    void EnviarDato(int,float);
    float RecibirDato(int);
};

class IotViewSensor
{
  private:
    int id;
    String Nombre;
    String Tipo;
    String Confirmacion;
    String NVar;
    float Var;
    String NMensaje;
    String Mensaje;
  public:
    //Constructores
    IotViewSensor();
    //Funciones Get
    String GetNombre(void);
    String GetTipo(void);
    String GetConfirmacion(void);
    String GetNVar(void);
    float GetVar(void);
    String GetNMensaje(void);
    String GetMensaje(void);
    //Funciones Pull
};


#endif
