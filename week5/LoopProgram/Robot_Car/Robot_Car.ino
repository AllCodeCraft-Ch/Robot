#include "Arduino_LED_Matrix.h"
#include "animation_go.h"
#include "animation_back.h"
#include "animation_L.h"
#include "animationloopL.h"
#include "animation_R.h"
#include "animationloopR.h"
#include "animationstop.h"

ArduinoLEDMatrix matrix;

// มอเตอร์ซ้าย
int ENA = 10;
int IN1 = 9;
int IN2 = 8;
// มอเตอร์ขวา
int ENB = 5;
int IN3 = 7;
int IN4 = 6;

// ใช้ชดเชยการเบี้ยวของการเคลื่อนที่
int B_L = 0; // ล้อซ้าย
int B_R = 0; // ล้อขวา

void setup() {
  // กำหนดให้ขาต่าง ๆ เป็นอินพุตและเอาต์พุต
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // เปลี่ยนความละเอียดของ PWM จาก 0 - 255 เป็น 0 - 4095
  analogWriteResolution(12);

  // เริ่มต้น LED matrix และโหลด animation
  matrix.begin();
  matrix.loadSequence(animation_go);
  matrix.loadSequence(animation_back);
  matrix.loadSequence(animation_L);
  matrix.loadSequence(animation_R);
  matrix.loadSequence(animationloopR);
  matrix.loadSequence(animationloopL);
  matrix.loadSequence(animationstop);
}

void forward() {
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เคลื่อนที่ไปข้างหน้าด้วยความเร็วคงที่
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  matrix.loadSequence(animation_go);
  matrix.play(true);
  analogWrite(ENA, 4000 - B_L);
  analogWrite(ENB, 4000 - B_R);
}

void backward() {
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เคลื่อนที่ไปข้างหลังด้วยความเร็วคงที่
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  matrix.loadSequence(animation_back);
  matrix.play(true);
  analogWrite(ENA, 4000 - B_L);
  analogWrite(ENB, 4000 - B_R);
}

void forward_left() {
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เลี้ยวซ้าย
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  matrix.loadSequence(animation_R);
  matrix.play(true);
  analogWrite(ENA, 0);
  analogWrite(ENB, 4000 - B_R);
}

void backward_left() {
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เลี้ยวซ้ายแบบถอยหลัง
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  matrix.loadSequence(animation_L);
  matrix.play(true);
  analogWrite(ENA, 0);
  analogWrite(ENB, 4000 - B_R);
}

void forward_right() {
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เลี้ยวขวา
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  matrix.loadSequence(animation_L);
  matrix.play(true);
  analogWrite(ENA, 4000 - B_L);
  analogWrite(ENB, 0);
}

void backward_right() {
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์ถอยหลังเลี้ยวขวา
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  matrix.loadSequence(animation_R);
  matrix.play(true);
  analogWrite(ENA, 4000 - B_L);
  analogWrite(ENB, 0);
}

void around_right() {
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์หมุนรอบตัวเองไปทางขวา
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  matrix.loadSequence(animationloopR);
  matrix.play(true);
  analogWrite(ENA, 4000 - B_L);
  analogWrite(ENB, 4000 - B_R);
}

void around_left() {
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์หมุนรอบตัวเองไปทางซ้าย
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  matrix.loadSequence(animationloopL);
  matrix.play(true);
  analogWrite(ENA, 4000 - B_L);
  analogWrite(ENB, 4000 - B_R);
}

void stop() {
  // ฟังก์ชั่นนี้จะทำให้หุ่นยนต์หยุดเดิน
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  matrix.loadSequence(animationstop);
  matrix.play(true);
  delay(250); // เพิ่มการหน่วงเวลา
}

void loop() {
  forward();
  delay(3000);
  stop(); // เพิ่มการหยุดหลังจากเคลื่อนที่ไปข้างหน้า
  delay(250);

  backward();
  delay(3000);
  stop();
  delay(250);

  forward_left();
  delay(3000);
  stop();
  delay(250);

  backward_left();
  delay(3000);
  stop();
  delay(250);

  forward_right();
  delay(3000);
  stop();
  delay(250);

  backward_right();
  delay(3000);
  stop();
  delay(250);

  around_right();
  delay(3000);
  stop();
  delay(250);

  around_left();
  delay(3000);
  stop();
  delay(250);
}
