/*
 * Libreria para la conexión a la plataforma IotView
 * Sistema
 * Desarrollado por: César Augusto Álvarez
 * Esp32: Ok
 * Versión: 0.1
 */




//Archivo IotView.h

//Declaración del objeto

#ifndef __IOTVIEWSISTEMA_H__
#define __IOTVIEWSISTEMA_H__

//Librerias
#include <dummy.h>
#include "IotViewSensor.h"
#include "IotViewPid.h"
#include <ArduinoJson.h>

class TIotViewSistema
{
  private:
    int Id;
    String Nombre;
    String Tipo;
    String Confirmacion;
    String Descripcion;
    String NVar;
    float Var;
    String NMensaje;
    String Mensaje;
    String Json;
    
    int NSensores;
  public:
    //Constructores
    TIotViewSistema();
    TIotViewSistema(int);
    ~TIotViewSistema();
    //Funciones Get conexión
    TIotViewSensor *Sensores;
    int GetId(void);
    String GetNombre(void);
    String GetDescripcion(void);
    String GetNvar(void);
    float GetVar(void);
    String GetNMensaje(void);
    String GetMensaje(void);
    
    //Funciones Set
    void SetId(int);
    void SetNombre(String);
    void SetDescripcion(String);
    void SetNVar(String);
    void SetVar(float);
    void SetNMensaje(String);
    void SetMensaje(String);
    void SetNSensores(int);

    //Funciones Json
    String ToJson(void);
    void OfJson(String);

    //Funciones de actualizacion
    String PushJson(void);
    void PullJson(String);

};



#endif
