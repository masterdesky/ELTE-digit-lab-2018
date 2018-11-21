// meghajto vezerlesehez szukseges konyvtar
#include <LiquidCrystal.h>

// inicializalas az LCD huzalozasaval osszhangban
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchPin = 6;        // higyankapcsolo laba
int switchState = 0;            // kapcsolo allapota
int prevSwitchState = 0;        // kapcsolo elozo allapota
int reply;                      // tarolo

void setup() {
  lcd.begin(16, 2);             // LCD 16 karakter mindket sorban
  pinMode(switchPin, INPUT);    // higanykapcsolo bemenetkent
  lcd.print("Alapallapot. Ova");// elso uzenet
  lcd.setCursor(0, 1);
  lcd.print("tosan razz meg..");
}

void loop() {
  switchState = digitalRead(switchPin);   // kapcsolo allapota
  if (switchState != prevSwitchState) {   // atmenet
    if (switchState == LOW) {
      reply = random(8);                  // sorsoljunk szamot
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sorsoltam:");
      lcd.setCursor(0, 1);
      switch (reply) {                    // sorsolas fuggo uzenet az LCD-re
        case 0:
        lcd.print("nulla");
        break;
        case 7:
        lcd.print("nemkocka");
        break;
        default:
        lcd.print(reply);
        break;
      }
    }
  }
  prevSwitchState = switchState;          // kapcsolo allapotanak mentese
}
