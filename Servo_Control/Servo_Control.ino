#include <ESP32Servo.h>
Servo servo;
const byte gpio = 5;
void setup() {
  servo.attach(gpio);
  servo.write(0);
  delay(2000);
}

void loop() {
  servo.write(90);
  delay(1000);
  servo.write(70);
  delay(1000);
}
