#include "Arduino_LED_Matrix.h"
#include "animation.h"

ArduinoLEDMatrix matrix;  // Declare the matrix object

void setup() {
  Serial.begin(115200);
  matrix.loadSequence(animation);  // Load the animation sequence
  matrix.begin();  // Initialize the LED matrix
  matrix.play(true);  // Start playing the animation in a loop
}

void loop() {
  delay(500);
  Serial.println(millis());  // Print the millis to serial monitor
}
