// Author: Gustavo Nocera Santiago

// Including Libraries
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <AHT10.h>

// Soil moisture variable
#define soil A1

// Anemomether variables
const int REED = 3;
int val = 0;
int old_val = 0;
int REEDCOUNT = 0;
const float pi = 3.14159265;
float radius = 0.065;
float windspeed = 0;

// Luminosity variables
#define LDR A0
int light;
int energy;

// Pluviomether variables
const int REEDR = 4;
int valR = 0;
int old_valR = 0;
int REEDCOUNTR = 0;
float rain = 0.00;

// Temp and Humi Class
AHT10Class AHT10;

int counter = 0;

void setup(){
  
  Serial.begin(9600);
  
  // Pluviomether
  pinMode(REEDR, INPUT_PULLUP);

  // Anemomether
  pinMode(REED, INPUT_PULLUP);
  
  // Temp, Humi and Pressure
  Wire.begin();

  // Temp and Humi
  Wire.begin();

  if(AHT10.begin(eAHT10Address_Low)){
    Serial.println("Init AHT10 Success!");
  } 
  else{
    Serial.println("Init AHT10 Failed!");
  }

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSyncWord(0xF3);
  LoRa.setTxPower(20);
  
}

void loop(){
  
  superDelay(5000);
  
  // Anemomether
  windspeed = 2 * pi * REEDCOUNT * 60 * radius * 12 / 1000;
  REEDCOUNT = 0;

  // Luminosity
  light = analogRead(LDR);
  energy = map(light, 1023, 0, 0, 100);

  // Pluviomether
  rain = REEDCOUNTR / 11.00;

  Serial.print("Rain: ");
  Serial.print(rain);
  Serial.print(", ");
  Serial.print("Wind Speed: ");
  Serial.print(windspeed);
  Serial.print(", ");
  Serial.print("Luminosity: ");
  Serial.print(energy);
  Serial.print(", ");
  Serial.print("Humidity: ");
  Serial.print(AHT10.GetHumidity());
  Serial.print(", ");
  Serial.print("Temperature: ");
  Serial.print(AHT10.GetTemperature());
  Serial.print(", ");
  Serial.print("Soil moisture: ");
  Serial.println(analogRead(soil));

  //LoRa.beginPacket();
  //LoRa.print("Hello world!!");
  //LoRa.print(counter);
  //LoRa.endPacket();
  
  counter++;

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
