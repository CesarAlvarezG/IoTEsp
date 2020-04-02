/*
  Programa para el manejo de la familia ESP para la plataforma IoTView
  Esp32: ok

  Desarrollado por: César Augusto Álvarez Gaspar
  Fecha: 2 de abril de 2020

  Versión: 0.0.17
  Descripción: 
               Programa de prueba con una función rampa hasta 100
               Programa para el monitoreo de humedad y temperatura, visualizado por medio de una pantalla OLED
               Prueba de paralelismo con los leds LED_TEST y LED_BUILTIN
               Paralelismo de la lectura del sensor y el refresco de la pantalla
               Conexión al WiFi y monitoreo de la conexión
               Conexión a la plataforma IotView y monitoreo de la conexión
               Envio de datos de Humedad y Temperatura a la plataforma IotView
               Recepción de los datos de configuración del sistema en la plataforma IotView
               Extracción de datos importantes del token
               Presentación del nombre del sistema en la pantalla
               Estructura de información en IotView
               Envio de datos por medio de API REST
               Nota: Encontré dificultades para usar Ticker y el Objeto Figura, por lo cual lo dejo en el loop()
*/


#include <dummy.h> //Libreria para identificar los pines del EPS32
#include <Ticker.h>//Libreria para el manejo de las tareas paralelas
#include "IotView.h"//Libreria para la conexión a la plataforma IotView
#include "IotViewEsp32.h"//Libreria para configurar el Esp32
#include "SSD1306Wire.h"
#include "IotViewOled.h"
#include "DHT.h"  //Libreria para el DHT11

//Declaración de los elementos para usar IotView

int status = WL_IDLE_STATUS;
const int httpPort = 80;
char host[]="iotview.herokuapp.com";
char token[]="RphPq81BeT";
int idSistema=1;

//Declaración de objetos usados en IotView
SSD1306Wire  display(0x3c, 21, 22);//Declaración del Objeto display
WiFiClient client;
char ssid[] = "ssid";
char password[] = "password";


//La pantalla tiene un acople debil con respecto al objeto de uso de IotView
IotViewPantalla Figura;//Declaración del Objeto Figura
TIotView IoTViewSistema(host,idSistema,token,httpPort,&client);//Declaración del Objeto para usar IotView

//Declaración de objetos usados en la aplicación en particular

Ticker TickerStatus;//Declaración de la tarea de monitorear la conexión a WiFi y la plataforma IotView
Ticker TickerSensor;//Declaración de la tarea de leer el sensor
//Taza de refresco de la tarea
float tazaRefrescoSensor =30;//Tiempo en segundos
float tazaRefrescoStatus =1;//Tiempo en segundos

int iter=0;//Numero de iteracción
float var=0;//Valor del sensor

void leerSensor() {
  var++;
  if(var>100)var=0;//Creación de Rampa hasta 100  
  //Visualización de las lecturas
  Serial.println(var);
  IoTViewSistema.Sistema.Sensores[0].SetVar(var);
  //Visualización en la pantalla OLED
  Figura.SetTrabajoVar1(IoTViewSistema.Sistema.Sensores[0].GetVar());
  Figura.SetApoyoVar2(++iter);
}


void estadoStatus() {
  if(WiFi.status() == WL_CONNECTED)
  {
    Figura.WiFiOn();
    }else{
          Figura.WiFiOff();
         }
  if(IoTViewSistema.GetStatus()==true)
     {
      Figura.ServidorOn();
      }else{
            Figura.ServidorOff();
        }       
}

void setup() {
  // Inicialización de los pines.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_TEST, OUTPUT);
  //Inicialización de la comunicación serial
  Serial.begin(TAZA_SERIAL);
  Serial.println("\nPrograma para monitoreo de humedad y temperatura");
  //Inicialización de la pantalla OLED
  Figura.SetDisplay(&display);
  Figura.Maqueta();
  Figura.Display();
  
  //Inicialización del WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
       {
        delay(500);
        Serial.print(".");
       }      
 Serial.println("");
 Serial.println("WiFi connectado");
 Serial.println("Dirección IP: ");
 Serial.println(WiFi.localIP());
 
 //Inicialización de la comunicación a IotView
 Serial.print("connecting to ");
 Serial.println(host);
 IoTViewSistema.GetConfiguracion();
 Figura.SetTrabajoEtiqueta1(IoTViewSistema.Sistema.Sensores[0].GetNvar());
 Figura.SetTrabajoEtiqueta2(IoTViewSistema.Sistema.Sensores[1].GetNvar()); 
 Figura.SetApoyoEtiqueta1("Ts");
 Figura.SetApoyoEtiqueta2("Iteracción");
 Figura.SetApoyoVar1(tazaRefrescoSensor);
 //Inicialización de la tarea de refresco
 TickerStatus.attach(tazaRefrescoStatus, estadoStatus);
 TickerSensor.attach(tazaRefrescoSensor, leerSensor);
}


//-------------------------------loop------------------------------------------


void loop() 
{
 Figura.Display();
 //Envio de las señales a la plataforma IotView
 IoTViewSistema.Push();
 delay(TAZA_REFRESCO_PANTALLA);
}
