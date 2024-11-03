#include <Servo.h>

#define x_pin A0
#define y_pin A1
#define sw_pin 3

#define ServoX_Pin 10
#define ServoY_Pin 9

Servo servo_x;
Servo servo_y;

int pos_x = 180; // เริ่มต้นที่ค่ากลาง (90 องศา)
int pos_y = 180; // เริ่มต้นที่ค่ากลาง (90 องศา)

void setup() {
  pinMode(x_pin, INPUT);
  pinMode(y_pin, INPUT);
  pinMode(sw_pin, INPUT);

  servo_x.attach(ServoX_Pin);
  servo_y.attach(ServoY_Pin);

  delay(1000);
}

void loop() {
  int x_data = analogRead(x_pin);
  int y_data = analogRead(y_pin);
  int sw_state = digitalRead(sw_pin); // กำหนดตัวแปรใหม่แทน `sw_pin` เพื่อไม่ให้ซ้ำกับพินที่ประกาศด้านบน

  pos_x = map(x_data, 0, 1023, 0, 180);
  pos_y = map(y_data, 0, 1023, 0, 180); // แก้ให้ใช้ `y_data` แทน `x_data` สำหรับการควบคุมเซอร์โวแกน Y

  servo_x.write(pos_x);
  servo_y.write(pos_y);

  delay(40);
}
