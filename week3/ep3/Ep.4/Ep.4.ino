#include<Servo.h>
Servo myServo;
int servoPos = 0;
int servoIncrement = 2;
void setup() {
  myServo.attach(9);

}

void loop() {
  servoSweep();
  delay(20);

}

void servoSweep(){
  servoPos = servoPos + servoIncrement;
  if ((servoPos < 0 || servoPos > 180)){
      servoIncrement = -servoIncrement;
  }
  myServo.write(servoPos);
}
