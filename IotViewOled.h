/*
 * Libreria con interfaz grafica de la pantalla OLED
 * Desarrollado por: César Augusto Álvarez
 * Esp32: Ok
 * Versión: 0.1
 * ____________________
 * |  Panel de estado  |
 * |___________________|
 * |       |           |
 * | Panel |    Área   |
 * |  de   |     de    |
 * | apoyo |  Trabajo  |
 * |       |           |
 * |_______|___________|
 * 
 * Panel de estado:
 *        Indicador de estado WiFi 
 *        Indicador de estado Servidor
 *        
 * Panel de apoyo
 *        Variable de apoyo
 *        Variable de apoyo
 *        
 * Área de trabajo       
 *        Variable de trabajo
 *        Variable de trabajo
 */




//Archivo IotViewOled.h

//Declaración del objeto

#ifndef __IOTVIEWOLED_H__
#define __IOTVIEWOLED_H__


//Librerias
#include <dummy.h>
#include <Wire.h>
#include "SSD1306Wire.h"

//Definiciones de los tamaños de los paneles

#define XOrigenEstado 0
#define XAnchoEstado 128
#define YOrigenEstado 0
#define YAltoEstado 17
#define XOrigenApoyo 0
#define XAnchoApoyo 49
#define YOrigenApoyo 17
#define YAltoApoyo 48
#define XOrigenTrabajo 49
#define XAnchoTrabajo 80
#define YOrigenTrabajo 17
#define YAltoTrabajo 48
#define TamanoIndicador 16


//Definición de la clase

class IotViewPantalla
{
  private:
    bool FWifi;//Bandera de conexión a WiFi
    bool Servidor;//Bandera de conexión al Servidor
    //Nombre del servidor
    String NombreServidor;
    //Variables de apoyo
    float ApoyoVar1;
    float ApoyoVar2;
    //Variables de trabajo
    float TrabajoVar1;
    float TrabajoVar2;
    //Etiquetas a las variables
    String ApoyoEtiqueta1;
    String ApoyoEtiqueta2;
    String TrabajoEtiqueta1;
    String TrabajoEtiqueta2;
    
    //Para uso de la pantalla
    SSD1306Wire *displayOled;
    
    //Funciones para graficar cada panel
    void Estado(void);
    void Apoyo(void);
    void Trabajo(void);
 public:
    //Constructor
    IotViewPantalla(void);
    
    //Funciones Set
    void WiFiOn(void);
    void WiFiOff(void);
    void ServidorOn(void);
    void ServidorOff(void);
    void SetNombreServidor(String);
    void SetApoyoVar1(float);
    void SetApoyoVar2(float);
    void SetTrabajoVar1(float);
    void SetTrabajoVar2(float);
    void SetTrabajoEtiqueta1(String);
    void SetTrabajoEtiqueta2(String);
    void SetApoyoEtiqueta1(String);
    void SetApoyoEtiqueta2(String);
     void SetDisplay(SSD1306Wire *disp);
    
    //Funciones Get
    bool GetWiFi(void);
    bool GetServidor(void);
    float GetApoyoVar1(void);
    float GetApoyoVar2(void);
    float GetTrabajoVar1(void);
    float GetTrabajoVar2(void);

    //Funciones varias
    void Maqueta(void);//Despliega la maqueta para verificar el estado de la pantalla
    void Display(void);//Refresca la pantalla
    void Clear(void);//Borra la pantalla
       
};

#endif
