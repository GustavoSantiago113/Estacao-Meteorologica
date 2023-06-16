#include <SD.h>
#include <SPI.h>
#include <RTClib.h>
 
RTC_DS3231 rtc;
 
File myFile;
 
const int pinoCS = 10; // Pin 53 para Mega / Pin 10 para UNO

void setup() 
{ // Executado uma vez quando ligado o Arduino
 
Serial.begin(9600); // Define BaundRate
pinMode(pinoCS, OUTPUT); // Declara pinoSS como saída

if (!SD.begin(8)) {
    Serial.println("Card failed, or not present");
    return;
  }SD.begin(8);

if (! rtc.begin())
  {
    Serial.println("Módulo RTC no encontrado!");
    while(1);
    
  }
  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 
}
 
void loop() 

{
  myFile = SD.open("test.txt", FILE_WRITE);
  DateTime fecha = rtc.now();
  myFile.print(fecha.day());
  myFile.print("/");
  myFile.print(fecha.month());
  myFile.print("/");
  myFile.print(fecha.year());
  myFile.print(",");
  myFile.print(fecha.hour());
  myFile.print(":");
  myFile.println(fecha.minute());

  myFile.close();

  Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("/");
  Serial.print(fecha.year());
  Serial.print(",");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.println(fecha.minute());

  delay(60000);
  
}
