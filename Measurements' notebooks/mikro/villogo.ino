const int pinLED = 13;              // melyik labon van a LED
const int pinKAPCSOLO = 12;         // melyik labon van a kapcsolo

void setup() {
  pinMode(pinLED, OUTPUT);          // a LED portja irhato
  pinMode(pinKAPCSOLO, INPUT);      // a kapcsolo portja olvashato
}

void beki(int lab, int tart, int var) {
  digitalWrite(lab, HIGH);          // magas ki, LED vilagit
  delay(tart);                      // var tart ms-ot
  digitalWrite(lab, LOW);           // alacsony ki, LED elalszik
  delay(var);                       // var var ms-ot
}

void loop() {
  int stateKAPCSOLO = digitalRead(pinKAPCSOLO); // kapcsolo pillanatnyi allapota
  if (stateKAPCSOLO == LOW) {       // elengedett kapcsolo
    beki(pinLED, 500, 500);
  } else {                          // nyomva tartott kapcsolo
    beki(pinLED, 125, 875);
  }
}
