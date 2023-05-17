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
  
  superDelay(300000);
  //superDelay(1000);
  
  // Anemomether
  windspeed = 2 * pi * REEDCOUNT * 60 * radius * 12 / 1000;
  REEDCOUNT = 0;

  // Luminosity
  light = analogRead(LDR);
  energy = map(light, 0, 1023, 0, 100);

  // Temp & Umi
  umi = AHT10.GetHumidity();
  temp = AHT10.GetTemperature();

  // Pluviomether
  rain = REEDCOUNTR / 11.00;

  // Clock
  DateTime fecha = rtc.now();
  
  // Saving everything on SD Card
  myFile = SD.open("WSKSU.txt", FILE_WRITE);
  myFile.print(fecha.day());
  myFile.print("/");
  myFile.print(fecha.month());
  myFile.print("/");
  myFile.print(fecha.year());
  myFile.print(",");
  myFile.print(fecha.hour());
  myFile.print(":");
  myFile.print(fecha.minute());
  myFile.print(",");
  myFile.print(rain);
  myFile.print(",");
  myFile.print(windspeed);
  myFile.print(",");
  myFile.print(energy);
  myFile.print(",");
  myFile.print(umi);
  myFile.print(",");
  myFile.println(temp);
  myFile.close();

  Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("/");
  Serial.print(fecha.year());
  Serial.print(",");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.print(fecha.minute());
  Serial.print(",");
  Serial.print(rain);
  Serial.print(",");
  Serial.print(windspeed);
  Serial.print(",");
  Serial.print(energy);
  Serial.print(",");
  Serial.print(umi);
  Serial.print(",");
  Serial.println(temp);
  
}

// Function to make anemomether works while other processes are happening
void superDelay(unsigned long tempoDeEspera) 
{
  unsigned long inicio = millis(); 
  while (millis() - inicio < tempoDeEspera) 
  { 
    // Wind
    val = digitalRead(REED);     
     if ((val == LOW) && (old_val == HIGH)) 
     {   
      delay(70);                   
      REEDCOUNT = REEDCOUNT + 1;   
      old_val = val;              
     }
   
    else 
    {
      old_val = val;
    }

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
