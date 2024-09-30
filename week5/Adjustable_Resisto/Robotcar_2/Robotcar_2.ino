//มอเตอร์ซ้าย
int ENA=10;
int IN1=9;
int IN2=8;
//มอเตอร์ขวา
int ENB=5;
int IN3=7;
int IN4=6;
// ตัวแปรที่ใช้กับค่าความเร็วของตัวต้านทานปรับค่าได้ทั้ง 2 ตัวตังแต่ 0 ถึง 4095
int analogIP_L = A0;
int analogIP_R = A1;
// ตัวแปรเก็บค่าความเร็วกำหนดค่าเริ่มต้นของความเร็วให้อยู่ที่ 0
int MotorSpeed_L = 0;
int MotorSpeed_R = 0;
//ใช้ชดเชยการเบี้ยวของการเคลื่อนที่
int B_L = 0; //ล้อซ้าย
int B_R = 0; //ล้อขวา

void setup() {
  //กำหนดให้ขาต่าง ๆ เป็นอินพุตและเอาต์พุต
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
  //เปลี่ยนความละเอียดของ PWM จาก 0 - 255 เป็น 0 - 4095
  analogWriteResolution(12);
}

void loop() {
  //กำหนดให้พารามิเตอร์ที่ L298N เดินหน้า
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  //อ่านค่าจากตัวต้านทานปรับค่าได้ทั้งสองข้างทั้ง A0 และ A1 เอามาเก็บไว้ในตัวแปร
  MotorSpeed_L = analogRead(analogIP_L);
  MotorSpeed_R = analogRead(analogIP_R);
  //ทำการแม็พค่าที่ได้รับที่ A0 และ A1 จาก 0 - 1023 ไปเป็น 0 - 4095
  MotorSpeed_L = map(MotorSpeed_L, 0, 1023, 0, 4095);
  MotorSpeed_R = map(MotorSpeed_R, 0, 1023, 0, 4095);
  // เขียนโปรแกรมป้องกันค่ามอเตอร์อยู่ในความเร็วที่ทำให้มอเตอร์เสียหาย โดยปกติแล้วจะอยู่ในช่วง 0 ถึง 2050
  if (MotorSpeed_L < 2050){
    MotorSpeed_L = 0;
  }
  if (MotorSpeed_R < 2050){
    MotorSpeed_R = 0;
  }
  // ส่งค่าความเร็วไปยังขา ENA และ ENB
  analogWrite(ENA, MotorSpeed_L -B_L);
  analogWrite(ENB, MotorSpeed_R -B_R);
  Serial.print("PWM ของล้อซ้าย");
  Serial.println(MotorSpeed_L);
  Serial.print("PWM ของล้อขวา");
  Serial.println(MotorSpeed_R);
}
