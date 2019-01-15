/*
 * Libreria para la conexión a la plataforma IotView
 * Desarrollado por: César Augusto Álvarez
 * Esp32: Ok
 * Versión: 0.1
 *
 */




//Archivo IotView.h

//Declaración del objeto

#ifndef __IOTVIEW_H__
#define __IOTVIEW_H__

//Librerias
#include <dummy.h>
#include <WiFi.h>//Libreria para el manejo del WiFi

class IotView
{
  private:
    String Host;
    String Token;
    int  httpPort;
    int status;
    WiFiClient *cliente;
    int DirVar;
    float Var;
    bool conexionServidor;
  public:
    //Constructores
    IotView(String host,String token, int port, WiFiClient *clie);
    //Funciones Set
    //Funciones Get
    String GetHost(void);
    String GetToken(void);
    int GetHttpPort(void);
    int GetStatus(void);
    bool GetConectServidor(void);
    //Funciones varias
    bool Conectar();
    void EnviarDato(int,float);
    float RecibirDato(int);
};

#endif
