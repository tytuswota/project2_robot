#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
#include <FirebaseJson.h>
#include <jsmn.h>



#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#import "index.h"
#import "main.h"
MDNSResponder mdns;

//#define FIREBASE_HOST "testforesp-25b98.firebaseio.com";
//#define FIREBASE_AUTH "59g3REBCx30dp73gE5DdcxZr6q8E3ouJGjZuM1Xo";
 
ESP8266WebServer server(80);
String landingPage = MAIN_page;
const char* ssid     = "Tesla IoT";      //wifi name
const char* password = "fsL6HgjN";  //wifi password
//FireData firebaseData;
FirebaseData firebaseData;

void setup() {
 
  pinMode(16, OUTPUT);  //led pin 16
  Serial.begin(115200);
  delay(100);
  
  Serial.println();
  Serial.println();
  Serial.print("Verbinding maken met ");
  Serial.println(ssid);
  
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

  Firebase.begin("testforesp-25b98.firebaseio.com", "59g3REBCx30dp73gE5DdcxZr6q8E3ouJGjZuM1Xo");

  Serial.println("the fire base data");
  /*server.on("/", [](){
    server.send(200, "text/html", landingPage);
  });*/
  
  server.on("/", HTTP_GET, handleRoot);  
  
  server.on("/login", HTTP_POST, handleLogin);
  
  server.on("/socket1On", [](){
    server.send(200, "text/html", landingPage);
    // Turn off LED
    digitalWrite(16, HIGH);
    delay(1000);
  });

  server.on("/coolBlink",coolBlinkHandel);
  
  server.on("/socket1Off", [](){
    server.send(200, "text/html", landingPage);
    //Turn on LED
    digitalWrite(16, LOW);
    delay(1000); 
  });

  server.begin();
  Serial.println("HTTP server gestart");
}
 
void loop() {
  server.handleClient();
}

void handleRoot() {                   
  server.send(200, "text/html", "<form action=\"/login\" method=\"POST\"><input type=\"text\" name=\"username\" placeholder=\"Username\"></br><input type=\"password\" name=\"password\" placeholder=\"Password\"></br><input type=\"submit\" value=\"Login\"></form>");
}

void coolBlinkHandel()
{

  server.send(200, "text/html", landingPage);
        
  for(int i; i < 100; i++)
  {
    digitalWrite(16, HIGH);
    delay(100);
    digitalWrite(16, LOW);
  }
}

void handleLogin() {    
  String username = "";
  String password = "";               
  if(Firebase.getString(firebaseData,"username"))
  {
    username = firebaseData.stringData();
  }
  if(Firebase.getString(firebaseData,"password"))
  {
      Serial.println(firebaseData.stringData());   
      password = firebaseData.stringData();
  }   
  if( ! server.hasArg("username") || ! server.hasArg("password") 
      || server.arg("username") == NULL || server.arg("password") == NULL) { 
    server.send(400, "text/plain", "400: Invalid Request");        
    return;
  }
  if(server.arg("username") == username && server.arg("password") == password) { 
    server.send(200, "text/html", landingPage);
  } else {                                                                          
    server.send(401, "text/plain", "401: Unauthorized");
  }
}
