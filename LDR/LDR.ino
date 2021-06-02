

void setup() {

Serial.begin(115200);

pinMode(2, OUTPUT);


}

void loop() {
digitalWrite(2,HIGH);
int LDR = analogRead(A0);
Serial.print("LDR  = "  );
Serial.println(LDR);

if(LDR<=700)
{
  digitalWrite(2,LOW);
  Serial.println(" Light");
  delay(5000);
  }
else
{
  digitalWrite(2, HIGH);
  Serial.println("No Light");
   delay(5000);
}
}
