#include "Wire.h";
#include "LiquidCrystal_I2C.h";
 
// Define o endereço utilizado pelo Adaptador I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
// Constantes:
const int REED = 5;
 
// Variáveis:
int val = 0;
int old_val = 0;
int REEDCOUNT = 0;
 
void setup() ,
{
  // Initializa o pino do switch como entrada
  pinMode (REED, INPUT_PULLUP); //This activates the internal pull up resistor
 
  // Initializa a comunicaçao serial:
  Serial.begin(9600);
 
  //Inicializa o LCD e o backlight
  lcd.init();
  lcd.backlight();
 
  lcd.setCursor(0, 0);      // Posiciona o cursor
  lcd.print("Pulsos: ");    // Escreve no LCD "Pulsos: "
  lcd.setCursor(0, 1);      // Posiciona o cursor
  lcd.print("Chuva: ");     // Escreve no LCD "Chuva: "
}
 
void loop() 
{
  val = digitalRead(REED);      // Lê o Status do Reed Switch
 
  if ((val == LOW) && (old_val == HIGH)) {   // Verefica se o Status mudou
    delay(100);                   // Atraso colocado para lidar com qualquer "salto" no switch.
    REEDCOUNT = REEDCOUNT + 1;   // Adiciona 1 à cntagem de pulsos
    old_val = val;              //Iguala o valor antigo com o atual
 
    // Imprime no Monitor Serial
    Serial.print("Medida de chuva (contagem): ");
    Serial.print(REEDCOUNT);
    Serial.println(" pulso");
    Serial.print("Medida de chuva (calculado): ");
    Serial.print(REEDCOUNT * 0.50);
    Serial.println(" mm");
 
    // Imprime as informações do Display
    lcd.setCursor(8, 0);         //Posiciona o cursor
    lcd.print(REEDCOUNT);        //Escreve o número de Pulsos
    lcd.setCursor(8, 1);         //Posiciona o cursor
    lcd.print(REEDCOUNT * 0.50); //Escreve o valor em milímetros
    lcd.setCursor(14, 1);        //Posiciona o cursor
    lcd.print("mm");             //Escreve no LCD "mm"
  }
 
  else {
    old_val = val;              //If the status hasn't changed then do nothing
  }
}
