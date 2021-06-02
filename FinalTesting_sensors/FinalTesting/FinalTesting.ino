
#include "DHT.h"  

#define DHTPIN 4    //to read digital from dht
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

const int analog_ldr = A0; //to read analog from ldr
int analog = A0; //to read analog values from YL-83 and soil mositure

int frequency=1000; //Specified in Hz
int buzzPin=12; 
int buzztime=1000; //specified in milliseconds

const int MOTOR = 2;


void setup() {
Serial.begin(115200);
pinMode(2, OUTPUT);     //ldr
pinMode(analog, INPUT); //rainfall
pinMode(MOTOR,OUTPUT);  //water pump
dht.begin();

}

void loop() {
  //LDR sensor
digitalWrite(2,HIGH);
int LDR = analogRead(analog_ldr);
Serial.print("LDR  = "  );
Serial.println(LDR);

if(LDR<=700)
{
  digitalWrite(2,LOW);
  Serial.println("Light");
  delay(1000);
  }
else
{
  digitalWrite(2, HIGH);
  Serial.println("No Light");
   delay(1000);
}

//Rainfall Sensor
 float Rain = analogRead(analog); 
 Serial.print("Analog value for rainfall sensor: ");
 Serial.println(Rain); 

 delay(500); 

 if(Rain <= 500) 
  {
    Serial.println("Wet"); 
    delay(1000); 
  }

else
  {
    Serial.println("Dry");
    delay(1000); 
  }
//Soil Moisture Sensor
  int moist = analogRead(analog);
  moist = map(moist,550,0,0,100);
  Serial.print("Mositure : ");
  Serial.print(moist);
  Serial.println("%");
  delay(1000);

//Temprature and Humidity Sensor
  float humid = dht.readHumidity();
  float temp = dht.readTemperature();
  
  Serial.print("Humidity =  ");
  Serial.println(humid);
  Serial.print("Temprature = ");
  Serial.println(temp);
  Serial.println("");
  delay(1000);

//buzzer

if (Rain<=500 || LDR<=700 || humid<=30 || temp<=30 || moist>=50) {
   tone(buzzPin, frequency);
   delay(buzztime);
}
else{
   noTone(buzzPin);
   delay(buzztime);
 }

 //water pump

if (Rain<=500 || LDR<=700 || humid<=30 || temp<=30 || moist>=50){
 digitalWrite(MOTOR,HIGH);// IT INDICATES MOTOR WIll OFF For 2 sec
 delay(2000);
}

else{
 digitalWrite(MOTOR,LOW);// IT INDICATES MOTOR WILL ON FOR 8 sec
 delay(8000);
}
 
 delay(5000);

}
