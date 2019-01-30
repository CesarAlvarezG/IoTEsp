///////////////////////////////////IotView.cpp////////////////////////////////////////////////
#include "IotView.h"

//Constructor

IotView::IotView(String host,String token, int port, WiFiClient *clie)
{
  Host=host;
  Token=token;
  httpPort=port;
  status=WL_IDLE_STATUS;
  Var=0;
  idSistema=1;
  cliente=clie;
  Nombre="Nombre";
  Descripcion="Descripción";
  Nvar="Nombre de variable";
  Var=0;
  NMensaje="Nombre de mensaje";
  Mensaje="Mensaje";
}

void IotView::GetConfiguracion(void)
{
 StaticJsonBuffer<500> jsonBuffer;
 String Solicitud;
 String c;
 //Solicitud de los datos al seervidor
 if (cliente->connect(Host.c_str(), httpPort)!=0)
    {
      
      Solicitud="GET";
      Solicitud+=" /iotsistema/";
      Solicitud+=idSistema;
      Solicitud+=" HTTP/1.1\r\n";
      Respuesta+=Solicitud;
      cliente->print(Solicitud);
      c="Host: ";
      c+=Host;
      Respuesta+=c+"\r\n";
      cliente->println(c);
      cliente->println();
      unsigned long timeout = millis();
      while(cliente->available() == 0)
            {
              if (millis() - timeout > 5000)
                 {
                  Respuesta+=">>> Client Timeout !\r\n";
                  cliente->stop();
                  return;
                 }
            }
      while(cliente->available())
           {
            String line=cliente->readStringUntil('\r');
            Respuesta+=line;
           }
    //Extracción de los datos de configuración 
    int h=Respuesta.indexOf("{")-1;
    int k=Respuesta.indexOf("}")+1;
    String Datos=Respuesta.substring(h,k);
    JsonObject& obj=jsonBuffer.parseObject(Datos);
    if(!obj.success())
    {
        return;
    }
    Nombre=obj["Nombre"].as<char*>();
    Descripcion=obj["Descripcion"].as<char*>();
    Nvar=obj["NVar"].as<char*>();
    Var=obj["Var"].as<int>();
    NMensaje=obj["NMensaje"].as<char*>();
    Mensaje=obj["Mensaje"].as<char*>();
  }
}

//Funciones Set

//Funciones Get
bool IotView::GetConectServidor(void)
{
 return conexionServidor;
}

String IotView::GetHost(void)
{
 return Host;  
}
    
String IotView::GetToken(void)
{
 return Token;  
}
    
int IotView::GetHttpPort(void)
{
 return httpPort;  
}

bool IotView::GetStatus(void)
{
 if(cliente->available())
 {
    status=true; 
  }else{
        status=false;
        }
 return status;  
}

//Funciones Get configuración de IotView
String IotView::GetNombre(void)
{
 return Nombre; 
}

String IotView::GetDescripcion(void)
{
 return Descripcion; 
}

String IotView::GetNvar(void)
{
 return Nvar; 
}

float IotView::GetVar(void)
{
 return Var; 
}

String IotView::GetNMensaje(void)
{
 return NMensaje; 
}

String IotView::GetMensaje(void)
{
 return Mensaje; 
}

String IotView::GetRespuesta(void)
{
 return Respuesta; 
}
//Funciones varias

void IotView::EnviarDato(int puerto, float medida)
{
 String Solicitud;
 String c;
 if (isnan(medida))return;
 if (cliente->connect(Host.c_str(), httpPort)!=0) {
          Solicitud="GET";
          Solicitud+=" /iot/";
          Solicitud+=puerto;
          Solicitud+="/";
          Solicitud+=medida;
          Solicitud+=" HTTP/1.1";
          cliente->println(Solicitud);
          //Serial->println(Solicitud    );
          c="Host: ";
          c+=Host;
          cliente->println(c);
          cliente->println();
          while(cliente->available()>0){
              c=cliente->read();
          }
  }
 return; 
}


float IotView::RecibirDato(int puerto)
{
  return Var;
}

bool IotView::Conectar(void)
{
 String C;
 if(cliente->connect(Host.c_str(), httpPort)!=0)
    {
     conexionServidor=true;
     cliente->println("GET / HTTP/1.1");
     C="Host: ";
     C+=Host;
     Respuesta=C+"\r\n";
     cliente->println(C);
     cliente->println();
     return conexionServidor;
 }else{
           conexionServidor=false;
          } 
}


/*---------------------------------------------------fin------------------------------------------*/
