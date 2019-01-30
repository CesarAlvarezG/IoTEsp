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
#include <ArduinoJson.h>


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

#endif
