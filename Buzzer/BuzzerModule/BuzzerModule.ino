int frequency=1000; //Specified in Hz
int buzzPin=12; 
int timeOn=1000; //specified in milliseconds
int timeOff=1000; //specified in millisecods
void setup(){
  
}
void loop ()
{
   tone(buzzPin, frequency);
   delay(timeOn);
   noTone(buzzPin);
   delay(timeOff);
}
