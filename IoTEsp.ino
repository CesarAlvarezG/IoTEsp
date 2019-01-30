/*
  Programa para el manejo de la familia ESP para la plataforma IoTView
  Esp32: ok

  Desarrollado por: César Augusto Álvarez Gaspar
  Fecha: 15 de enero de 2019

  Versión: 0.0.13
  Descripción: Programa para el monitoreo de humedad y temperatura, visualizado por medio de una pantalla OLED
               Prueba de paralelismo con los leds LED_TEST y LED_BUILTIN
               Paralelismo de la lectura del sensor y el refresco de la pantalla
               Conexión al WiFi y monitoreo de la conexión
               Conexión a la plataforma IotView y monitoreo de la conexión
               Envio de datos de Humedad y Temperatura a la plataforma IotView
               Recepción de los datos de configuración del sistema en la plataforma IotView
               Nota: Encontré dificultades para usar Ticker y el Objeto Figura, por lo cual lo dejo en el loop()
*/


#include <dummy.h> //Libreria para identificar los pines del EPS32
#include <Wire.h> //Libreria para el manejo del puerto I2C
#include <Ticker.h>//Libreria para el manejo de las tareas paralelas

//#include <WiFi.h>//Libreria para el manejo del WiFi
#include "DHT.h"  //Libreria para el DHT11
#include "SSD1306Wire.h"//Libreria para el manejo de la pantalla OLED
#include "IotViewOled.h"//Libreria con interfaz grafica implementada en la pantalla OLED
#include "IotView.h"//Libreria para la conexión a la plataforma IotView

#define LED_BUILTIN 27 
#define LED_TEST 0
#define TAZA_SERIAL 115200  //Velocidad por defecto en el ESP32
#define TAZA_REFRESCO_PANTALLA 100//Taza de refresco de la pantalla

//Sensores creados en la plataforma IotView
#define DirVarTrabajo1 1
#define DirVarTrabajo2 2

#define DTHPIN 25      //Pin al que se conecto el sensor
#define DTHTYPE DHT11 //Tipo de sensor



//Declaración de los elementos para usar IotView

int status = WL_IDLE_STATUS;
const int httpPort = 80;
char host[]="iotview.herokuapp.com";
char token[]="1:v9clypYoSq;YMyedSLQx0";

//Declaración de objetos usados

DHT dht(DTHPIN, DTHTYPE); //Declaración del Objeto DHT
IotViewPantalla Figura;//Declaración del Objeto Figura
SSD1306Wire  display(0x3c, 21, 22);//Declaración del Objeto display
WiFiClient client;
IotView IoTViewSistema(host,token,httpPort,&client);//Declaración del Objeto para usar IotView


Ticker TickerSensorDHT;//Declaración de la tarea de leer el sensor
Ticker TickerStatus;//Declaración de la tarea de monitorear la conexión a WiFi y la plataforma IotView

//Declaración de las variables para el uso del WiFi

//char ssid[] = "ssid";
//char password[] = "password";

char ssid[] = "ALVAREZ MORALEZ";
char password[] = "97395883";

//const char* ssid     = "CesarAndroid";
//const char* password = "24fb64ca5d11";


//Taza de refresco de la tarea
float tazaRefrescoSensorDHT =60;//Tiempo en segundos
float tazaRefrescoStatus =1;//Tiempo en segundos

float h=0;//Humedad
float t=0;//Temperatura
int i=0;//Numero de iteracción

void leerSensorDHT() {
  
  //Lectura del sensor
  h=dht.readHumidity();
  t=dht.readTemperature();
  
  //Visualización de las lecturas
  Serial.print(h);
  Serial.print(",");
  Serial.println(t);
  
  //Visualización en la pantalla OLED
  Figura.SetTrabajoVar1(t);
  Figura.SetTrabajoVar2(h);
  Figura.SetApoyoVar2(++i);

  //Envio de las señales a la plataforma IotView
  IoTViewSistema.EnviarDato(DirVarTrabajo1,t);
  IoTViewSistema.EnviarDato(DirVarTrabajo2,h);
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
  Figura.SetTrabajoEtiqueta1("T [°C]");
  Figura.SetTrabajoEtiqueta2("H [%]"); 
  Figura.SetApoyoEtiqueta1("Ts");
  Figura.SetApoyoEtiqueta2("Iteracción");
  Figura.SetApoyoVar1(tazaRefrescoSensorDHT);
  Figura.SetApoyoVar2(0);
  Figura.SetTrabajoVar1(0);
  Figura.SetTrabajoVar2(0); 

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
 IoTViewSistema.Conectar();
 Serial.print(IoTViewSistema.GetRespuesta());
 
 //Mostrar configuración de IotView
 IoTViewSistema.GetConfiguracion();
 Serial.print(IoTViewSistema.GetRespuesta());
 Serial.print("Nombre: ");
 Serial.println(IoTViewSistema.GetNombre());
 Serial.print("Descripcion: ");
 Serial.println(IoTViewSistema.GetDescripcion());
 Serial.print("Nvar: ");
 Serial.println(IoTViewSistema.GetNvar());
 Serial.print("Var: ");
 Serial.println(IoTViewSistema.GetVar());
 Serial.print("NMensaje: ");
 Serial.println(IoTViewSistema.GetNMensaje());
 Serial.print("Mensaje: ");
 Serial.println(IoTViewSistema.GetMensaje());
 
 //Inicialización del sensor
  dht.begin();
   
  //Inicialización del Serial Ploter
  Serial.print(0);
  Serial.print(",");
  Serial.println(0);

  //Inicialización de la tarea de refresco
  TickerSensorDHT.attach(tazaRefrescoSensorDHT, leerSensorDHT);
  TickerStatus.attach(tazaRefrescoStatus, estadoStatus);
}


//-------------------------------loop------------------------------------------


void loop() 
{
 Figura.Display();
 delay(TAZA_REFRESCO_PANTALLA);
}
