#include "mapek.h"

//Constructor
TMapeKControl::TMapeKControl(void)
{
  VSensor=0;
  VActuador=0;
  VknolegdeP=0;
  VknolegdeI=0;
  VknolegdeD=0;
  VknolegdeTs=0;
  VknolegdeSetPoint=0;
  VknolegdeError=0;
  VknolegdeVSensorAnterior=0;
  VknolegdeErrorIntegral=0;
  VknolegdeErrorDerivada=0;
  VknolegdeOutMin=0;
  VknolegdeOutMax=3; 
}

void TMapeKControl::analyze(void)
{
  VknolegdeError=VknolegdeSetPoint-VSensor;
  VknolegdeErrorIntegral+=(VknolegdeError*VknolegdeTs);
  VknolegdeErrorDerivada=((VknolegdeError-VknolegdeVSensorAnterior)/VknolegdeTs);
}

void TMapeKControl::plan(void)
{
  VActuador=VknolegdeP*VknolegdeError+VknolegdeI*VknolegdeErrorIntegral+VknolegdeD*VknolegdeErrorDerivada;
}

void TMapeKControl::runMapek(void)
{
    VSensor=this->monitor();
    this->analyze();
    this->plan();
    this->execute(VActuador);
    return;
}

//Para verificar el experimento
void TMapeKControl::setSetpoint(float setpoint)
{
  VknolegdeSetPoint=setpoint;
}

void TMapeKControl::setKpid(float p, float i, float d)
{
 VknolegdeP=p;
 VknolegdeI=i;
 VknolegdeD=d;  
}

void TMapeKControl::setTs(float t)
{
 if(VknolegdeTs!=t)
   {
    this->reset();
    VknolegdeTs=t;  //Segundos
   }
}


void TMapeKControl::setLimites(float minimo, float maximo)
{
 if(minimo>maximo)return;
 VknolegdeOutMin=minimo;
 VknolegdeOutMax=maximo; 
}

float TMapeKControl::getKp(void)
{
 return VknolegdeP;  
}

float TMapeKControl::getKi(void)
{
 return VknolegdeI;  
}

float TMapeKControl::getKd(void)
{
 return VknolegdeD;  
}

float TMapeKControl::getTs(void)
{
 return VknolegdeTs;  
}

float TMapeKControl::getVSensor(void)
{
 return VSensor;  
}

void TMapeKControl::reset(void)
{
  VSensor=0;
  VActuador=0;
  VknolegdeError=0;
  VknolegdeErrorIntegral=0;
  VknolegdeErrorDerivada=0;
}
