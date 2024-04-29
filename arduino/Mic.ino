const int SoundSensor = A0;
int value, MIN = 100, MAX = 50;
const int Pin[] = {8,9,10,11};
int length;
int Level(int input);
void LED(int input);
void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  length = sizeof(Pin)/sizeof(int);
}

void loop() {
  while(1) {
    value = Level(analogRead(SoundSensor));
    Serial.println(value);
    for (int i = 0; i < length ; i++) {
      if (value >= 25 * i) {
        analogWrite(Pin[i], 100);
      }
      else {
        analogWrite(Pin[i], 0);
      }
    }
    delay(500);
  }
}


int Level (int input) {
  if ( MIN > input) {
    MIN = input;
  }
  if ( MAX < input) {
    MAX = input;
  }
  int output = map(input, MIN, MAX, 0, 100);
  return output;
}
