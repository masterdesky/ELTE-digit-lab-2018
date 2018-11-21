const int pinLED = 13;              // melyik labon van a LED
const int pinKAPCSOLO = 12;         // melyik labon van a kapcsolo

const int pinTANLED = 8;
const int pinTANKAPCS = 7;

int currentState;

void setup()
{
  int currentState = 0;
  
  pinMode(pinLED, OUTPUT);          // a LED portja irhato
  pinMode(pinKAPCSOLO, INPUT);      // a kapcsolo portja olvashato
  pinMode(pinTANLED, OUTPUT);          // a LED portja irhato
  pinMode(pinTANKAPCS, INPUT);      // a kapcsolo portja olvashato
}

void ledOnOff(int lab, int state)
{
  if(state == 0)
  {
    digitalWrite(lab, HIGH);
  }

  else
  {
    digitalWrite(lab, LOW);
  }
}

// Constant light for the LearnLED if lerining mode is active
void power(int lab)
{
  digitalWrite(lab, HIGH);
}

void NOpower(int lab)
{
  digitalWrite(lab, LOW);
}


// LEARING MODE
int learn(int lab, unsigned long* ElapsedTimes)
{
  int ElementCounter = 0;
  
  // HIGH == 1
  // LOW == 0
  int HighOrLow;
  
  while(1)
  {
    // LearnLED is constantly in high position when in learn mode
    power(pinTANLED);
    
    int stateKAPCSOLO = digitalRead(pinKAPCSOLO); // kapcsolo pillanatnyi allapota
    int stateTANKAPCSOLO = digitalRead(pinTANKAPCS); // TANkapcsolo pillanatnyi allapota
    
    // Button is NOT pressed
    if (stateKAPCSOLO == LOW)
    {
      HighOrLow = 0;
      // Measuring time
      unsigned long StartTime = millis();
      while(1)
      {
        ledOnOff(pinLED, 0);
        
        if(stateKAPCSOLO == HIGH)
        {
          break;
        }
      }
      unsigned long CurrentTime = millis();
      unsigned long ElapsedTime = CurrentTime - StartTime;
      
      ElapsedTimes[ElementCounter] = ElapsedTime;
      ElementCounter++;
    }
    
    // Button is pressed
    else
    {
      HighOrLow = 1;
      // Measuring time
      unsigned long StartTime = millis();
      while(1)
      {
        ledOnOff(pinLED, 1);
        
        if(stateKAPCSOLO == LOW)
        {
          break;
        }
      }
      unsigned long CurrentTime = millis();
      unsigned long ElapsedTime = CurrentTime - StartTime;
      
      ElapsedTimes[ElementCounter] = ElapsedTime;
      ElementCounter++;
    }
    
    if(stateTANKAPCSOLO == LOW)
    {
      
      break;
    }
  }
  
  return HighOrLow;
}

// PALAYING MODE
void play(int lab, unsigned long* ElapsedTimes, int HighOrLow)
{
  int stateTANKAPCSOLO = digitalRead(pinTANKAPCS); // TANkapcsolo pillanatnyi allapota
  
  NOpower(pinTANLED);
  
  int ElementCounter = 0;
  
  while(1)
  {
    if(HighOrLow == 0)
    {
      digitalWrite(lab, LOW);
      delay(ElapsedTimes[ElementCounter]);
      ElementCounter++;
    }
    
    if(HighOrLow == 1)
    {
      digitalWrite(lab, HIGH);
      delay(ElapsedTimes[ElementCounter]);
      ElementCounter++;
    }
      
    if(ElementCounter > sizeof(ElapsedTimes)/sizeof(ElapsedTimes[0]))
    {
      ElementCounter = 0;
    }
    
    if(stateTANKAPCSOLO == LOW)
    {
      break;
    }
  }
}

void loop()
{
  unsigned long* ElapsedTimes = (unsigned long*)malloc(32 * sizeof(unsigned long));
  
  int HighOrLow;
  
  if (currentState == 0)
  {
    HighOrLow = learn(pinLED, ElapsedTimes);
    
    currentState = 1;
  }

  else
  {
    play(pinLED, ElapsedTimes, HighOrLow);
    
    currentState = 0;
  }
}
