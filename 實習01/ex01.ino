const int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  for (int i=0; i<=20; i+=2) {
    digitalWrite(LED, HIGH);
    delay(i*10);
    digitalWrite(LED, LOW);
    delay(i*10);
  }

  for (int i=20; i>=0; i-=2) {
    digitalWrite(LED, HIGH);
    delay(i*10);
    digitalWrite(LED, LOW);
    delay(i*10);
  }

}
