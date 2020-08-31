   /*
Programa para medir el nivel de agua en dos tanques y reportarlo via web.

por David Wong el 14oct17

Requiere una unidad compatible con ESP8266 (yo usé una NodeMCU v3 Lolin)
    
    */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <math.h>  //para el redondeo

// ***** Pines para sensor HC-SR07 ****
// Sensor tanque inferior    
    const int echoPinInf = 16; // D0 en NodeMCU
    const int trigPinInf = 5; // D1 en NodeMCU

// Sensor tanque superior   
    const int echoPinSup = 4; // D2 en NodeMCU
    const int trigPinSup = 0; // D3 en NodeMCU

// **** Constantes de tamano tanque agua, superior e inferior (en metros) ****
// Tanque inferior
    const float lengthInfTankM = 3.2;   // Largo tanque inferior
    const float widthInfTankMM = 2;     // Ancho tanque inferior
    const float deepInfTankM = 1.7;     // Profundidad tanque inferior
    const float volTotalInfTankM3 = 8.96; // Restado 0.3 de distancia al sensor tanque inferior, nivel

// Tanque superior
    const float lengthSupTankM = 2.74;  // Largo tanque superior
    const float widthSupTankM = 2;      // Ancho tanque superior 
    const float deepUpTankM = 1.9;      // Profundidad tanque superior
    const float volTotalSupTankM3 = 9.32; // Restado 0.2 de distancia al sensor tanque superior
   
// Para calculos internos
    long duration1;
    float deepInfTankCm;

    long duration2;
    float deepSupTankCm;

    float volumeInfTank;
    float volumeSupTank; 

    float porcInfTank;
    float porcSupTank;

    String infoSensorInf;  // Estado web sensor inferior
    String infoSensorSup; // Estado web sensor superior

// Clave wifi del AP del lugar
const char* ssid = "wifi-ap";
const char* password = "wifipass";

ESP8266WebServer server(80);

void handleRoot() {
//  server.send(200, "text/plain", "hello from esp8266!");
  server.send(200, "text/plain", infoSensorInf + "\n" + infoSensorSup);
//  server.send(200, "text/plain", infoSensorSup);
    
}

void handleNotFound(){
  digitalWrite(13, 1);
  delay(2000);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(13, 0);
}


void setup(void){
  // Configuramos los pines de los sensores HC-SR07 x 2
  pinMode(trigPinInf, OUTPUT);
  pinMode(echoPinInf, INPUT);
  pinMode(trigPinSup, OUTPUT);
  pinMode(echoPinSup, INPUT);
  // no olvidar abrir puerto para depurar
  Serial.begin (9600);     

  // A partir de aca es para la conexion http
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
 //   Serial.print(".");
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
 
      // Dispara sensor HC-SR07 para medir tanque bajo
      digitalWrite(trigPinInf, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPinInf, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPinInf, LOW);
      duration1 = pulseIn(echoPinInf, HIGH);
      deepInfTankCm = duration1*0.034/2;

       // Trigger upper tank
      digitalWrite(trigPinSup, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPinSup, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPinSup, LOW);
      duration2 = pulseIn(echoPinSup, HIGH);
      deepSupTankCm= duration2*0.034/2;  
/*
     if (deepInfTankCm > 0 && deepSupTankCm > 0) {   // Verificar que no haya error, ningún sensor puede ser cero!
        // Make calculations based on volume1 and volume2
          volumeInfTank = lengthInfTankM * widthInfTankMM * (deepInfTankM - (float)deepInfTankCm/100);
       
          porcInfTank = (float)volumeInfTank/(float)volTotalInfTankM3 * 100;   
   
          volumeInfTank = round(volumeInfTank*10);
          volumeInfTank = volumeInfTank/10;
 
          volumeSupTank = lengthSupTankM * widthSupTankM * (deepUpTankM - (float)deepSupTankCm/100);
          volumeSupTank = round(volumeSupTank*10);
          volumeSupTank = volumeSupTank/10;
          porcSupTank = (float)volumeSupTank / volTotalSupTankM3 * 100;

       // Elabora mensaje a mostrar en web
          infoSensorInf = "Volumen Tanque Inferior: " + String(volumeInfTank) + "m3, " + String(porcInfTank) + "%";
          infoSensorSup = "Volumen Tanque Superior: " + String(volumeSupTank) + "m3, " + String(porcSupTank) + "%";
          
     } else {
      // Hubo un error con algun sensor, alguno fue cero.
          infoSensorInf = "ERROR SENSOR: cmInf: " + String(deepInfTankCm) + ", " + String(duration1) + "uS";
          infoSensorSup = "ERROR SENSOR: cmSup: " + String(deepSupTankCm) + ", " + String(duration2) + "uS";
     }
 */     
     // Información para depuración
     Serial.println("cmInf: " + String(deepInfTankCm) + ", " + "cmSup: " + String(deepSupTankCm));
   //  Serial.println(infoSensorSup + " /  " + infoSensorInf);

  server.handleClient();
}
