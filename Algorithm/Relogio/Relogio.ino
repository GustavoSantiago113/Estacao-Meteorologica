#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
 
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  Serial.begin(9600); //INICIALIZA A SERIAL
  lcd.init();
  lcd.backlight();
  if (! rtc.begin())
  {
    Serial.println("Módulo RTC no encontrado!");
    while(1);
    
  }
  rtc.adjust(DateTime(2021, 10, 22, 10, 21, 0));
}
 
void loop () 
{
 DateTime fecha = rtc.now();

 
 delay(1000);
}
