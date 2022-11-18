#include <SD.h>
#include <SPI.h>
 
File myFile;
 
int pinoCS = 10; // Pin 53 para Mega / Pin 10 para UNO
#define LDR A0 //Pino em que está o LDR
int luminosidade; //Variável para armazenar o valor da luminosidade
int energia;

void setup() 
{ // Executado uma vez quando ligado o Arduino
 
Serial.begin(9600); // Define BaundRate
pinMode(pinoCS, OUTPUT); // Declara pinoSS como saída
SD.begin(pinoCS);
 // Cria / Abre arquivo .txt
 
}
 
void loop() 

{
  luminosidade = analogRead(LDR);
  energia = map(luminosidade, 0, 1023, 0, 100);
  myFile = SD.open("teste.txt", FILE_WRITE);
  myFile.print(energia);
  myFile.println("%");
  myFile.close();
  delay(1000);
  
}
