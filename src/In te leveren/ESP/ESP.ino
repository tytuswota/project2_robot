/*
   Project 2 - RescueBots - ESP

   Namen: Don Luyendijk   - 0970101
          Tymek Pisko     - 0986216
          Gillbert Resida - 0990026
          Charlie de Raaf - 0987084

   Klas:  TI1E - Groep 4
*/

/*------Initialisatie------*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "login.h"
#include "main.h"
 
ESP8266WebServer server(80);
//====================
//the networks

//const char* ssid     = "Tesla IoT";      //wifi name
//const char* password = "fsL6HgjN";  //wifi password

const char* ssid     = "Tjarlei";      //wifi name
const char* password = "Chaplinn!";  //wifi password


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
    server.send(400, "text/plain", "400: Invalid Request");        
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
   Serial.write(server.arg("direction"));
 }
}

//here the handlers are setup up and the network connection
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
