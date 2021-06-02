#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
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
  
}
