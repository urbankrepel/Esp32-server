#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>

#define led 2
#include "gesla.h"

bool stanjeLucke = false; // false:OFF, true:ON

WebServer server(80);

IPAddress local_IP(192, 168, 1, 212);

IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led,OUTPUT);

  if (!WiFi.config(local_IP,gateway,subnet)){
     Serial.println("STA Failed to configure"); 
  }

  WiFi.begin(ssid,password,1);

  while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.println("Connecting to WiFi..");  
  }

  Serial.print("Connected to ");
  Serial.print(ssid);
  Serial.print("\n with this ip: ");
  Serial.print(WiFi.localIP());

  server.on("/light/on", [](){
    server.send(200, "text/plain", "OK");
    turnLight(true);
  });
  
  server.on("/light/off", [](){
    server.send(200, "text/plain", "OK");
    turnLight(false);
  });

  server.on("/light/info", [](){
    server.send(200, "text/plain", stanjeLucke == true ? "ON":"OFF");
  });

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void turnLight(bool vklopi){
  stanjeLucke = vklopi;

    if (vklopi){
      digitalWrite(led, HIGH);  
    }else{
      digitalWrite(led, LOW);  
    }
}
