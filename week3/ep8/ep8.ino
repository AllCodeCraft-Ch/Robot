#include<Servo.h>
Servo myServo;
int servoPos = 0;
int servoIncrement = 2;
int ledState = LOW;
int brightness = 0;
int fadeIncrement = 1;
int toggleState = LOW;

unsigned long C = 0;
unsigned long P_1 = 0;
unsigned long P_2 = 0;
unsigned long P_3 = 0;
unsigned long P_4 = 0;

void setup() {
  pinMode(2, INPUT);
  myServo.attach(9);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  C = millis();
  blinkLED();
  fadeLED();
  toggleLED();
  servoSweep();
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

void servoSweep(){
  if(C - P_4 >= 15){
    P_4 = C;
    servoPos = servoPos + servoIncrement;
    if ((servoPos < 0 || servoPos > 180)){
      servoIncrement = -servoIncrement;
  }
  myServo.write(servoPos);
    }
}



















 
