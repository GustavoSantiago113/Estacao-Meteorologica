#include <Wire.h>;
#include <SD.h>;
#include <SPI.h>;

File myFile;

// Constants:
const int REED = 3; //Rain "sensor" pin
const int pinCS = 8; //SD card pin

// Variables:
int val = 0;
int old_val = 0;
int REEDCOUNT = 0;
float rain = 0.00;
 
void setup()
{
  
  Serial.begin(9600); //Initialize serial comunication:
  
  pinMode (REED, INPUT_PULLUP); //Initialize switch pin as input
  pinMode(10, OUTPUT); //Needed to SD shield works
  pinMode(pinCS, OUTPUT); // Declare pinCS as output

  if (!SD.begin(pinCS)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");

}
 
void loop() 
{

  val = digitalRead(REED);      // Read Reed Switch status
  String dataString = "";
  
  if ((val == LOW) && (old_val == HIGH)) {   // Verify if status have changed
    delay(100);                   // Delay inserted to deal with any "jump" in Switch
    REEDCOUNT = REEDCOUNT + 1;   // Add 1 to pulse counting
    old_val = val;              // Equalize old value to actual
    rain = REEDCOUNT / 11.00;      //Calculates rain value (Must be calibrated)
    
    //Converting and gathering data to be saved
    dataString += String("Counts: ");
    dataString += String(REEDCOUNT);
    dataString += String(",");
    dataString += String("Rain: ");
    dataString += String(rain);
    dataString += String("mm");

    //Saving data do SD card
    myFile = SD.open("WSKSU.txt", FILE_WRITE);
    myFile.println(dataString);
    myFile.close();

    // Print on Serial Monitor
    Serial.println(dataString);
  }
 
  else {
    old_val = val;              //If the status hasn't changed then do nothing
  }
}
