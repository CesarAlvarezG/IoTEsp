///////////////////////////////////IotView.cpp////////////////////////////////////////////////
#include "IotViewSensor.h"

//Constructor

TIotViewSensor::TIotViewSensor()
{
    Id=0;
    Nombre ="";
    Tipo ="";
    Confirmacion="";
    Nvar="";
    Var=0;
    NMensaje="";
    Mensaje="";
    Pids=NULL;
}

//Funciones Get conexión

int TIotViewSensor::GetId(void)
{
  return Id;  
}

String TIotViewSensor::GetNombre(void)
{
  return Nombre;  
}
    
String TIotViewSensor::GetTipo(void)
{
  return Tipo;  
}
    
String TIotViewSensor::GetConfirmacion(void)
{
  return Confirmacion;  
}
    
String TIotViewSensor::GetNvar(void)
{
  return Nvar;  
}
    
float TIotViewSensor::GetVar(void)
{
  return Var;  
}
    
String TIotViewSensor::GetNMensaje(void)
{
  return NMensaje;  
}
    
String TIotViewSensor::GetMensaje(void)
{
  return Mensaje; 
}

//Funciones Set
void TIotViewSensor::SetId(int i)
{
 Id=i;  
}
    
void TIotViewSensor::SetNombre(String s)
{
  Nombre=s;  
}
    
void TIotViewSensor::SetTipo(String s)
{
  Tipo=s;  
}
    
void TIotViewSensor::SetConfirmacion(String s)
{
  Confirmacion=s;  
}

void TIotViewSensor::SetNVar(String s)
{
  Nvar=s;  
}
    
void TIotViewSensor::SetVar(float f)
{
    Var=f;  
}
    
void TIotViewSensor::SetNMensaje(String s)
{
  NMensaje=s;  
}
    
void TIotViewSensor::SetMensaje(String s)
{
  Mensaje=s; 
}

/*---------------------------------------------------fin------------------------------------------*/
