int ledState = LOW;
int brightness = 0;
int fadeIncrement = 1;

unsigned long C = 0;
unsigned long P_1 = 0;
unsigned long P_2 = 0;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  C = millis();
  blinkLED();
  fadeLED();
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
 
