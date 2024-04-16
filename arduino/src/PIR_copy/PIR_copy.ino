#include <MsTimer2.h>

const int PIR = 2;
const int LED = 9;
int detect;
int time;

void setup() {
  Serial.begin(9600);
  pinMode(PIR, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIR), ISR1, CHANGE);
  MsTimer2::set(5000,ISR0);
}

void loop() {

}

void ISR0() {
  digitalWrite(LED, LOW);
  Serial.println("stop");
  MsTimer2::stop();
}
void ISR1() {
  digitalWrite(LED, HIGH);
  Serial.println("start");
  MsTimer2::start();
}
