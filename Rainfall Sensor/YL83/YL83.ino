
const int Rain = A0;


void setup()
{
  pinMode(Rain, INPUT);
  
  Serial.begin(115200);
//configueatoion of microcontroller of pin
}

void loop()
{

//main
float R = analogRead(Rain); 
 Serial.print("Analog value : ");
 Serial.println(R); 
 Serial.println("");
 delay(1000);

 if(R <= 500) 
  {
    Serial.println("Analog value : wet"); 
    delay(500); 
  }

else
  {
    Serial.println("Analog value : dry");
    delay(500); 
  }





}