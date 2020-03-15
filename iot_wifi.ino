#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>

//--------------Your Data----------------//
String apiKey = "705UWCHVDS1EUCIV"; // <<<<< YOUR API KEY
const char* ssid = "i point"; // <<<<<<<< Your Wi-Fi SSID 
const char* password = "ynpe1234"; // <<<<<<<< Your Wi-Fi Pasword
//--------------------------------------//
const char* server = "api.thingspeak.com";
int data1, data2, data3, data4, data5, ok;
WiFiClient client;


 
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  while (!Serial) continue;
   WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
 

 
void loop() {
 StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    {return;
    }
    
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  //Serial.print("Data 1 ");
  //Serial.print("");
  int data1=root["data1"];
  //Serial.println(data1);
  //Serial.print("   Data 2 ");
  int data2=root["data2"];
  //Serial.println(data2);
  int data3 =root["data3"] ;
  //Serial.println(data3) ;
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");

if (client.connect(server, 80))
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(data1);
    postStr += "&field2=";
    postStr += String(data2);
    postStr += "&field3=";
    postStr += String(data3);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.println(postStr);
  }
  client.stop();
  Serial.println("Waiting...15s");
  delay(15000);

 
}
