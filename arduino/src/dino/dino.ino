#include <Servo.h>
int MAX = 0;
int light;
int dummy;

Servo servo;
int photo();

void setup() {
  Serial.begin(9600);
  servo.attach(9);
}

void loop() {
  while (1) {
    dummy = photo();
    if (dummy < 50) {
      servo.write(150);
      delay(50);
      servo.write(90);
      delay(300);
    }
  }
}


int photo() {
  if (MAX < light) {
    MAX = light;
  }
  light = analogRead(A0);
  int out = map(light, 0, MAX, 0, 100);
  return out;
}