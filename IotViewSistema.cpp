///////////////////////////////////IotView.cpp////////////////////////////////////////////////
#include "IotViewSistema.h"

//Constructor

TIotViewSistema::TIotViewSistema()
{
    Id=0;
    Nombre ="";
    Descripcion="";
    NVar="";
    Var=0;
    NMensaje="";
    Mensaje="";
    NSensores=1;
    Sensores=NULL;
    Sensores= new TIotViewSensor[NSensores];
}

//Destructor

TIotViewSistema::~TIotViewSistema()
{
    Id=0;
    Nombre ="";
    Descripcion="";
    NVar="";
    Var=0;
    NMensaje="";
    Mensaje="";
    delete [] Sensores;
}


//Funciones Get conexión

int TIotViewSistema::GetId(void)
{
  return Id;  
}

String TIotViewSistema::GetNombre(void)
{
  return Nombre;  
}
    
String TIotViewSistema::GetDescripcion(void)
{
  return Descripcion;  
}
    
String TIotViewSistema::GetNvar(void)
{
  return NVar;  
}
    
float TIotViewSistema::GetVar(void)
{
  return Var;  
}
    
String TIotViewSistema::GetNMensaje(void)
{
  return NMensaje;  
}
    
String TIotViewSistema::GetMensaje(void)
{
  return Mensaje; 
}

//Funciones Set
void TIotViewSistema::SetId(int i)
{
 Id=i;  
}
    
void TIotViewSistema::SetNombre(String s)
{
  Nombre=s;  
}
    
void TIotViewSistema::SetDescripcion(String s)
{
  Descripcion=s;  
}
    
void TIotViewSistema::SetNVar(String s)
{
  NVar=s;  
}
    
void TIotViewSistema::SetVar(float f)
{
    Var=f;  
}
    
void TIotViewSistema::SetNMensaje(String s)
{
  NMensaje=s;  
}
    
void TIotViewSistema::SetMensaje(String s)
{
  Mensaje=s; 
}

void TIotViewSistema::SetNSensores(int n)
{
  delete [] Sensores;
  NSensores=n;
  Sensores= new TIotViewSensor[NSensores];
}


//Funciones Json
String TIotViewSistema::ToJson(void)
{
  Json="";
  const size_t capacity = JSON_ARRAY_SIZE(2) + 2*JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(8);
  DynamicJsonBuffer jsonBuffer(capacity);
  
  JsonObject& root = jsonBuffer.createObject();
  root["id"] = Id;
  root["Nombre"] = Nombre;
  root["Descripcion"] = Descripcion;
  root["NVar"] = NVar;
  root["Var"] = Var;
  root["NMensaje"] = NMensaje;
  root["Mensaje"] = Mensaje;
  JsonArray& sensors = root.createNestedArray("sensors");
  for(int i=0;i<NSensores;i++)
  {
    JsonObject& sensors_i = sensors.createNestedObject();
    sensors_i["id"] = this->Sensores[i].GetId();
    sensors_i["Nombre"] = this->Sensores[i].GetNombre();
    sensors_i["Tipo"] = this->Sensores[i].GetTipo();
    sensors_i["NVar"] = this->Sensores[i].GetNvar();
    sensors_i["Var"] = this->Sensores[i].GetVar();
    sensors_i["NMensaje"] = this->Sensores[i].GetNMensaje();
    sensors_i["Mensaje"] = this->Sensores[i].GetMensaje();
  }
  root.printTo(Json);
  return Json;
}
    
void TIotViewSistema::OfJson(String J)
{
 Json=J;
 const char* tem;
 const size_t capacity = JSON_ARRAY_SIZE(2) + 2*JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(8) + 360;
 DynamicJsonBuffer jsonBuffer(capacity);
 JsonObject& root = jsonBuffer.parseObject(Json);
 
 if(!root.success())
    {
        return;
    }
    //Veriricación de la exixtencia de los datos
    const char* error=root["error"];
    if(error != nullptr)
      {
        return;
      }
      
 Id = root["id"];
 tem= root["Nombre"];
 Nombre=tem;
 tem= root["Descripcion"];
 Descripcion=tem;
 tem = root["NVar"];
 NVar=tem;
 Var = root["Var"];
 tem = root["NMensaje"];
 NMensaje=tem;
 tem= root["Mensaje"];
 Mensaje=tem;
 //Sensores
 for(int i=0;i<NSensores;i++)
    {
      JsonObject& sensors_i = root["sensors"][i];
      this->Sensores[i].SetId(sensors_i["id"]);
      this->Sensores[i].SetNombre(sensors_i["Nombre"]);
      this->Sensores[i].SetTipo(sensors_i["Tipo"]);
      this->Sensores[i].SetConfirmacion( sensors_i["NVar"]);
      this->Sensores[i].SetNVar(sensors_i["NVar"]);
      this->Sensores[i].SetVar(sensors_i["Var"]);
      this->Sensores[i].SetNMensaje(sensors_i["NMensaje"]);
      this->Sensores[i].SetMensaje( sensors_i["Mensaje"]);
    }
}

String TIotViewSistema::PushJson(void)
{
  String tem;
  const size_t capacity = JSON_ARRAY_SIZE(2) + 2*JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(8);
  DynamicJsonBuffer jsonBuffer(capacity);
  
  JsonObject& root = jsonBuffer.createObject();
  root["id"] = Id;
  root["Var"] = Var;
  root["Mensaje"] = Mensaje;
  JsonArray& sensors = root.createNestedArray("sensors");
  for(int i=0;i<NSensores;i++)
  {
    JsonObject& sensors_i = sensors.createNestedObject();
    sensors_i["id"] = this->Sensores[i].GetId();
    sensors_i["Var"] = this->Sensores[i].GetVar();
    sensors_i["Mensaje"] = this->Sensores[i].GetMensaje();
  }
  root.printTo(tem);
  return tem;
}
void TIotViewSistema::PullJson(String j)
{
 const char* tem;
 const size_t capacity = JSON_ARRAY_SIZE(2) + 2*JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(8) + 360;
 DynamicJsonBuffer jsonBuffer(capacity);
 JsonObject& root = jsonBuffer.parseObject(j);
 
 if(!root.success())
    {
        return;
    }
    //Veriricación de la exixtencia de los datos
    const char* error=root["error"];
    if(error != nullptr)
      {
        return;
      }
      
 Var = root["Var"];
 tem= root["Mensaje"];
 Mensaje=tem;
 //Sensores
 for(int i=0;i<NSensores;i++)
    {
      JsonObject& sensors_i = root["sensors"][i];
      this->Sensores[i].SetVar(sensors_i["Var"]);
      this->Sensores[i].SetMensaje( sensors_i["Mensaje"]);
    }
}


/*---------------------------------------------------fin------------------------------------------*/
