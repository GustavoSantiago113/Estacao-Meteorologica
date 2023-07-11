// Author: Gustavo Nocera Santiago

// Including Libraries
#include <AHT10.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <RTClib.h>

// Anemomether variables
const int REED = 3;
int val = 0;
int old_val = 0;
int REEDCOUNT = 0;
const float pi = 3.14159265;
float radius = 0.065;
float windspeed = 0;

// Temp and Humi Class
AHT10Class AHT10;
float temp;
float umi;

// SD Card Variables
File myFile;
const int pinCS = 10;

// Luminosity variables
#define LDR A0
int light;
int energy;

// Clock class
RTC_DS3231 rtc;

// Pluviomether variables
const int REEDR = 2;
int valR = 0;
int old_valR = 0;
int REEDCOUNTR = 0;
float rain = 0.00;

void setup(){
  
  Serial.begin(9600);
  
  // Pluviomether
  pinMode(REEDR, INPUT_PULLUP);

  // Anemomether
  pinMode(REED, INPUT_PULLUP);

  // SD Card
  pinMode(pinCS, OUTPUT);
  if (!SD.begin(8)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");

  // Clock
  if (! rtc.begin())
  {
    Serial.println("Módulo RTC no encontrado!");
    while(1);
    
  }
  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Upload code once with this line uncommented so the clock is adjusted, then coment this line and upload again
  
  // Temp and Humi
  Wire.begin();

  if(AHT10.begin(eAHT10Address_Low)){
    Serial.println("Init AHT10 Success!");
  } 
  else{
    Serial.println("Init AHT10 Failed!");
  }
  
}

void loop(){
  
  if (analogRead(LDR > 700)){
    superDelay(3600000);
    // Anemomether
    windspeed = 2 * pi * radius * (REEDCOUNT / (60 * 60));
    readAndSave();
  }
  else{
    superDelay(7200000);
    // Anemomether
    windspeed = 2 * pi * radius * (REEDCOUNT / (60 * 120));
    readAndSave();
  }

}
