#include "Arduino_LED_Matrix.h"
#include "animation_go.h"
#include "animation_back.h"
#include "animation_L.h"
#include "animationloopL.h"
#include "animation_R.h"
#include "animationloopR.h"
#include "animationstop.h"

// มอเตอร์ซ้าย
int ENA = 10;
int IN1 = 9;
int IN2 = 8;
// มอเตอร์ขวา
int ENB = 5;
int IN3 = 7;
int IN4 = 6;
// กำหนดค่าให้กับ Joystick Module
int joyX = A0;
int joyY = A1;
int joyB = 4;
// ตัวแปรเก็บค่าความเร็วกำหนดค่าเริ่มต้นของความเร็วให้อยู่ที่ 0
int MotorSpeed_L = 0;
int MotorSpeed_R = 0;
// กำหนดค่าดีฟอลต์ให้กับจอยสติ้กที่จุดกึ่งกลางที่ 512
int joy_pos_Y = 512;
int joy_pos_X = 512;
bool joy_button = 0;
// ใช้ชดเชยการเบี้ยวของการเคลื่อนที่
int B_L = 0; // ล้อซ้าย
int B_R = 0; // ล้อขวา
// ย่านต้องห้าม
int L_POINT = 29491;
int H_POINT = 36045;
int E_RES = 65535;

ArduinoLEDMatrix matrix;

void setup() {
  // กำหนดให้ขาต่าง ๆ เป็นอินพุตและเอาต์พุต
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(joyY, INPUT);
  pinMode(joyX, INPUT);
  pinMode(joyB, INPUT);
  // กำหนดค่าเริ่มต้นให้กับมอเตอร์ทั้งด้านซ้ายและด้านขวา (เป็นค่าดีฟอลต์) ให้เป็น 0 ทั้งหมด
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  // เปลี่ยนความละเอียดของ PWM จาก 0 - 255 เป็น 0 - 4095
  analogWriteResolution(12);
  analogReadResolution(16);

  // เริ่มต้น LED matrix
  matrix.begin();
}

void loop() {
  // อ่านค่าจากจอยสติ้กจาก A0,A1 และ สวิตซ์
  joy_pos_Y = analogRead(joyY);
  joy_pos_X = analogRead(joyX);
  joy_button = digitalRead(joyB);

  // เดินหน้า
  if (joy_pos_Y > H_POINT) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    MotorSpeed_L = map(joy_pos_Y, H_POINT, E_RES, 2050, 4095);
    MotorSpeed_R = map(joy_pos_Y, H_POINT, E_RES, 2050, 4095);
    matrix.loadSequence(animation_go);
    matrix.play(true);
  }
  // ถอยหลัง
  else if (joy_pos_Y < L_POINT) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    joy_pos_Y = (joy_pos_Y - L_POINT) * (-1);
    MotorSpeed_L = map(joy_pos_Y, 0, L_POINT, 2050, 4095);
    MotorSpeed_R = map(joy_pos_Y, 0, L_POINT, 2050, 4095);
    matrix.loadSequence(animation_back);
    matrix.play(true);
  }
  else {
    MotorSpeed_L = 0;
    MotorSpeed_R = 0;
    matrix.loadSequence(animationstop);
    matrix.play(true);
  }

  // เลี้ยวซ้าย
  if (joy_pos_X < L_POINT && joy_button == 1) {
    joy_pos_X = (joy_pos_X - L_POINT) * (-1);
    joy_pos_X = map(joy_pos_X, 0, L_POINT, 0, 4095);
    MotorSpeed_L = MotorSpeed_L + joy_pos_X;
    MotorSpeed_R = MotorSpeed_R - joy_pos_X;
    if (MotorSpeed_L < 0) MotorSpeed_L = 0;
    if (MotorSpeed_R > 4095) MotorSpeed_R = 4095;
    matrix.loadSequence(animation_L);
    matrix.play(true);
  }
  // เลี้ยวขวา
  else if (joy_pos_X > H_POINT && joy_button == 1) {
    joy_pos_X = map(joy_pos_X, H_POINT, E_RES, 0, 4095);
    MotorSpeed_L = MotorSpeed_L - joy_pos_X;
    MotorSpeed_R = MotorSpeed_R + joy_pos_X;
    if (MotorSpeed_L > 4095) MotorSpeed_L = 4095;
    if (MotorSpeed_R < 0) MotorSpeed_R = 0;
    matrix.loadSequence(animation_R);
    matrix.play(true);
  }
  // หมุนซ้าย
  else if (joy_pos_X < L_POINT && joy_button == 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    joy_pos_X = (joy_pos_X - L_POINT) * (-1);
    joy_pos_X = map(joy_pos_X, 0, L_POINT, 2050, 4095);
    MotorSpeed_L = joy_pos_X;
    MotorSpeed_R = joy_pos_X;
    if (MotorSpeed_L > 4095) {
      MotorSpeed_L = 4095;
    }
    if (MotorSpeed_R > 4095) {
      MotorSpeed_R = 4095;
    }
    matrix.loadSequence(animationloopL);
    matrix.play(true);
  }
  // หมุนขวา
  else if (joy_pos_X > H_POINT && joy_button == 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    joy_pos_X = map(joy_pos_X, H_POINT, E_RES, 2050, 4095);
    MotorSpeed_L = joy_pos_X;
    MotorSpeed_R = joy_pos_X;
    if (MotorSpeed_L > 4095) {
      MotorSpeed_L = 4095;
    }
    if (MotorSpeed_R > 4095) {
      MotorSpeed_R = 4095;
    }
    matrix.loadSequence(animationloopR);
    matrix.play(true);
  }

  // ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050
  if (MotorSpeed_L < 2050) {
    MotorSpeed_L = 0;
  }
  if (MotorSpeed_R < 2050) {
    MotorSpeed_R = 0;
  }

  // คำสั่งขับมอเตอร์ทั้งซ้ายและขวา
  analogWrite(ENA, MotorSpeed_L - B_L);
  analogWrite(ENB, MotorSpeed_R - B_R);
}
