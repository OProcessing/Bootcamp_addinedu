#include <Servo.h>
int motor_work;
int speed_up, speed_down;
bool work_flag;
int forehead = 1, value = 0, speed = 1;
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
}

void loop() {

  if (digitalRead(2) == HIGH) {
    work_flag = 1;
  }
  if (digitalRead(3) == HIGH) {
    speed ++;
    delay(20);
  }
  if (digitalRead(4) == HIGH) {
    speed --;
    delay(20);
  }


  

  if (work_flag == 1) {
    value += speed * 0.125 * forehead;
    work_flag = 0;
    value = 180;
    if (value >= 180) {
    forehead = -1;
    value = 0;
    }
    if (value <= 0) {
      forehead = 1;
    }
    Serial.println(value);
    servo.write(value);
    delay(20);
  }
}