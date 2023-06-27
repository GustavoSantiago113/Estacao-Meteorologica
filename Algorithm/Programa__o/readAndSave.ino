void readAndSave(){
  
  // Anemomether
  windspeed = 2 * pi * radius * (REEDCOUNT / (60 * 30));
  //windspeed = 2 * pi * radius * (REEDCOUNT / (60));
  REEDCOUNT = 0;
  // Luminosity
  light = analogRead(LDR);

  // Temp & Umi
  umi = AHT10.GetHumidity();
  temp = AHT10.GetTemperature();

  // Pluviomether
  rain = REEDCOUNTR / 11.00;

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
  myFile.print(light);
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
  Serial.print(light);
  Serial.print(",");
  Serial.print(umi);
  Serial.print(",");
  Serial.println(temp);
}  
  