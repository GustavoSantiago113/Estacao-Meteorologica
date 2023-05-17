#include <SD.h>
#include <SPI.h>
 
File myFile;
 
const int pinoCS = 10; // Pin 53 para Mega / Pin 10 para UNO
#define LDR A0 //Pino em que está o LDR
int luminosidade; //Variável para armazenar o valor da luminosidade
int energia;

void setup() 
{ // Executado uma vez quando ligado o Arduino
 
Serial.begin(9600); // Define BaundRate
pinMode(pinoCS, OUTPUT); // Declara pinoSS como saída

if (!SD.begin(8)) {
    Serial.println("Card failed, or not present");
    digitalWrite(LED_BUILTIN, HIGH);
    return;
  }SD.begin(8);
 
}
 
void loop() 

{
  luminosidade = analogRead(LDR);
  energia = map(luminosidade, 0, 1023, 0.0, 100.00);
  myFile = SD.open("test.txt", FILE_WRITE);
  myFile.print(energia);
  myFile.println("%");
  myFile.close();
  Serial.print(energia);
  Serial.println(" %");
  delay(1000);
  
}
