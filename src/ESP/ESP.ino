#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "login.h"
#include "main.h"
MDNSResponder mdns;

 
ESP8266WebServer server(80);
//const char* ssid     = "A";      //wifi name
//const char* password = "Babaman12";  //wifi 

//const char* ssid     = "Tesla IoT";      //wifi name
//const char* password = "fsL6HgjN";  //wifi password


const char* ssid     = "Tjarlei";      //wifi name
const char* password = "Chaplinn!";  //wifi password

//const char* ssid     = "Martaton";      //wifi name
//const char* password = "Nella2018";  //wifi password
//FireData firebaseData;

void handleRoot() 
{                   
  server.send(200, "text/html", LOGIN_page);
}

void handleLogin() 
{    
  String username = "test";
  String password = "123";

  if( ! server.hasArg("username") || ! server.hasArg("password") 
      || server.arg("username") == NULL || server.arg("password") == NULL) { 
    server.send(400, "text/plain", "400: Invalid Request");        
    return;
  }
  if(server.arg("username") == username && server.arg("password") == password) { 
    server.send(200, "text/html", CONTROLLER_page);
  } else {                                                                          
    server.send(401, "text/plain", "401: Unauthorized");
  }
}

void handleControls()
{
 if(server.hasArg("direction"))
 {  
   if(server.arg("direction") == "forward")
   {
     Serial.println("forward");
     Serial.write(1);
   }

   if(server.arg("direction") == "man")
   {
     Serial.println("man");
     Serial.write(5);
   }

   if(server.arg("direction") == "back")
   {
      Serial.println("back");
      Serial.write(2);
   }

   if(server.arg("direction") == "right")
   {
       Serial.println("right");
       Serial.write(3);
   }

   if(server.arg("direction") == "left")
   {
      Serial.println("left");
      Serial.write(4);
   }
   if(server.arg("direction") == "stop_trans")
   {
    Serial.println("stop");
    Serial.write(9);
   }
 }
 
}

void setup(){
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi aangesloten");  
  Serial.println("IP addres: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) 
    Serial.println("MDNS responder gestart");
  
  server.on("/", HTTP_GET, handleRoot);  
  server.on("/login",HTTP_POST, handleLogin);
  server.on("/controller",HTTP_POST, handleControls);
  server.begin();
  Serial.println("HTTP server gestart");
}
 
void loop() 
{
  //runs the client
  server.handleClient();
}
