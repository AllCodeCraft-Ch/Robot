int ledState = LOW;
int brightness = 0;
int fadeIncrement = 1;
int toggleState = LOW;

unsigned long C = 0;
unsigned long P_1 = 0;
unsigned long P_2 = 0;
unsigned long P_3 = 0;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  C = millis();
  blinkLED();
  fadeLED();
  toggleLED();
}

void blinkLED(){
  if (C - P_1 >= 500){
    P_1 = C;
    ledState = !ledState;
    digitalWrite(12, ledState);
  }
}

void fadeLED(){
if (C - P_2 >= 5){
  P_2 = C;
  brightness = brightness + fadeIncrement;
    if ((brightness < 0 || brightness > 255)){
      fadeIncrement = -fadeIncrement;
  }
  analogWrite(11, brightness);
  }
}

void toggleLED(){
  if(C - P_3 >= 100){
    P_3 = C;
    if(digitalRead(2) == HIGH){
    toggleState = HIGH;
  }
  else {
    toggleState = LOW;
  }
  digitalWrite(10, toggleState);
  }
}



















 
