int ledState = LOW;
void setup() {
  pinMode(12, OUTPUT);

}

void loop() {
  blinkLED();
  delay(500);

}

void blinkLED(){
  digitalWrite(12, ledState);
  ledState = !ledState;
}
