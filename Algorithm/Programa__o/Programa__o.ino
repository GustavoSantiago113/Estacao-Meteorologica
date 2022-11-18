// Autor: Gustavo Nocera Santiago
#include <Adafruit_AHT10.h>; //INCLUI A BIBLIOTECA DHT
#include <Wire.h> // Inclui a biblioteca Wire
#include <LiquidCrystal_I2C.h> // Usando a biblioteca LiquidCrystal I2C
#include <SD.h> //Biblioteca do cartão SD
#include <SPI.h>
#include <RTClib.h>

Adafruit_AHT10 aht;
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configura endereço I2C e display com 16 caracteres e 2 linhas 

#define LDR A0 //Pino em que está o LDR

//VARIÁVEIS
const int REED = 5; //PINO EM QUE ESTÁ O PINO REED SWITCH
int val = 0; //INICIALIZA OS VALORES QUE SERÃO USADOS PARA CONTAGEM DOS PULSOS DE CHUVA 
int old_val = 0;
int REEDCOUNT = 0;
int chuva = 0; //Armazena o valor da chuva acumulada
int vol = 2.83; //Valor do volume da bascula (em mm)

const int REEDv = 2;
int valv = 0;
int old_valv = 0;
int REEDCOUNTv = 0;
const float p = 3.14159265;
int raio = 65;
float windspeed = 0;

int luminosidade; //Variável para armazenar o valor da luminosidade
int energia;

File myFile;
int pinoCS = 10;

void setup() 
{
  
  Serial.begin(9600);
  pinMode (REED, INPUT_PULLUP); //DIZ QUE O PINO DO REED É DE ENTRADA
  pinMode(5, INPUT);        //configura o digital 5 como entrada para o reedswitch do vento
  digitalWrite(5, HIGH);    //internall pull-up active
  pinMode (REEDv, INPUT_PULLUP);
  pinMode(2, INPUT);
  rtc.begin();
  rtc.adjust(DateTime(2021, 10, 26, 15, 24, 00)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  lcd.init();
  lcd.backlight();
  aht.begin();
  pinMode(pinoCS,OUTPUT);
  SD.begin(pinoCS);
  
}

void loop() 
{
     
     superDelay(60000);
     windspeed = ((2 * p * REEDCOUNTv) / 60) * raio/1000;
     chuva = REEDCOUNT / vol;
     sensors_event_t humidity, temp;
     aht.getEvent(&humidity,&temp);
     luminosidade = analogRead(LDR);
     energia = map(luminosidade, 0, 1023, 0, 100);
     lcd.cursor(); //Liga o cursor
     lcd.setCursor(0,0); //Seleciona a coluna 0 e linha 0
     lcd.print(humidity.relative_humidity);
     lcd.setCursor(5,0); //Seleciona a coluna 5 e linha 0
     lcd.print("%");
     lcd.setCursor(7,0); //Seleciona a coluna 7 e linha 0
     lcd.print(temp.temperature);
     lcd.setCursor(13,0); //Seleciona a coluna 12 e linha 0
     lcd.print("C");
     lcd.setCursor(0,1); //Seleciona a coluna 0 e linha 1
     lcd.print(windspeed);
     lcd.setCursor(4,1); //Seleciona a coluna 4 e linha 1
     lcd.print("m/s");
     lcd.setCursor(8,1); //Seleciona a coluna 9 e linha 1
     lcd.print(chuva);
     lcd.setCursor(14,1); //Seleciona a coluna 9 e linha 1
     lcd.print("mm"); //Seleciona a coluna 9 e linha 1
     DateTime fecha = rtc.now();
     myFile = SD.open("Meteorologia.txt", FILE_WRITE);
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
     myFile.print(chuva);
     myFile.print(",");
     myFile.print(humidity.relative_humidity);
     myFile.print(",");
     myFile.print(temp.temperature);
     myFile.print(",");
     myFile.print(windspeed);
     myFile.print(",");
     myFile.println(energia);
     myFile.close();
     REEDCOUNTv = 0;  
       
}

void superDelay(unsigned long tempoDeEspera) 
{
  
  unsigned long inicio = millis(); // ANOTA O TEMPO QUE INICIOU A FUNÇÃO
  while (millis() - inicio < tempoDeEspera) 
  { // LAÇO PARA O ARDUINO ESPERAR O TEMPO PASSAR
    // === COLOQUE SUA LÓGICA AQUI ===
    val = digitalRead(REED); //VERIFICA O ESTADO DO PINO REED (ALTO OU BAIXO)
    if ((val == LOW) && (old_val == HIGH)) // Verefica se o Status mudou
    {   
      delay(70);                   // Atraso colocado para lidar com qualquer "salto" no switch.
      REEDCOUNT = REEDCOUNT + 1;   // Adiciona 1 à contagem de pulsos
     old_val = val;              //Iguala o valor antigo com o atual
    } 
    else 
    {
      old_val = val;              //Se o status não mudou, faça nada
    }
    
    //LÊ E ARMAZENA OS VALORES DE UMIDADE E TEMPERATURA;
    
    valv = digitalRead(REEDv);      // Lê o Status do Reed Switch
    if ((valv == LOW) && (old_valv == HIGH)) 
    {   // Verefica se o Status mudou
      delay(70);                   // Atraso colocado para lidar com qualquer "salto" no switch.
      REEDCOUNTv = REEDCOUNTv + 1;   // Adiciona 1 à cntagem de pulsos
      old_valv = valv;              //Iguala o valor antigo com o atual
    }
 
    else 
    {
      old_valv = valv;              //If the status hasn't changed then do nothing
    }
    
  }
    // FIM DA LÓGICA DENTRO DO SUPERDELAY
}
  
