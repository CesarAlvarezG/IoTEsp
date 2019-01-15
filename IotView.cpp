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
  DirVar=0;
  cliente=clie;
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
     cliente->println(C);
     cliente->println();
     return conexionServidor;
 }else{
           conexionServidor=false;
          } 
}


/*---------------------------------------------------fin------------------------------------------*/
