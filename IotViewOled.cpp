
#include"IotViewOled.h"

//----------------------------Constructor----------------------------

IotViewPantalla::IotViewPantalla(void)
{
 FWifi=false;
 Servidor=false;
 ApoyoVar1=0;
 ApoyoVar2=0;
 TrabajoVar1=0;
 TrabajoVar2=0;
}

//----------------------------Funciones Set----------------------------

void IotViewPantalla::SetTrabajoEtiqueta1(String tem)
{
  TrabajoEtiqueta1=tem;
}
    
void IotViewPantalla::SetTrabajoEtiqueta2(String tem)
{
 TrabajoEtiqueta2=tem;
}
    
void IotViewPantalla::SetApoyoEtiqueta1(String tem)
{
  ApoyoEtiqueta1=tem;
}
    
void IotViewPantalla::SetApoyoEtiqueta2(String tem)
{
  ApoyoEtiqueta2=tem;
}

void IotViewPantalla::WiFiOn(void)
{
 FWifi=true; 
}

void IotViewPantalla::WiFiOff(void)
{
  FWifi=false;
}

void IotViewPantalla::ServidorOn(void)
{
  Servidor=true;  
}
    
void IotViewPantalla::ServidorOff(void)
{
  Servidor=false;  
}
    
void IotViewPantalla::SetApoyoVar1(float T)
{
  ApoyoVar1=T;
}

void IotViewPantalla::SetApoyoVar2(float T)
{
  ApoyoVar2=T;
}

void IotViewPantalla::SetTrabajoVar1(float V)
{
  TrabajoVar1=V;
}

void IotViewPantalla::SetTrabajoVar2(float V)
{
  TrabajoVar2=V;
}

//----------------------------Funciones Get----------------------------

bool IotViewPantalla::GetWiFi(void)
{
  return FWifi;
}

bool IotViewPantalla::GetServidor(void)
{
  return Servidor;  
}
    
float IotViewPantalla::GetTrabajoVar1(void)
{
  return TrabajoVar1;  
}

float IotViewPantalla::GetTrabajoVar2(void)
{
  return TrabajoVar2;  
}
    
float IotViewPantalla::GetApoyoVar1(void)
{
 return ApoyoVar1; 
}

float IotViewPantalla::GetApoyoVar2(void)
{
 return ApoyoVar2; 
}

void IotViewPantalla::SetDisplay(SSD1306Wire *disp)
{
  displayOled=disp;
  displayOled->init();
  displayOled->flipScreenVertically();
}

//-------------------Funciones para graficar cada panel-------------------

void IotViewPantalla::Estado(void)
{
  displayOled->setTextAlignment(TEXT_ALIGN_LEFT);
  displayOled->setFont(ArialMT_Plain_10);
  displayOled->drawString(XOrigenEstado,YOrigenEstado+1,"WiFi:");
  if(FWifi)
     {
       displayOled->drawCircle(XAnchoEstado/2-TamanoIndicador/2, YAltoEstado/2, TamanoIndicador/2-1);
      }else{
            displayOled->drawRect(XAnchoEstado/2-TamanoIndicador,YOrigenEstado,TamanoIndicador,TamanoIndicador); 
        }
  displayOled->setTextAlignment(TEXT_ALIGN_LEFT);
  displayOled->setFont(ArialMT_Plain_10);
  displayOled->drawString(XAnchoEstado/2+1,YOrigenEstado+1,"Servidor:");
  if(Servidor)
     {
       displayOled->drawCircle(XAnchoEstado-TamanoIndicador/2, YAltoEstado/2, TamanoIndicador/2-1);
       
      }else{
            displayOled->drawRect(XAnchoEstado-TamanoIndicador,YOrigenEstado,TamanoIndicador,TamanoIndicador); 
        }
}

void IotViewPantalla::Apoyo(void)
{
  String tem;
  displayOled->drawRect(XOrigenApoyo, YOrigenApoyo, XAnchoApoyo-1, YAltoApoyo-1);
  displayOled->setTextAlignment(TEXT_ALIGN_LEFT);
  displayOled->drawString(XOrigenApoyo+1,YOrigenApoyo+1,ApoyoEtiqueta1+":");
  displayOled->setTextAlignment(TEXT_ALIGN_CENTER);
  tem=ApoyoVar1;
  displayOled->drawString(XOrigenApoyo+XAnchoApoyo/2,YOrigenApoyo+11,tem);
  displayOled->setTextAlignment(TEXT_ALIGN_LEFT);
  displayOled->drawString(XOrigenApoyo+1,YOrigenApoyo+21,ApoyoEtiqueta2+":");
  displayOled->setTextAlignment(TEXT_ALIGN_CENTER);
  tem=ApoyoVar2;
  displayOled->drawString(XOrigenApoyo+XAnchoApoyo/2,YOrigenApoyo+31,tem);
}

void IotViewPantalla::Trabajo(void)
{
  String tem;
  displayOled->drawRect(XOrigenTrabajo, YOrigenTrabajo, XAnchoTrabajo-1, YAltoTrabajo-1);
  displayOled->setFont(ArialMT_Plain_10);
  displayOled->setTextAlignment(TEXT_ALIGN_LEFT);
  displayOled->drawString(XOrigenTrabajo+1,YOrigenTrabajo+1,TrabajoEtiqueta1+":");
  displayOled->setTextAlignment(TEXT_ALIGN_CENTER);
  tem=TrabajoVar1;
  displayOled->drawString(XOrigenTrabajo+XAnchoTrabajo/2,YOrigenTrabajo+11,tem);
  displayOled->setTextAlignment(TEXT_ALIGN_LEFT);
  displayOled->drawString(XOrigenTrabajo+1,YOrigenTrabajo+21,TrabajoEtiqueta2+":");
  displayOled->setTextAlignment(TEXT_ALIGN_CENTER);
  tem=TrabajoVar2;
  displayOled->drawString(XOrigenTrabajo+XAnchoTrabajo/2,YOrigenTrabajo+31,tem);   
}


//----------------------------Funciones varias----------------------------

void IotViewPantalla::Maqueta(void)
{
  //Panel de estado
  displayOled->setFont(ArialMT_Plain_10);
  displayOled->setTextAlignment(TEXT_ALIGN_CENTER);
  displayOled->drawString((XOrigenEstado+XAnchoEstado)/2,YOrigenEstado+1,"Panel estado");
  displayOled->drawRect(XOrigenEstado, YOrigenEstado, XAnchoEstado-1, YAltoEstado-1);
  
  //Panel de notificación
  displayOled->setFont(ArialMT_Plain_10);
  displayOled->setTextAlignment(TEXT_ALIGN_LEFT);
  displayOled->drawStringMaxWidth(XOrigenApoyo,YOrigenApoyo,XAnchoApoyo,"Panel de apoyo");
  displayOled->drawRect(XOrigenApoyo, YOrigenApoyo, XAnchoApoyo-1, YAltoApoyo-1);
  
  //Area de trabajo
  displayOled->setFont(ArialMT_Plain_10);
  displayOled->setTextAlignment(TEXT_ALIGN_CENTER);
  displayOled->drawString(XOrigenTrabajo+(XAnchoTrabajo)/2,YOrigenTrabajo+1,"Área de trabajo");
  displayOled->drawRect(XOrigenTrabajo, YOrigenTrabajo, XAnchoTrabajo-1, YAltoTrabajo-1);  
} 

void IotViewPantalla::Display(void)
{
  displayOled->clear();
  Estado();
  Apoyo();
  Trabajo();
  displayOled->display();
}

void IotViewPantalla::Clear(void)
{
  displayOled->clear();
}
