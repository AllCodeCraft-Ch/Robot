int ledState = LOW;
unsigned long C = 0;
unsigned long P = 0;
void setup() {
  pinMode(12, OUTPUT);
}

void loop() {
  C = millis();
  blinkLED();
}

void blinkLED(){
  if (C - P >= 500){
    P = C;
    ledState = !ledState;
    digitalWrite(12, ledState);
  }
}