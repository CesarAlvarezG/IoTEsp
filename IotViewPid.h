/*
 * Libreria para la conexión a la plataforma IotView
 * Controlador PID
 * Desarrollado por: César Augusto Álvarez
 * Esp32: Ok
 * Versión: 0.1
 *
 */




//Archivo IotViewPid.h

//Declaración del objeto

#ifndef __IOTVIEWPID_H__
#define __IOTVIEWPID_H__

//Librerias
#include <dummy.h>
#include <Arduino.h>


class TIotViewPid
{
  private:
    int Id;
    float Kp;
    float Ki;
    float Kd;
    float Ts;
    float SetPoint;
    //Funciones privadas
  public:
    //Constructores
    TIotViewPid(void);
   
    //Funciones Get conexión
    int GetId(void);
    float GetKp(void);
    float GetKi(void);
    float GetKd(void);
    float GetTs(void);
    float GetSetPoint(void);

    //Funciones Set
    void SetId(int);
    void SetKp(float);
    void SetKi(float);
    void SetKd(float);
    void SetTs(float);
    void SetSetPoint(float);
};


#endif
