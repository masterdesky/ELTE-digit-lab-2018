int pinLED = 11;               // kimeno lab
int alpha;                     // kitoltesi tenyezo 1/255 egysegekben
boolean dir;                   // valtozas iranya

void setup() {
  pinMode(pinLED, OUTPUT);     // a LED portjat irjuk
  alpha = 0;
  dir = false;
}

void loop() {
  if ((alpha == 0) or (alpha == 255)) {
    dir = ! dir;               // vegallapotban fordulunk
  }
  analogWrite(pinLED, alpha);  // igazitsunk a generatoron
  if (dir) {                   // kitoltesi tenyezo frissitese
    alpha++;
  } else {
    alpha--;
  }
  delay(2);                    // szusszanjunk 2 ms-t
}
