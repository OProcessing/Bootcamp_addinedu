#include <MsTimer2.h>

const int PIR = 2;
const int LED = 9;
int detect;
int sec=0, flag;

void setup() {
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  detect = digitalRead(PIR);
  if (detect == 1) {
    digitalWrite(LED, 1);
    sec = 1 * 1 * 100;
    flag = 1;
  }
  else {
    //
  }

  if (sec > 0) {
    Serial.println(sec);
    sec--;
  }
  else {
    digitalWrite(LED, 0);
    if (flag == 1) {
      Serial.println("stop");
    }
    flag = 0;
  }

  delay(10);
}
