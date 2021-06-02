#include "DHT.h"
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>


#define DHTPIN 12                                                                                                                                                                    
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int Rain = A0;

int sensor_pin = A0; 
int moist ;
int tomatoe, spinach, flower;

String apiWritekey = "8G4KV26ISGKCNDYC";     // replace with your THINGSPEAK WRITEAPI key here
#define ssid  "EVO-Charji-7DD8"    // your wifi SSID name
#define password "TUScX5Js"  // wifi pasword
#define server "api.thingspeak.com"
WiFiClient client;

void setup() {
  pinMode(Rain, INPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
  
  Serial.println(F("Testing......."));

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

  digitalWrite(2,HIGH);
int LDR = analogRead(A0);
Serial.print("LDR  = "  );
Serial.println(LDR);

if(LDR<=700)
{
  digitalWrite(2,LOW);
  Serial.println(" Light");
 
  }
else
{
  digitalWrite(2, HIGH);
  Serial.println("No Light");
 
}

float R = analogRead(Rain); 
 Serial.print("Analog value for Rain module : ");
 Serial.println(R); 


 if(R <= 500) 
  {
    Serial.println("RainModule : wet"); 
   
  }

else
  {
    Serial.println("RinModule : dry");
   
  }

  moist= analogRead(sensor_pin);
  moist = map(moist,550,0,0,100);
  Serial.print("Mositure : ");
  Serial.print(moist);
  
  Serial.println("");
  Serial.println("");
  Serial.println("");



   delay(2000);

if (t>10 && t<30 && h>65 && h<75 && moist<70 && moist>80){
  
  tomatoe = 90
   Serial.println(tomatoe);
}
else //condition2 {
   tomatoe = 50;
  
}

if (t>10 && t<30 && h>65 && h<75 && moist<70 && moist>80){
  
  spinach = 90;

}
else {
   spinach = "Plant(spinach) will be not be healthy under these conditions"; //change to int
  
}
if (t>10 && t<30 && h>65 && h<75 && moist<70 && moist>80){
  
  flower = "Plant(flower) will be % healthy under these conditions";//change to int
  

}
else {
   flower = "Plant(flower) will be not be healthy under these conditions";//change to int
  
  
}

   

   if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(t);
           tsData +="&field2=";
           tsData += String(h);
           tsData +="&field3=";
           tsData += String(R);
           tsData +="&field4=";
           tsData += String(moist);
           tsData +="&field5=";
           tsData += String(LDR);
           tsData +="&field6=";
           tsData += String(tomatoe);
           tsData +="&field7=";
           tsData += String(spinach);
            tsData +="&field8=";
           tsData += String(flower);
           tsData += "\r\n\r\n";

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
