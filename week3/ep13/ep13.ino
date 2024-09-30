#include<Servo.h>

#define SERVO_PIN 9
#define LED_RED 5
#define LED_GREEN 6
#define BUTTON_PIN 2

Servo servo_1;
volatile int pos = 180;

void setup() {
  Serial.begin(9600);

  pinMode(SERVO_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  servo_1.attach(SERVO_PIN);
  servo_1.write(pos);
  delay(1000);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Doreamon,LOW); //กดปุ่มแล้ว FALLING เข้าทำ Doreamon - ปล่อยปุ่มแล้ว RISING เข้าทำ Doreamon - CHANGE กดเข้า Doreamon ปล่อยเข้า Doreamon
}

void Doreamon(){
  pos = 180;
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
}

void loop() {
  // ปัดขวา
  for(pos = 180;pos > 90;pos--){
    servo_1.write(pos);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
    delay(40);
  }
  // ปัดซ้าย
  for(pos = 90;pos < 180;pos++){
    servo_1.write(pos);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
    delay(40);
  }

}











