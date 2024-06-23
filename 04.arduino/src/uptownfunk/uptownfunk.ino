#include <Servo.h>

#define first_up A0
#define first_down A1
#define second_up A3
#define second_down A2
#define third_up A5
#define third_down A4

const int UP = 1;
const int DOWN = -1;
const int SPEED = 1;
const int total_floor = 3;

const int ev_ledpin[] = { 7, 8, 9, 10, 11, 12, 13 };
const int floor_ledpin[] = { 3, 2, 5, 4, 2, 6 };

const int floor_btn[] = {
  first_up, first_down,
  second_up, second_down,
  third_up, third_down
};

int floor_request[3][6] = {
  { 0, 0, 0, 0, 0, 0 },    // floor requset
  { 1, 1, 2, 2, 3, 3 },    // called floor
  { 1,-1, 1,-1, 1,-1 }  // status
};

typedef struct {
  int floor;
  int present;
  int status;
  int destination;
  int speed;
} ELEVATOR;

ELEVATOR elevator = { 1, 100, 0, 1, 0};
Servo servo;

void LED();

void setup() {
  Serial.begin(9600);
  servo.attach(2);
  for (int i = 0; i < total_floor * 2; i++) {
    pinMode(floor_btn[i], INPUT);
    pinMode(floor_ledpin[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {
    pinMode(ev_ledpin[i], OUTPUT);
  }
}

void loop() {
  //*********************************************************//
  // USER INTERFACE
  LED();
  Serial.print(" now : ");
  Serial.print(elevator.present);
  Serial.print(", floor : ");
  Serial.print(elevator.floor);
  Serial.print(", status : ");
  Serial.print(elevator.status);
  Serial.print(", speed : ");
  Serial.print(elevator.speed);
  Serial.print(", destination : ");
  Serial.println(elevator.destination);

  //*********************************************************//
  // PROCESSOR

  for (int i = 0; i < total_floor * 2; i++) {  
    // request btn toggle
    if (digitalRead(floor_btn[i])) {
      floor_request[0][i] = !floor_request[0][i];
      delay(200);
    }
    digitalWrite(floor_ledpin[i], floor_request[0][i]);
  }

  //*********************************************************//
  // ELEVATOR

  if (!elevator.status) {  // if it hasn't destination, set destination
    for (int i = 0; i < total_floor * 2; i++) {
      if (floor_request[0][i]) {
        elevator.destination = floor_request[1][i];
        elevator.speed = SPEED;
        if (elevator.destination > elevator.floor) {
          elevator.status = UP;
        } else if (elevator.destination < elevator.floor) {
          elevator.status = DOWN;
        } else {
          floor_request[0][i] = 0;  //reset request
          return;
        }
      }
    }
  }
  // EV in working phase
  else if (elevator.status) {
    // path_planning
    for (int i = 0; i < total_floor * 2; i++) {
      // destination update
      if ((elevator.status == UP) && (floor_request[0][i]) && (elevator.destination < floor_request[1][i])) {
        elevator.destination = floor_request[1][i];
      } else if ((elevator.status == DOWN) && (floor_request[0][i]) && (elevator.destination > floor_request[1][i])) {
        elevator.destination = floor_request[1][i];
      }
    }

    // Ev on the floor
    if (!(elevator.present % 100)) {
      elevator.floor = elevator.present / 100;
      int tmp = (elevator.floor - 1) * 2;
      if (elevator.status == DOWN) {
        tmp++;
      }
      if (floor_request[0][tmp] && (elevator.floor = floor_request[1][tmp])) {
        floor_request[0][tmp] = 0;
        if (elevator.destination == elevator.floor) {
          elevator.status = 0;
          elevator.speed = 0;
        }
        delay(100);
      }
    }

    if (elevator.floor != elevator.destination) {
      elevator.present += elevator.status * elevator.speed;
    } else {
      elevator.status = 0;
      elevator.speed = 0;
    }
  }
  delay(100);
}

void LED() {
  int tmp = elevator.present;
  for (int i = 0; i < 7; i++) {
    if (tmp > 33*(3+i)-25 && tmp < 33*(3+i)+25) digitalWrite(7 + i, 1);
    else digitalWrite(7 + i, 0);
  }
  int sv = map(elevator.present, 100, 300, 0, 180);
  servo.write(sv);
}
