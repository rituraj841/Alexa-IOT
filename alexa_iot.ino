int device1 = 5;
int device2 = 4;
int device3 = 0;
int device4 = 2;
int device5 = 14;
int device6 = 12;
int device7 = 13;
int device8 = 15;

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h> // get it from https://github.com/Links2004/arduinoWebSockets/releases 
#include <ArduinoJson.h> // get it from https://arduinojson.org/ or install via Arduino library manager
#include <StreamString.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

#define MyApiKey "ADD YOUR SINRIC API KEYS" // TODO: Change to your sinric API Key. Your API Key is displayed on sinric.com dashboard
#define MySSID "SSID NAME" // TODO: Change to your Wifi network SSID
#define MyWifiPassword "SSID PASSPHRASE" // TODO: Change to your Wifi network password

#define HEARTBEAT_INTERVAL 300000 // 5 Minutes

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

void setPowerStateOnServer(String deviceId, String value);
void setTargetTemperatureOnServer(String deviceId, String value, String scale);

void turnOn(String deviceId) {
// Device ID of device 1
 if (deviceId == "") 
 { 
 Serial.print("Turn on Device ID ==>One: ");
 Serial.println(deviceId);
 digitalWrite(device1, HIGH);
 }
 // Device ID of device 1

 // Device ID of device 2
 else if (deviceId == "") 
 { 
 Serial.print("Turn on Device ID==>Two: ");
 Serial.println(deviceId);
 digitalWrite(device2, HIGH);
 }
 // Device ID of device 2

 // Device ID of device 3
 else if (deviceId == "") 
 { 
 Serial.print("Turn on Device ID==>Three: ");
 Serial.println(deviceId);
 digitalWrite(device3, HIGH);
 }
 // Device ID of device 3

 // Device ID of device 4
 else if (deviceId == "") 
 { 
 Serial.print("Turn on Device ID==>Four: ");
 Serial.println(deviceId);
 digitalWrite(device4, HIGH);
 }
 // Device ID of device 4

  // Device ID of device 5
 else if (deviceId == "") 
 { 
 Serial.print("Turn on Device ID==>Five: ");
 Serial.println(deviceId);
 digitalWrite(device5, HIGH);
 }
 // Device ID of device 5

  // Device ID of device 6
 else if (deviceId == "") 
 { 
 Serial.print("Turn on Device ID==>Six: ");
 Serial.println(deviceId);
 digitalWrite(device6, HIGH);
 }
 // Device ID of device 6

  // Device ID of device 7
 else if (deviceId == "") 
 { 
 Serial.print("Turn on Device ID==>Seven: ");
 Serial.println(deviceId);
 digitalWrite(device7, HIGH);
 }
 // Device ID of device 7

  // Device ID of device 8
 else if (deviceId == "") 
 { 
 Serial.print("Turn on Device ID==>Eight: ");
 Serial.println(deviceId);
 digitalWrite(device8, HIGH);
 }
 // Device ID of device 8
 else 
 {
 Serial.print("Turn on for unknown device id: ");
 Serial.println(deviceId); 
 }
}

