#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "login.h"
#include "main.h"
 
ESP8266WebServer server(80);
//====================
//the networks
const char* ssid     = "A";      //wifi name
const char* password = "Babaman12";  //wifi 

//const char* ssid     = "Tesla IoT";      //wifi name
//const char* password = "fsL6HgjN";  //wifi password

//const char* ssid     = "Tjarlei";      //wifi name
//const char* password = "Chaplinn!";  //wifi password

//const char* ssid     = "Martaton";      //wifi name
//const char* password = "Nella2018";  //wifi password
//FireData firebaseData;

void handleRoot() 
{   
  String login = LOGIN_page;
  server.send(200, "text/html", login);
}

//the function that handels the login page
void handleLogin() 
{
  //login credentials
  String username = "test";
  String password = "123";

  if( ! server.hasArg("username") || ! server.hasArg("password") 
      || server.arg("username") == NULL || server.arg("password") == NULL) { 
    //server.send(400, "text/plain", "400: Invalid Request");        
    return;
  }
  if(server.arg("username") == username && server.arg("password") == password) { 
    server.send(200, "text/html", CONTROLLER_page);
  } else {                                                                          
   server.send(401, "text/plain", "401: Unauthorized");
  }
}

//the function that sends to the arduino nano via serial
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

//here the handlers are setup up, the port and the network connection
void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/login",HTTP_POST, handleLogin);
  server.on("/controller",HTTP_POST, handleControls);
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() 
{
  //runs the client
  server.handleClient();
}
