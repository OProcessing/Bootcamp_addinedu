const int floor_ledpin[] = { 3, 4, 5, 6 };
const int floor_btn[] = { A0, A1, A2, A3 };
const int floor_info[] = { 0, 1, 2, 3 };
char floor_requir[] = { 0, 0, 0, 0 };
const int FORWARD = 1;
const int BACKWARD = -1;
const int SPEED = 5;

int prev_btn;
int printscript = 1;

typedef struct {
  int floor;
  int present;
  int heading;
  int status;
  int destination;
  float speed;
  bool emergency;
} ELEVATOR;
ELEVATOR elevator = { 1, 100, 0, 0, 1, 0, false };

void setup() {
  Serial.begin(9600);
  for (int i = 0; i <= 3; i++) {
    pinMode(floor_btn[i], INPUT);
    pinMode(floor_ledpin[i], OUTPUT);
  }
}

void loop() {
  //*********************************************************//
  // USER INTERFACE
  if (printscript) {
    printscript = 0;
    Serial.print(" now : ");
    Serial.print(elevator.present);
    Serial.print(", floor : ");
    Serial.print(elevator.floor);
    Serial.print(", status : ");
    Serial.print(elevator.status);
    Serial.print(", head : ");
    Serial.print(elevator.heading);
    Serial.print(", speed : ");
    Serial.print(elevator.speed);
    Serial.print(", destination : ");
    Serial.println(elevator.destination);
  }
  //*********************************************************//
  // PROCESSOR

  for (int i = 0; i <= 3; i++) {
    if (digitalRead(floor_btn[i])) {
      floor_requir[i] = !floor_requir[i];
      delay(300);
    }
    digitalWrite(floor_ledpin[i], floor_requir[i]);

    if (floor_requir[i]) {
      if (!elevator.status) {  // 운행중이지 않을 경우 목적지 설정
        elevator.destination = floor_info[i];
      }
      elevator.status = 1;  // 운행상태 변경
    }
  }

  //*********************************************************//
  // ACTUATOR
  if (elevator.status) {


    // set heading
    if (!elevator.heading) {  // heading is 0
      elevator.speed = SPEED;
      if (elevator.destination > elevator.floor) {
        elevator.heading = FORWARD;
      } else if (elevator.destination < elevator.floor) {
        elevator.heading = BACKWARD;
      } else {
        elevator.status = 0;
        elevator.heading = 0;
        elevator.speed = 0;
      }
    } else {  // headint is not 0
      if (elevator.present >= 0 && elevator.present <= 300) {
        elevator.present += elevator.speed * elevator.heading;
      }
      // add destination
      for (int i = 0; i < 4; i++) {
        if (floor_requir[i]) {
          if ((elevator.destination < floor_info[i]) && (elevator.heading == FORWARD)) {
            elevator.destination = floor_info[i];
          } else if ((elevator.destination > floor_info[i]) && (elevator.heading == BACKWARD)) {
            elevator.destination = floor_info[i];
          }
        }
      }
      // stopover
      if (!(elevator.present % 100)) {
        printscript = 1;
        elevator.floor = elevator.present / 100;
        if (floor_requir[elevator.floor]) {  // stop over
          elevator.heading = 0;
          floor_requir[elevator.floor] = 0;
          Serial.print("arrived at ");
          Serial.println(floor_info[elevator.floor]);
          Serial.println();
          delay(1000);  // 임시 정류
        }
      }
    }
  } else {
    return;
  }
  delay(100);
}
