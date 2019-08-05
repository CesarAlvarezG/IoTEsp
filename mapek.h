/*
 * Libreria para el manejo del ciclo MAPEK
 * Desarrollado por: César Augusto Álvarez
 * Esp32: Ok
 * Versión: 0.1
 *
 */



#ifndef __MAPEK_H__
#define __MAPEK_H__

#include <dummy.h>
#include <Arduino.h>


class TMapeKControl //Mapek para el lazo cerrado de control
{
  private:
    float VSensor;
    float VActuador;
    float VknolegdeSetPoint;
    float VknolegdeError;
    float VknolegdeErrorIntegral;
    float VknolegdeErrorDerivada;
    float VknolegdeVSensorAnterior;
    float VknolegdeP;
    float VknolegdeI;
    float VknolegdeD;
    float VknolegdeTs;
    float VknolegdeOutMin;
    float VknolegdeOutMax;
    void reset(void);
    void analyze(void);
    void plan(void);
    
  public:
    //Constructores
    TMapeKControl();
    void runMapek(void); 
    float (*monitor)(void);
    void (*execute)(float);
    //Para verificar el experimento
    void setSetpoint(float);
    void setKpid(float, float, float);
    void setTs(float);
    void setLimites(float, float);
    float getKp(void);
    float getKi(void);
    float getKd(void);
    float getTs(void);
    float getVSensor(void);
};


#endif
