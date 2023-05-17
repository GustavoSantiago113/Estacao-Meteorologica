#include <Wire.h>
#include <RTClib.h>
 
RTC_DS3231 rtc;

void setup(){
  
  Serial.begin(9600); //INICIALIZA A SERIAL
  
  if (! rtc.begin())
  {
    Serial.println("Módulo RTC no encontrado!");
    while(1);
    
  }
  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
}
 
void loop () 
{
 DateTime fecha = rtc.now();

 Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("/");
  Serial.print(fecha.year());
  Serial.print(",");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.println(fecha.minute());
  
 delay(1000);
}
