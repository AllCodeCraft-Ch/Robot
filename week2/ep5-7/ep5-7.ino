#include "Arduino_LED_Matrix.h"   
#include "animation.h"            
ArduinoLEDMatrix matrix; 
void setup() {
  pinMode(3, OUTPUT);
  matrix.loadSequence(animation);
  matrix.begin();
  matrix.play(true);
}

void loop() {
  int d_time = 1000;
  digitalWrite(3, 1);
  delay(d_time);
  digitalWrite(3, 0);
  delay(d_time);

}
