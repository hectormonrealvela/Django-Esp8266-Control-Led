#include <ESP8266WiFi.h> //Incluimos la librería para del WiFi
#include "ESP8266HTTPClient.h"
#include "ArduinoJson.h"
#include <ESP8266mDNS.h>  
 
//WIFI, PASSWORD
const char* ssid = "INVETT";
const char* password = "isisLab16$$";
int state; 
int ledpin=2; // Pin que usaremos para encender el led 
WiFiServer server(80); // Declaramos un servidor que estará en el puerto 80

 
void setup() {
  Serial.begin(115200); //Inicio el puerto serie 
  pinMode(ledpin,OUTPUT);
 
  // Conecto con la red WiFi 
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

 
  while (WiFi.status() != WL_CONNECTED) { // meintras que no estemos conectando imprimimos ".", una vez que nos conectamos imprimimos " Wifi conectado"
    delay(500);
    Serial.print(".");
  }

  if (!MDNS.begin("Arduino2")) {             // Asignamos la DNS " Arduino2" al Esp8266 para que la aplicación web pueda comunicarse con él a pesar de que cambie la ip.
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");

  
  Serial.println("");
  Serial.println("WiFi conectado");
 
  // Inicializo el servidor 
  server.begin();   
  Serial.println("Servidor iniciado");
 
  // Muestro la IP local asignada. URL del servidor 
  Serial.print("Usa esta URL para conectar al servidor: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
  HTTPClient http; // A continuación vamos a ver el estado actual en el que se encuentra el Led al inicializar el Arduino
  http.begin("http://192.168.64.5:8000/2/read/"); // invocamos el método http y pasamos la Url a la que queremos conectarnos y hacemos la solicitud GET
  int httpCode = http.GET();
  if (httpCode > 0) {// ponemos esta condicion ya que si el valor es menor que 0, significa que hemos tenido un error del cliente al hacer la solicitud GET.
 
   String payload = http.getString(); // obtenemos el resultado de la respuesta, y lo almacenamos en payload.
   Serial.println(payload);
    
   const size_t bufferSize = JSON_OBJECT_SIZE(1) + 20;   // Definimos cuanta memoria queremos guardar para los datos JSON
   DynamicJsonBuffer jsonBuffer(bufferSize); // Declaramos DynamicJsonBuffer para asignar una parte de la memoria para almacenar los datos Json
   JsonObject& root = jsonBuffer.parseObject(payload);// Llamamos al método parseOBject con el objecto jsonBuffer, pasando la cadena payload como argumento. Esto nos devolvera un dato que lo pasaremos a la variable root 
    
    
   int set_state = root["estado"];    // Declaramos la variable set_state con el valor obtenido de la web ( TRue or False)
    
   Serial.println(set_state);      // Lo imprimimos.

    
   if (set_state == 1) {
     
     digitalWrite(ledpin, LOW);
     Serial.println("Led ON");
     }
   else {
     digitalWrite(ledpin, HIGH);
     Serial.println("Led OFF");
     }
   }

 if (!MDNS.begin("Arduino2")) {             // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
 }
 Serial.println("mDNS responder started");

}
 
void loop() {

  // Compruebo si hay un cliente disponible (una petición) 
  
  WiFiClient client = server.available();  // Creamos un objeto cliente
   if (client == true) {
    client.println("HTTP/1.1 200 OK");
   }
   else {
    return; 
   }
   
  String url = "/2/read/";
  Serial.print("Requesting URL:");
  Serial.println(url);

  Serial.println();
  HTTPClient http;
  http.begin("http://192.168.64.5:8000/2/read/"); // invocamos el método http y pasamos la Url a la que queremos conectarnos y hacemos la solicitud GET
  int httpCode = http.GET();

  if (httpCode > 0) {// ponemos esta condicion ya que si el valor es menor que 0, significa que hemos tenido un error del cliente al hacer la solicitud GET.
 
   String payload = http.getString(); // obtenemos el resultado de la respuesta, y lo almacenamos en payload.
   Serial.println(payload);
    
   const size_t bufferSize = JSON_OBJECT_SIZE(1) + 20;   // Definimos cuanta memoria queremos guardar para los datos JSON
   DynamicJsonBuffer jsonBuffer(bufferSize); // Declaramos DynamicJsonBuffer para asignar una parte de la memoria para almacenar los datos Json
   JsonObject& root = jsonBuffer.parseObject(payload);// Llamamos al método parseOBject con el objecto jsonBuffer, pasando la cadena payload como argumento. Esto nos devolvera un dato que lo pasaremos a la variable root 
    
    
   int set_state = root["estado"];    // Declaramos la variable set_state con el valor obtenido de la web ( TRue or False)
    
   Serial.println(set_state);      // Lo imprimimos.

    
   if (set_state == 1) {
     
     digitalWrite(ledpin, LOW);
     Serial.println("Led ON");
     }
   else {
     digitalWrite(ledpin, HIGH);
     Serial.println("Led OFF");
     } 
   }

   
}
