int ENA = 10;
int IN1 = 9;
int IN2 = 8;
int ENB = 5;
int IN3 = 7;
int IN4 = 6;

void setup() {
  // ตั้งค่าพินมอเตอร์เป็น output
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // เดินตรงไปข้างหน้า 5 ซม.
  moveForward();
  delay(900);  // ปรับระยะเวลาเพื่อให้ได้ 5 ซม.
  stopMotor();

  // หยุด
  delay(1000);

  // เลี้ยวซ้าย 90 องศา
  turnLeft();
  delay(600);  // ปรับระยะเวลาเพื่อให้ได้การเลี้ยว 90 องศา
  stopMotor();

  // หยุด
  delay(1000);

  // เดินตรงไปข้างหน้า 2 เมตร
  moveForward();
  delay(3000);  // ปรับระยะเวลาเพื่อให้ได้ 2 เมตร
  stopMotor();

  // หยุด
  delay(1000);

  // เลี้ยวซ้าย 90 องศา
  turnLeft();
  delay(600);
  stopMotor();

  // หยุด
  delay(1000);

  // เดินตรงไปข้างหน้า 4 เมตร
  moveForward();
  delay(4400);  // ปรับระยะเวลาเพื่อให้ได้ 4 เมตร
  stopMotor();

  // หยุด
  delay(1000);

  turn();
  delay(1000);

  moveForward();
  delay(2000);

  // จบ loop
  while (true);
}

// ฟังก์ชันสำหรับเดินหน้า
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255); // ความเร็วของมอเตอร์ด้านซ้าย
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 255); // ความเร็วของมอเตอร์ด้านขวา
}

// ฟังก์ชันสำหรับเลี้ยวซ้าย
void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255); // ความเร็วของมอเตอร์ด้านซ้ายหมุนถอยหลัง
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 255); // มอเตอร์ด้านขวาหมุนเดินหน้า
}

void turn() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255); // ความเร็วของมอเตอร์ด้านซ้ายหมุนถอยหลัง
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 255); // มอเตอร์ด้านขวาหมุนเดินหน้า
}

// ฟังก์ชันสำหรับหยุดมอเตอร์
void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}