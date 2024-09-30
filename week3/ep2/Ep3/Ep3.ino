int toggleState = LOW;
void setup() {
  pinMode(10, OUTPUT);
  pinMode(2, INPUT);

}

void loop() {
  toggleLED();
  delay(50);

}

void toggleLED(){
  if (digitalRead(2) == HIGH){
    toggleState = HIGH;
  }
  else {
    toggleState = LOW;
  }
  digitalWrite(10, toggleState);
}
