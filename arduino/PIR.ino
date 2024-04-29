#include <MsTimer2.h>

const int PIR = 6;
const int LED = 9;
int detect;
int time;

void setup() {
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  MsTimer2::set(5000,ISR0);
}

void loop() {
  detect = digitalRead(PIR);
  if (detect == 1) {
    Serial.println("Start");
    MsTimer2::start();
    digitalWrite(LED, 1);
    detect = 0;
  }
  else {
  }
}

void ISR0() {
  digitalWrite(LED, 0);
  Serial.println("stop");
  MsTimer2::stop();
}
