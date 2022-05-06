#include "Wire.h";
#include "LiquidCrystal_I2C.h";
 
// Define o endereço utilizado pelo Adaptador I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
// Constantes:
const int REED = 2;
 
// Variáveis:
int val = 0;
int old_val = 0;
int REEDCOUNT = 0;

const float pi = 3.14159265;
int radius = 65;
float windspeed = 0;
 
void setup()
{
  // Initializa o pino do switch como entrada
  pinMode (REED, INPUT_PULLUP); //This activates the internal pull up resistor
 
  // Initializa a comunicaçao serial:
  Serial.begin(9600);
 
  //Inicializa o LCD e o backlight
  lcd.init();
  lcd.backlight();
 
  lcd.setCursor(0, 0);      // Posiciona o cursor
  lcd.print("Velocidade ");    // Escreve no LCD "Velocidade: "
}
 
void loop() 
{
  // Imprime no Monitor Serial
    superDelay(60000);
    windspeed = ((2 * pi * REEDCOUNT) / 60) * radius/1000;
    Serial.print("Contagem: ");
    Serial.print(REEDCOUNT);
    Serial.println(" pulsos");
    Serial.print("Velocidade do vento: ");
    Serial.print(windspeed);
    Serial.println(" m/s");
 
    // Imprime as informações do Display
    lcd.setCursor(0, 1);         //Posiciona o cursor
    lcd.print(windspeed); //Escreve o valor em milímetros
    lcd.setCursor(13, 1);        //Posiciona o cursor
    lcd.print("m/s");             //Escreve no LCD "mm"
    REEDCOUNT = 0;
}

void superDelay(unsigned long tempoDeEspera) 
{
  unsigned long inicio = millis(); // ANOTA O TEMPO QUE INICIOU A FUNÇÃO

  while (millis() - inicio < tempoDeEspera) 
  { // LAÇO PARA O ARDUINO ESPERAR O TEMPO PASSAR
    // === COLOQUE SUA LÓGICA AQUI ===
    val = digitalRead(REED);      // Lê o Status do Reed Switch
   if ((val == LOW) && (old_val == HIGH)) 
   {   // Verefica se o Status mudou
    delay(70);                   // Atraso colocado para lidar com qualquer "salto" no switch.
    REEDCOUNT = REEDCOUNT + 1;   // Adiciona 1 à cntagem de pulsos
    old_val = val;              //Iguala o valor antigo com o atual
   }
 
  else 
  {
    old_val = val;              //If the status hasn't changed then do nothing
  }
    // FIM DA LÓGICA DENTRO DO SUPERDELAY
  }
}
