void setup() {
  Serial.begin(9600);

}

void loop() {
  unsigned long c;
  c = millis();
  Serial.println(c);

}
