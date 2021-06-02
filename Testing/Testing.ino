#include "DHT.h"
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>


#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

String apiWritekey = "8G4KV26ISGKCNDYC";     // replace with your THINGSPEAK WRITEAPI key here
#define ssid  "eduroam bridge"    // your wifi SSID name
#define password "connected"  // wifi pasword
#define server "api.thingspeak.com"
WiFiClient client;


void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  Serial.print("Humid =  ");
  Serial.println(h);
  Serial.print("Temp = ");
  Serial.println(t);
  if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(t);
           tsData +="&field2=";
           tsData += String(h);
           

     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);
     Serial.println("uploaded Sensors DATA to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(15000);   // 15 sec // 
  
}
