#include "Wire.h";
 
// Constantes:
const int REED = 2;
 
// Variáveis:
int val = 0;
int old_val = 0;
int REEDCOUNT = 0;

const float pi = 3.14159265;
float radius = 0.065;
float windspeed = 0;
 
void setup()
{
  // Initializa o pino do switch como entrada
  pinMode (REED, INPUT_PULLUP); //This activates the internal pull up resistor
 
  // Initializa a comunicaçao serial:
  Serial.begin(9600);
 
}
 
void loop() 
{
  // Imprime no Monitor Serial
    superDelay(5000);
    windspeed = 2 * pi * REEDCOUNT * 60 * radius * 12 / 1000;
    Serial.print("Contagem: ");
    Serial.print(REEDCOUNT);
    Serial.println(" pulsos");
    Serial.print("Velocidade do vento: ");
    Serial.print(windspeed);
    Serial.println(" m/s");

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
