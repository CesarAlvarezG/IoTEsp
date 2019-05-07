/*
  Programa para el manejo de la familia ESP para la plataforma IoTView
  Esp32: ok

  Desarrollado por: César Augusto Álvarez Gaspar
  Fecha: 3 de abril de 2019

  Versión: 0.0.16
  Descripción: Programa para el monitoreo de humedad y temperatura, visualizado por medio de una pantalla OLED
               Prueba de paralelismo con los leds LED_TEST y LED_BUILTIN
               Paralelismo de la lectura del sensor y el refresco de la pantalla
               Conexión al WiFi y monitoreo de la conexión
               Conexión a la plataforma IotView y monitoreo de la conexión
               Envio de datos de Humedad y Temperatura a la plataforma IotView
               Recepción de los datos de configuración del sistema en la plataforma IotView
               Extracción de datos importantes del token
               Presentación del nombre del sistema en la pantalla
               Estructura de información en IotView
               Nota: Encontré dificultades para usar Ticker y el Objeto Figura, por lo cual lo dejo en el loop()
*/


#include <dummy.h> //Libreria para identificar los pines del EPS32
#include <Ticker.h>//Libreria para el manejo de las tareas paralelas
#include "IotView.h"//Libreria para la conexión a la plataforma IotView
#include "DHT.h"  //Libreria para el DHT11

//Declaración de los elementos para usar IotView

int status = WL_IDLE_STATUS;
const int httpPort = 80;
char host[]="iotview.herokuapp.com";
char token[]="1:2;1/v9clypYoSq&2/YMyedSLQx0";
/*
 *IdSistema=1 : 
 *NumeroSensores=2 ; 
 *IdSensor1=1 / 
 *TokenSensor1= v9clypYoSq & 
 *IdSensor2=2 / 
 *TokenSensor2= YMyedSLQx0 & 
 */

//Declaración de objetos usados en IotView


SSD1306Wire  display(0x3c, 21, 22);//Declaración del Objeto display
WiFiClient client;

//La pantalla tiene un acople debil con respecto al objeto de uso de IotView
IotViewPantalla Figura;//Declaración del Objeto Figura
IotView IoTViewSistema(host,token,httpPort,&client);//Declaración del Objeto para usar IotView

//Declaración de objetos usados en la aplicación en particular

DHT dht(DTHPIN, DTHTYPE); //Declaración del Objeto DHT
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
 Serial.println("Respuesta de la API: ");
 Serial.println("");
 IoTViewSistema.GetConfiguracion();
 Serial.println(IoTViewSistema.GetRespuesta());
 String Respuesta;
 Respuesta=IoTViewSistema.GetRespuesta();
 int h=Respuesta.indexOf("\n{");
    int k=Respuesta.indexOf("}\n")+1;
    String Datos=Respuesta.substring(h,k);
 Serial.println("");
 Serial.println("");
 Serial.println(Datos);   
 Serial.println("");
 Serial.println("");
 
  Serial.print("Nombre: ");
 Serial.println(IoTViewSistema.GetNombre());
  Figura.SetNombreServidor(IoTViewSistema.GetNombre());
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
