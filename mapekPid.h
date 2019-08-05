/*
 * Libreria para el manejo del ciclo MAPEK
 * Desarrollado por: César Augusto Álvarez
 * Esp32: Ok
 * Versión: 0.1
 *
 */



#ifndef __MAPEKPID_H__
#define __MAPEKPID_H__

#include <dummy.h>
#include <Arduino.h>
#include "mapek.h"

class TMapeKPid //Mapek para el lazo cerrado de control
{
  private:
    float VSensor;
    int Kn;//Numero de medidadas actuales
    float KJ;//Indice de funcionamiento
    float KJmin;//Indice de funcionamiento minimo
    int KJ_i;//Posición del menor indice de funcionamiento
    int KN_pids;//Numeros de Pids actuales
    float KSetpoint;
    float Ksensor;
    float Kerror;
    float KIerror;
    float KSP;//Sensibilidad de Kp
    float KSI;//Sensibilidad de Ki
    float KSD;//Sensibilidad de Kp
    float KDeltaKp;//Variación de kp
    float KDeltaKi;//Variación de ki
    float KDeltaKd;//Variación de kd
    float Kp;
    float Ki;
    float Kd;
    float TS;
    float gradKj;
    bool onAdaptar;
    float TS_anterior;
    int iter;
    void monitor(void);
    void analyze(void);
    void plan(void);
    void execute(void);
    TMapeKControl *ControlPid;
  public:
    //Constructores
    TMapeKPid(TMapeKControl *Pid);
    void runMapek(void); 
    void SetSetpoint(float);
    float (*ADC)(void);
};


#endif
