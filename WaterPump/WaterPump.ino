#include<ESP8266WiFi.h>
#include<SoftwareSerial.h>
#include<FirebaseArduino.h> //for firebase integration
#include<ArduinoJson.h>
#include<ESP8266HTTPClient.h>

#define FIREBASE_HOST "fir-iot-2960c-default-rtdb.firebaseio.com"//Adding host here....
#define FIREBASE_AUTH "U0Eu2ixpEVXji23brOzsZX949ajsJOuXWVJTP7Rh" //Add secret key from firebase here....

// now for Wi-Fi Setup
#define WIFI_SSID "PTCL-BB"  // WIFI SSID HERE
#define WIFI_PASSWORD "03345178042"

bool motor; //for switiching the motor
unsigned long previousMillies=0;
const long interval=1000;
// we added above lines to add a time limit after which data will be read from the sensor
//We dont want the sensor to read the data every second  as values of sensors is  not changed every sec

const int analog_ldr = A0; //to read analog from ldr
int analog = A0; //to read analog values from YL-83 and soil mositure

const int MOTOR = 2;

void setup() {
  // put your setup code here, to run once:
pinMode(2, OUTPUT);     //ldr
pinMode(analog, INPUT); //rainfall
pinMode(MOTOR,OUTPUT);  //water pump
Serial.begin(115200);
delay(500);
WiFi.begin(WIFI_SSID,WIFI_PASSWORD); //initializing the wifi credentials
Serial.println("connecting");


while(WiFi.status()!= WL_CONNECTED)
{
  Serial.println(".");
  delay(500);
}
Serial.println();
Serial.println("connected");
Serial.println(WiFi.localIP());

Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
dht.begin();
delay(1000);
}

void readData(){
  Firebase.setFloat("Data/Light:",LDR);
  Firebase.setFloat("Data/Water Sensor:",Rain);
}

void loop() {
  // put your main code here, to run repeatedly:
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
   //water pump

motor=Firebase.getBool("MotorState/switch");//This is the path we specified to our firebase in realtime database
 if(motor==true){
  if (Rain<=500 || LDR<=700 || humid<=30 || temp<=30 || moist>=50){
 digitalWrite(MOTOR,HIGH);// IT INDICATES MOTOR WIll OFF For 2 sec
 delay(2000);
}
 else{
 digitalWrite(MOTOR,LOW);// IT INDICATES MOTOR WILL ON FOR 8 sec
 delay(8000);
}

// now adding time limit before every read of DHT11
unsigned long currentMillis=millis();
if(currentMillis-previousMillis>=interval){
  readData();
  previousMillis=currentMillis;
  
  
}
 }


 
 delay(5000);
}
