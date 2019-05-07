///////////////////////////////////IotView.cpp////////////////////////////////////////////////
#include "IotView.h"

//Constructor

TIotView::TIotView(String host,String token, int port, WiFiClient *clie)
{
  Host=host;
  Token=token;
  httpPort=port;
  status=WL_IDLE_STATUS;
  cliente=clie;
  //Extraer datos de configuración del Token
  int h=token.indexOf(":");
  idSistema=token.substring(0,h).toInt();  
  token.remove(0,h+1);
  h=token.indexOf(";");
  nSensores=token.substring(0,h).toInt();
  token.remove(0,h+1);
  Sistema.SetNSensores(nSensores);
}

//Funciones privadas

String TIotView::Conexion(String url,String verboHttp, String cuerpo)
{
 String Solicitud;
 String Respuesta;
  if (cliente->connect(Host.c_str(), httpPort)!=0) {
          Solicitud=verboHttp;
          Solicitud+=" ";
          Solicitud+=url;
          Solicitud+=" HTTP/1.1\r\n";
          Solicitud+="Host: ";
          Solicitud+=Host;
          Solicitud+="\r\n";
          Solicitud+=cuerpo;
          cliente->println(Solicitud);
          cliente->println();
          unsigned long timeout = millis();
          while(cliente->available() == 0)
                {
                 if (millis() - timeout > 5000)
                    {
                      Respuesta+=">>> Client Timeout !\r\n";
                      cliente->stop();
                      return "";
                    }
                }
          while(cliente->available())
               {
                String line=cliente->readStringUntil('\r');
                Respuesta+=line;
               }
  }
 return Respuesta;   
}

String TIotView::extraerJson(String tem)
{
  String temJson="";
  int h=tem.indexOf("\n{");
  int k=tem.indexOf("}\n")+1;
  temJson=Respuesta.substring(h,k);
  return temJson;
}


void TIotView::GetConfiguracion(void)
{
 StaticJsonBuffer<1500> jsonBuffer;
 String Solicitud;
 String c;
 Solicitud="/api/sistemas/";
 Solicitud+=idSistema;
 //Solicitud de los datos al seervidor
 Respuesta=Conexion(Solicitud,"GET","");
    //Extracción de la cadena JSON
    String Datos="";
    Datos=extraerJson(Respuesta);
    Sistema.OfJson(Datos);
  
}

//Funciones Set

//Funciones Get
bool TIotView::GetConectServidor(void)
{
 return conexionServidor;
}

String TIotView::GetHost(void)
{
 return Host;  
}
    
String TIotView::GetToken(void)
{
 return Token;  
}
    
int TIotView::GetHttpPort(void)
{
 return httpPort;  
}

bool TIotView::GetStatus(void)
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

String TIotView::GetRespuesta(void)
{
 return Respuesta; 
}
//Funciones varias

void TIotView::EnviarDato(int puerto, float medida)
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


float TIotView::RecibirDato(int puerto)
{
  float Var;
  return Var;
}

bool TIotView::Conectar(void)
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

//Función para subir datos al sistema
String TIotView::Push(void)
{
 String Solicitud;
 String cuerpo;
 Solicitud="/api/sistemas/";
 Solicitud+=urlencode(Sistema.PushJson());
 //Solicitud+="%7B%22id%22%3A2%2C%22Nombre%22%3A%22ApiIot%22%2C%22Descripcion%22%3A%22Prueba+de+envio+y+recepcion+de+datos+por+la+API%22%2C%22NVar%22%3A%22N+Sensores%22%2C%22Var%22%3A5%2C%22NMensaje%22%3A%22Estado%22%2C%22Mensaje%22%3A%22Lo+Mejor%22%2C%22sensors%22%3A%5B%7B%22id%22%3A4%2C%22Nombre%22%3A%22Decremento%22%2C%22Tipo%22%3A%22Sensor%22%2C%22NVar%22%3A%22Valor%22%2C%22Var%22%3A46%2C%22NMensaje%22%3A%22Estado%22%2C%22Mensaje%22%3A%22El+mejor+Ok%22%7D%2C%7B%22id%22%3A3%2C%22Nombre%22%3A%22Incremento%22%2C%22Tipo%22%3A%22Sensor%22%2C%22NVar%22%3A%22Valor%22%2C%22Var%22%3A210%2C%22NMensaje%22%3A%22Estado%22%2C%22Mensaje%22%3A%22Ok%22%7D%5D%7D";
 //Solicitud de los datos al servidor
 cuerpo="";
 //cuerpo+="Content-Type: application/x-www-form-urlencoded\r\n";
 //cuerpo+="\r\n";
 Respuesta=Conexion(Solicitud,"PUT",cuerpo);
 return Respuesta;
}

void TIotView::Pull(void)
{
  return;
}
/*---------------------------------------------------fin------------------------------------------*/
