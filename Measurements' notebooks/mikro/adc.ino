int pinPOTM = A0;             // az analog szenzor kimeno laba

void setup() {
  Serial.begin(9600);         // soros vonal beallitasa
  Serial.println("adatok");   // hello uzenet
}

void loop() {
  int sample = analogRead(pinPOTM); // szenzor kiolvasasa
  Serial.println(sample);     // adatok soros vonalra irasa
  delay(500);                 // 0,5 sec szusszanas a kovetkezo minta elott
}
