/*
 * Libreria para la conexión a la plataforma IotView
 * Sensor
 * Desarrollado por: César Augusto Álvarez
 * Esp32: Ok
 * Versión: 0.1
 */




//Archivo IotViewSensor.h

//Declaración del objeto

#ifndef __IOTVIEWSENSOR_H__
#define __IOTVIEWSENSOR_H__

//Librerias
#include "IotViewPid.h"
#include <Arduino.h>

class TIotViewSensor
{
  private:
    int Id;
    String Nombre;
    String Tipo;
    String Confirmacion;
    String Nvar;
    float Var;
    String NMensaje;
    String Mensaje;
    TIotViewPid *Pids;
  public:
    //Constructores
    TIotViewSensor();
    
    //Funciones Get conexión
    int GetId(void);
    String GetNombre(void);
    String GetTipo(void);
    String GetConfirmacion(void);
    String GetNvar(void);
    float GetVar(void);
    String GetNMensaje(void);
    String GetMensaje(void);
    
    //Funciones Set
    void SetId(int);
    void SetNombre(String);
    void SetTipo(String);
    void SetConfirmacion(String);
    void SetNVar(String);
    void SetVar(float);
    void SetNMensaje(String);
    void SetMensaje(String);
};

#endif
