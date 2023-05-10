#include <AHT10.h>
#include <Wire.h>

AHT10Class AHT10;

void setup() {

  Serial.begin(9600);

  Wire.begin();

  if
(AHT10.begin(eAHT10Address_Low))


Serial.println("Init AHT10 Success!");

  else


Serial.println("Init AHT10 Failed!");

}

void loop() {


Serial.println("//Arduino & AHT10//");


Serial.println("Quick Test – Serial Monitor");


Serial.println(String("") + "Humidity(%RH):\t\t" +
AHT10.GetHumidity() + "%");


Serial.println(String("") + "Temperature(℃):\t"
+ AHT10.GetTemperature() + "℃");

delay(1000);

}
