#include <Wire.h>

// Constants:
const int REEDR = 2; //Rain "sensor" pin

// Variables:
int valR = 0;
int old_valR = 0;
int REEDCOUNTR = 0;
float rain = 0.00;

void setup()
{
  
  Serial.begin(9600); //Initialize serial comunication:
  
  pinMode (REEDR, INPUT_PULLUP); //Initialize switch pin as input

}
 
void loop() 
{

  superDelay(30000);

  valR = digitalRead(REEDR);      // Read Reed Switch status
  String dataString = "";

  rain = REEDCOUNTR / 11.00;      //Calculates rain value (Must be calibrated)

  //Converting and gathering data to be saved
  dataString += String("Counts: ");
  dataString += String(REEDCOUNTR);
  dataString += String(", ");
  dataString += String("Rain: ");
  dataString += String(rain);
  dataString += String("mm");

  Serial.println(dataString);

}

// Function to make anemomether works while other processes are happening
void superDelay(unsigned long tempoDeEspera) 
{
  unsigned long inicio = millis(); 
  while (millis() - inicio < tempoDeEspera) 
  { 

    // Rain
    valR = digitalRead(REEDR);
    
    if ((valR == LOW) && (old_valR == HIGH)) {
      delay(100);
      REEDCOUNTR = REEDCOUNTR + 1;
      old_valR = valR;
    }
    else {
      old_valR = valR;
    }
    
  }
}
