#include<Servo.h>

#define x_pin A0
#define y_pin A1
#define sw_pin 3

#define ServoX_Pin 10
#define ServoY_Pin 9

Servo servo_x;
Servo servo_y;

int pos_x = 180;
int pos_y = 180;

void setup() {
  pinMode(x_pin, INPUT);
  pinMode(y_pin, INPUT);
  pinMode(sw_pin, INPUT);

  pinMode(ServoX_Pin, OUTPUT);
  pinMode(ServoY_Pin, OUTPUT);

  servo_x.attach(ServoX_Pin);
  servo_x.attach(pos_x);
  servo_y.attach(ServoY_Pin);
  servo_x.attach(pos_y)

  delay(1000);
}

void loop() {
  int x_data = analogRead(x_pin);
  int y_data = analogRead(y_pin);
  int sw_pin = digitalRead(sw_pin);

  pos_x = map(x_data,0,1023,0,180);
  pos_y = map(x_data,0,1023,0,180);

  servo_x.write(pos_x);
  servo_y.write(pos_y);

  delay(40);

}
