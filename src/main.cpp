#include <Arduino.h>

//Set output pins
const int enjector   = 3;
const int pumpPin    = 4;
// set inputs
const int throtalPot = 0; // Throtle Body throtal pos sence
const int pumpPot    = 2; // idle pump adjustment
const int idlePot    = 1; // Ajust the amount of fule the enjectors give at idle

// config
unsigned int idletoon         = 3;
const int    idleThresh       = 78;
// End config


//unsigned long pumpms;
unsigned long pumplastms;
bool pumpState;

int throtalAmount = 0;
int idleAmount    = 0;
int pumpOn    = 1;
int injectorState = LOW;
unsigned long lastInject = 0;
long injInterval = 50;

void setup()
{
  pinMode(enjector, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enjector Output termianl Started");
}





void loop(){
//Getting Persentage
throtalAmount = analogRead(throtalPot) / 10.24; //ranging 1 to 100
idleAmount = analogRead(idlePot) / 10.24; //ranging 1 to 100
// End Persentages

//For Tuning
injInterval = throtalAmount; // Do throtal curve here
//end Tuning

////////// FulePump
  unsigned long currentMillis = millis();
if (injInterval >= idleThresh){
  digitalWrite(pumpPin, LOW);
  //pumpOffidle();
  //Serial.println("At idle"); delay(300); //DEBGUG
}else{
  digitalWrite(pumpPin, HIGH);
  //Serial.println("Not idle"); delay(300); //DEBGUG
}
///////End Fule pump

////////Enjector Code
if (currentMillis - lastInject >= injInterval){
    lastInject = currentMillis;
    if (injectorState == LOW) {
      injectorState = HIGH;
    } else {
      injectorState = LOW;
    }
    digitalWrite(enjector, injectorState);
  }
/////////End Enjecotr code
}
