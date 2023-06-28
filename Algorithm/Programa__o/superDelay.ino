// Function to make anemomether works while other processes are happening
void superDelay(unsigned long tempoDeEspera) 
{
  unsigned long inicio = millis(); 
  while (millis() - inicio < tempoDeEspera) 
  { 
    // Wind
    val = digitalRead(REED);     
     if ((val == LOW) && (old_val == HIGH)) 
     {   
      delay(70);                   
      REEDCOUNT = REEDCOUNT + 1;   
      old_val = val;              
     }
   
    else 
    {
      old_val = val;
    }

    // Rain
    valR = digitalRead(REEDR);
    
    if ((valR == LOW) && (old_valR == HIGH)) {
      delay(70);
      REEDCOUNTR = REEDCOUNTR + 1;
      old_valR = valR;
    }
    else {
      old_valR = valR;
    }
    
  }
}
