

#include "mapekPid.h"

//Constructor
TMapeKPid::TMapeKPid(TMapeKControl *Pid)
{
   Kn=0;//Numero de medidadas actuales
   KJ=0;//Indice de funcionamiento 
   ControlPid=Pid;
   KDeltaKp=0;//Variación de kp
   KDeltaKi=1;//Variación de ki
   KDeltaKd=0;//Variación de kd
   Kp=0;
   Ki=0;
   Kd=0;
   KSP=1;
   KSI=1;
   KSD=0.000001;
   TS=0;
   onAdaptar=false;
}

void TMapeKPid::monitor(void)
{
 VSensor=ControlPid->getVSensor();
 Kp=ControlPid->getKp();
 Ki=ControlPid->getKi();
 Kd=ControlPid->getKd();
 TS=ControlPid->getTs(); 
}


void TMapeKPid::analyze(void)
{
 Kerror=KSetpoint-VSensor;
 //if(TS!=TS_anterior)iter=0;
 if(iter>10)
    {
     onAdaptar=true;
    }else{
         onAdaptar=false;
         }
 TS_anterior=TS;
}

void TMapeKPid::plan(void)
{
 if(onAdaptar)
 {
  KDeltaKp=KSP*(-(KIerror));
  KDeltaKi=KSI*(-(KIerror));
  KDeltaKd=KSD*(-(KIerror));
  iter=0;
  KIerror=0;
 }else{
       KDeltaKp=0;
       KDeltaKi=0;
       KDeltaKd=0;
       KIerror+=(Kerror*Kerror*TS);
       iter++;
       
      }  
}


void TMapeKPid::execute(void)
{
 Kp+=KDeltaKp;
 Ki+=KDeltaKi;
 Kd+=KDeltaKd; 
 ControlPid->setKpid(Kp,Ki,Kd);
}


void TMapeKPid::runMapek(void)
{
    this->monitor();
    this->analyze();
    this->plan();
    this->execute();
    return;
}

//Para verificar el experimento


void TMapeKPid::SetSetpoint(float set)
{
 KSetpoint=set;
}
