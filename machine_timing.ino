#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//Componnent 1
#define relayPin D1
#define relayPin2 D2
bool isTurnC1On = true;
bool isC1Reverse = false;

//Componnent 2
#define relayPin3 D3
#define relayPin4 D4
bool isTurnC2On = true;
bool isC2Reverse = false;

//Componnent 3
#define relayPin5 D5
#define relayPin6 D6



ESP8266WebServer server(80);

const char* apSSID = "Marchan_Machine1"; // Access Point SSID
const char* apPassword = "config123";  // Access Point Password

void handleRoot();
void handleOffC1();
void handleOnC1();
void handleRevC1();
void handleOffC2();
void handleOnC2();
void handleRevC2();

void setup() {
  Serial.begin(115200);
  pinMode(relayPin,OUTPUT);
  pinMode(relayPin2,OUTPUT);
  pinMode(relayPin3,OUTPUT);
  pinMode(relayPin4,OUTPUT);
  pinMode(relayPin5,OUTPUT);
  pinMode(relayPin6,OUTPUT);

  digitalWrite(relayPin,  LOW);
  digitalWrite(relayPin2,  LOW);
  digitalWrite(relayPin3,  LOW);
  digitalWrite(relayPin4,  LOW);
  digitalWrite(relayPin5,  LOW);
  digitalWrite(relayPin6,  LOW);
  
  // put your setup code here, to run once:
  WiFi.softAP(apSSID, apPassword);
  Serial.println("Access Point started.");
  Serial.print("SSID: ");
  Serial.println(apSSID);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/1/off", handleOffC1);
  server.on("/1/on", handleOnC1);
  server.on("/1/reverse", handleRevC1);

  
  server.on("/2/off", handleOffC2);
  server.on("/2/on", handleOnC2);
  server.on("/2/reverse", handleRevC2);
  
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(isTurnC1On){
    if(isC1Reverse){
      turnComponentReverse(relayPin,relayPin2);
    }else{
      turnComponent(relayPin,relayPin2);
    }
  }else{
    turnOffComponent(relayPin,relayPin2);
  }

  if(isTurnC2On){
    if(isC2Reverse){
      turnComponentReverse(relayPin3,relayPin4);
    }else{
      turnComponent(relayPin3,relayPin4);
    }
  }else{
    turnOffComponent(relayPin3,relayPin4);
  }
  
  turnComponent(relayPin5,relayPin6);
  
  server.handleClient();
}

void handleRoot(){
  String response = "{\"Healthy\": " + String(true) + "}";
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", response);
}

void turnComponent(int pin, int pin2){
  digitalWrite(pin, LOW);
  digitalWrite(pin2,  HIGH);
}

void turnComponentReverse(int pin, int pin2){
  digitalWrite(pin2, LOW);
  digitalWrite(pin,  HIGH);
}

void turnOffComponent(int pin, int pin2){
  digitalWrite(pin, LOW);
  digitalWrite(pin2,  LOW);
}

void handleOffC1(){
    isTurnC1On = false;
    isC1Reverse = false;
    String response = "{\"Component 1 Off\": true}";
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", response);
}

void handleOnC1(){
    isTurnC1On = true;
    isC1Reverse = false;
    String response = "{\"Component 1 Off\": true}";
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", response);
}

void handleRevC1(){
    isTurnC1On = true;
    isC1Reverse = true;
    String response = "{\"Component 1 Reverse\": true}";
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", response);
}

void handleOffC2(){
    isTurnC2On = false;
    isC2Reverse = false;
    String response = "{\"Component 1 Off\": true}";
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", response);
}

void handleOnC2(){
    isTurnC2On = true;
    isC2Reverse = false;
    String response = "{\"Component 1 Off\": true}";
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", response);
}

void handleRevC2(){
    isTurnC2On = true;
    isC2Reverse = true;
    String response = "{\"Component 1 Reverse\": true}";
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", response);
}
