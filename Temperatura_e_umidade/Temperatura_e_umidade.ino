#include <Adafruit_AHT10.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

Adafruit_AHT10 aht;
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  Serial.begin(9600);
  Serial.println("Teste de temperatura e umidade");

  if (! aht.begin()) 
  {
    Serial.println("Não localizou o sensor continue tentando");
    while (1) delay(10);
  }
  Serial.println("AHT10 encontrado");
  lcd.init();
  lcd.backlight();
  if (! rtc.begin())
  {
    Serial.println("Módulo RTC no encontrado!");
    while(1);
    
  }
  rtc.adjust(DateTime(2021, 10, 26, 13, 32, 0));
}

void loop() 
{
 DateTime fecha = rtc.now();
 lcd.setCursor(0, 0);
 lcd.print(fecha.hour());
 lcd.setCursor(3, 0);
 lcd.print(fecha.minute());
 lcd.setCursor(7, 0);
 lcd.print(fecha.second());
 sensors_event_t humidity, temp;
 aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
 Serial.print("Temperatura: "); Serial.print(temp.temperature); Serial.println(" C");
 Serial.print("Umidade: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
 lcd.setCursor(0, 1);
 lcd.print(temp.temperature);
 lcd.setCursor(3, 1);
 lcd.print(humidity.relative_humidity);
 delay(1000);
}
