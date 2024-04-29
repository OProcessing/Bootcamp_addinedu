const int BUTTON_PIN = 2;
int n=0;
int digits [16][7]{
{1,1,1,1,1,1,0}, // digit 0
{0,1,1,0,0,0,0}, // digit 1
{1,1,0,1,1,0,1}, // digit 2
{1,1,1,1,0,0,1}, // digit 3
{0,1,1,0,0,1,1}, // digit 4
{1,0,1,1,0,1,1}, // digit 5
{1,0,1,1,1,1,1}, // digit 6
{1,1,1,0,0,0,0}, // digit 7
{1,1,1,1,1,1,1}, // digit 8
{1,1,1,1,0,1,1}, // digit 9
{1,1,1,0,1,1,1}, // hexa A
{0,0,1,1,1,1,1}, // hexa B      /////
{0,0,0,1,1,0,1}, // hexa C
{0,1,1,1,1,0,1}, // hexa D
{1,0,0,1,1,1,1}, // hexa E
{1,0,0,0,1,1,1} // hexa F
};

void displayDigit(int a);


void setup() {
  Serial.begin(9600);
  displayDigit(n);
  pinMode(BUTTON_PIN, INPUT);
  for (int i = 4; i <= 10 ; i++ ) {
    pinMode(i, OUTPUT);
  }

}

void loop() {
  if (buttonPress()) {
    n++;
    if (n > 15) {
    n = 0;
    }
    displayDigit(n);
    Serial.println(n);
  }
}


int buttonPress() {
  int press;
  int state;
  static int prev = LOW;
  state = digitalRead(BUTTON_PIN);
  press = (state == HIGH && prev == LOW);
  prev = state;
  return press;
}

void displayDigit(int a) {
  for (int i = 0; i < 7 ; i++ ) {
    if (digits[a][i]==1) digitalWrite(i+4, HIGH); else digitalWrite(i+4, LOW);
  }
}
