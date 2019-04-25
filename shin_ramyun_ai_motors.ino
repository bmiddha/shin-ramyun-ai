#include <AccelStepper.h>
#define HALFSTEP 4

#define NUM_COLUMNS 7
#define NUM_DISPENSERS 2
#define MAX_SPEED 10000
#define ACCELARATION 300
#define SPEED 300

AccelStepper column1(HALFSTEP, 22, 24, 23, 25);
AccelStepper column2(HALFSTEP, 26, 28, 27, 29);
AccelStepper column3(HALFSTEP, 30, 32, 31, 33);
AccelStepper column4(HALFSTEP, 34, 36, 35, 37);
AccelStepper column5(HALFSTEP, 38, 40, 39, 41);
AccelStepper column6(HALFSTEP, 42, 44, 42, 45);
AccelStepper column7(HALFSTEP, 46, 48, 47, 49);
AccelStepper dispenser1(HALFSTEP, 2, 4, 3, 5);
AccelStepper dispenser2(HALFSTEP, 8, 10, 9, 11);

AccelStepper *columns[NUM_COLUMNS] = {
  &column1,
  &column2,
  &column3,
  &column4,
  &column5,
  &column6,
  &column7
};

AccelStepper *dispensers[NUM_DISPENSERS] = {
  &dispenser1,
  &dispenser2
};


void initSteppers() {
  for (byte col = 0; col < NUM_COLUMNS; col++) {
    columns[col]->setSpeed(SPEED);
    columns[col]->setMaxSpeed(MAX_SPEED);
    columns[col]->setAcceleration(ACCELARATION);
  }
  for (byte disp = 0; disp < NUM_DISPENSERS; disp++) {
    dispensers[disp]->setSpeed(SPEED);
    dispensers[disp]->setMaxSpeed(MAX_SPEED);
    dispensers[disp]->setAcceleration(ACCELARATION);
  }
}

void openColumn(AccelStepper *s, char disp) {
  s->move(512);
  s->runToPosition();
  if (disp >= 'x' && disp <= 'y') openDispenser(dispensers[(int)(disp - 'x')]);
  delay(7000);
  s->move(-512);
  s->runToPosition();
  Serial.println("Z");
}

void openDispenser(AccelStepper *s) {
  s->move(512);
  s->runToPosition();
}

void setup() {
  Serial.begin(115200);
  initSteppers();
}

void loop() {
  while (!Serial.available()) {}
  String input;
  input = Serial.readString();
  char col = input[0];
  char disp = input[2];
  if (col >= 'a' && col <= 'g') openColumn(columns[col - 'a'], disp);

}