void turnOff(String deviceId) {
// Device ID of device 1
 if (deviceId == "") 
 { 
 Serial.print("Turn off Device ID ==>One: ");
 Serial.println(deviceId);
 digitalWrite(device1, LOW);
 }
 // Device ID of device 1

 // Device ID of device 2
 else if (deviceId == "") 
 { 
 Serial.print("Turn off Device ID==>Two: ");
 Serial.println(deviceId);
 digitalWrite(device2, LOW);
 }
 // Device ID of device 2

 // Device ID of device 3
 else if (deviceId == "") 
 { 
 Serial.print("Turn off Device ID==>Three: ");
 Serial.println(deviceId);
 digitalWrite(device3, LOW);
 }
 // Device ID of device 3

 // Device ID of device 4
 else if (deviceId == "") 
 { 
 Serial.print("Turn off Device ID==>Four: ");
 Serial.println(deviceId);
 digitalWrite(device4, LOW);
 }
 // Device ID of device 4

  // Device ID of device 5
 else if (deviceId == "") 
 { 
 Serial.print("Turn off Device ID==>Five: ");
 Serial.println(deviceId);
 digitalWrite(device5, LOW);
 }
 // Device ID of device 5

  // Device ID of device 6
 else if (deviceId == "") 
 { 
 Serial.print("Turn off Device ID==>Six: ");
 Serial.println(deviceId);
 digitalWrite(device6, LOW);
 }
 // Device ID of device 6

  // Device ID of device 7
 else if (deviceId == "") 
 { 
 Serial.print("Turn off Device ID==>Seven: ");
 Serial.println(deviceId);
 digitalWrite(device7, LOW);
 }
 // Device ID of device 7

  // Device ID of device 8
 else if (deviceId == "") 
 { 
 Serial.print("Turn off Device ID==>Eight: ");
 Serial.println(deviceId);
 digitalWrite(device8, LOW);
 }
 // Device ID of device 8
 else 
 {
 Serial.print("Turn off for unknown device id==>Unknown: ");
 Serial.println(deviceId); 
 }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
 switch(type) {
 case WStype_DISCONNECTED:
 isConnected = false; 
 Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
 break;
 case WStype_CONNECTED: {
 isConnected = true;
 Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
 Serial.printf("Waiting for commands from sinric.com ...\n"); 
 }
 break;
 case WStype_TEXT: {
 Serial.printf("[WSc] get text: %s\n", payload);
 // Example payloads

// For Switch or Light device types
 // {"deviceId": xxxx, "action": "setPowerState", value: "ON"} // https://developer.amazon.com/docs/device-apis/alexa-powercontroller.html

// For Light device type
 // Look at the light example in github
 
 DynamicJsonBuffer jsonBuffer;
 JsonObject& json = jsonBuffer.parseObject((char*)payload); 
 String deviceId = json ["deviceId"]; 
 String action = json ["action"];
 
 if(action == "setPowerState") { // Switch or Light
 String value = json ["value"];
 if(value == "ON") {
 turnOn(deviceId);
 } else {
 turnOff(deviceId);
 }
 }
 else if (action == "SetTargetTemperature") {
 String deviceId = json ["deviceId"]; 
 String action = json ["action"];
 String value = json ["value"];
 }
 else if (action == "test") {
 Serial.println("[WSc] received test command from sinric.com");
 }
 }
 break;
 case WStype_BIN:
 Serial.printf("[WSc] get binary length: %u\n", length);
 break;
 }
}

void setup() 
{
 pinMode (device1, OUTPUT);
 pinMode (device2, OUTPUT);
 pinMode (device3, OUTPUT);
 pinMode (device4, OUTPUT);
 pinMode (device5, OUTPUT);
 pinMode (device6, OUTPUT);
 pinMode (device7, OUTPUT);
 pinMode (device8, OUTPUT);




Serial.begin(115200);
 
 WiFiMulti.addAP(MySSID, MyWifiPassword);
 Serial.println();
 Serial.print("Connecting to Wifi: ");
 Serial.println(MySSID);

// Waiting for Wifi connect
 while(WiFiMulti.run() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 if(WiFiMulti.run() == WL_CONNECTED) {
 Serial.println("");
 Serial.print("WiFi connected. ");
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 }

// server address, port and URL
 webSocket.begin("iot.sinric.com", 80, "/");

// event handler
 webSocket.onEvent(webSocketEvent);
 webSocket.setAuthorization("apikey", MyApiKey);
 
 // try again every 5000ms if connection has failed
 webSocket.setReconnectInterval(5000); // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets
}

void loop() {
 
 webSocket.loop();
 
 if(isConnected) {
 uint64_t now = millis();
 
 // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night. Thanks @MacSass
 if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
 heartbeatTimestamp = now;
 webSocket.sendTXT("H"); 
 }
 } 
}

// If you are going to use a push button to on/off the switch manually, use this function to update the status on the server
// so it will reflect on Alexa app.
// eg: setPowerStateOnServer("deviceid", "ON")
void setPowerStateOnServer(String deviceId, String value) {
 DynamicJsonBuffer jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
 root["deviceId"] = deviceId;
 root["action"] = "setPowerState";
 root["value"] = value;
 StreamString databuf;
 root.printTo(databuf);
 
 webSocket.sendTXT(databuf);
}

//eg: setPowerStateOnServer("deviceid", "CELSIUS", "25.0")
void setTargetTemperatureOnServer(String deviceId, String value, String scale) {
 DynamicJsonBuffer jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
 root["action"] = "SetTargetTemperature";
 root["deviceId"] = deviceId;
 
 JsonObject& valueObj = root.createNestedObject("value");
 JsonObject& targetSetpoint = valueObj.createNestedObject("targetSetpoint");
 targetSetpoint["value"] = value;
 targetSetpoint["scale"] = scale;
 
 StreamString databuf;
 root.printTo(databuf);
 
 webSocket.sendTXT(databuf);
}
