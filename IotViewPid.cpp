///////////////////////////////////IotViewPid.cpp////////////////////////////////////////////////
#include "IotViewPid.h"

//Constructor

TIotViewPid::TIotViewPid()
{
 Id=0;
 Kp=1;
 Ki=0;
 Kd=0;
 Ts=1;
 SetPoint=1;
}

//Funciones Get
int TIotViewPid::GetId()
{
  return Id;  
}

float TIotViewPid::GetKp()
{
  return Kp;  
}

float TIotViewPid::GetKi()
{
  return Ki;  
}
    
float TIotViewPid::GetKd()
{
  return Kd;  
}
    
float TIotViewPid::GetTs()
{
  return Ts;  
}
    
float TIotViewPid::GetSetPoint()
{
  return SetPoint;  
}

//Funciones Set

void TIotViewPid::SetId(int i)
{
  Id=i; 
}
   
void TIotViewPid::SetKp(float j)
{
  Kp=j;  
}

void TIotViewPid::SetKi(float j)
{
  Ki=j;
}
   
void TIotViewPid::SetKd(float j)
{
  Kd=j;  
}
    
void TIotViewPid::SetTs(float j)
{
  Ts=j;  
}
    
void TIotViewPid::SetSetPoint(float j)
{
  SetPoint =j;  
}

/*---------------------------------------------------fin------------------------------------------*/
