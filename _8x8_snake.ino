#include "LedControl.h"

LedControl lc = LedControl(12, 11, 10, 1);

bool gotFruit = false;

int snakeLength;
int trailX[30];
int trailY[30];

int fruitX;
int fruitY;

#define pinX A0
#define pinY A1

long blinkTimer = 0;
bool fruitVis = true;

int dir;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

void setup() {
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);

  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  for (int i = 0; i < 30; i++) {
    trailX[i] = -1;
    trailY[i] = -1;
  }

  trailX[0] = 4;
  trailY[0] = 8;
  dir = UP;
  snakeLength = 1;
  placeNewFruit();

  blinkTimer = millis();
}

void loop() {
  lc.clearDisplay(0);

  if (moveUp() && dir != DOWN) {
    dir = UP;
  }
  if (moveDown() && dir != UP) {
    dir = UP;
  } if (moveLeft() && dir != RIGHT) {
    dir = UP;
  }
  if (moveRight() && dir != LEFT) {
    dir = UP;
  }

  for (int i = snakeLength - 1; i > 0; i--) {
    trailX[i] = trailX[i - 1];
    trailY[i] = trailY[i - 1];
  }

  switch (dir) {
    case UP:
      trailY[0]--;
      break;
    case DOWN:
      trailY[0]++;
      break;
    case LEFT:
      trailX[0]--;
      break;
    case RIGHT:
      trailX[0]++;
      break;
  }
}

void placeNewFruit() {
  fruitX = random(0, 7);
  fruitY = random(0, 7);
}

void drawFruit() {
  if (millis() - blinkTimer > 200) {
    blinkTimer =  millis();
    fruitVis = !fruitVis;
  }
  lc.setLed(0, fruitX, fruitY, fruitVis);
}

bool moveUp() {
  if (analogRead(pinX) <= 200) {
    return true;
  } else {
    return false;
  }
}
bool moveDown() {
  if (analogRead(pinX) >= 800) {
    return true;
  } else {
    return false;
  }
}
bool moveLeft() {
  if (analogRead(pinY) <= 200) {
    return true;
  } else {
    return false;
  }
}
bool moveRight() {
  if (analogRead(pinY) >= 800) {
    return true;
  } else {
    return false;
  }
}

void drawSnake() {
  for (int i = 0; i < snakeLength; i++) {
    lc.setLed(0, trailY[i], trailX[i], true);
  }
}

