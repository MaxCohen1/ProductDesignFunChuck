#include <WiiChuck.h>
Accessory nunchuck1;

int lastLeftJoyX = 128;
int leftJoyX = 128;
int lastLeftJoyY = 128;
int leftJoyY = 128;
int lastRightJoyX = 128;
int rightJoyX = 128;
int lastRightJoyY = 128;
int rightJoyY = 128;

int lastXButton = 0;
int xButton = 0;
int lastYButton = 0;
int yButton = 0;
int lastAButton = 0;
int aButton = 0;
int lastBButton = 0;
int bButton = 0;

void setup() {
  Serial.begin(9600);
  nunchuck1.begin();
  nunchuck1.type = WIICLASSIC;
}

void loop() {
  nunchuck1.readData();
  checkLeftX();
  checkLeftY();
  checkRightX();
  checkRightY();
  checkXButton();
  checkYButton();
  checkAButton();
  checkBButton();
}

void checkLeftX() {
  leftJoyX = nunchuck1.values[0];
  if (leftJoyX != lastLeftJoyX) {
  }
  lastLeftJoyX = leftJoyX;
}

void checkLeftY() {
  leftJoyY = nunchuck1.values[1];
  if (leftJoyY != lastLeftJoyY) {
  }
  lastLeftJoyY = leftJoyY;
}

void checkRightX() {
  rightJoyX = nunchuck1.values[2];
  if (rightJoyX != lastRightJoyX) {
  }
  lastRightJoyX = rightJoyX;
}

void checkRightY() {
  rightJoyY = nunchuck1.values[3];
  if (rightJoyY != lastRightJoyY) {
  }
  lastRightJoyY = rightJoyY;
}

void checkXButton() {
  xButton = nunchuck1.values[8];
  if (xButton == 255 and xButton != lastXButton) {
    usbMIDI.sendNoteOn(38, 127, 1);
    delay(5);
  }
  if (xButton == 0 and xButton != lastXButton) {
    usbMIDI.sendNoteOff(38, 127, 1);
    delay(5);
  }
  lastXButton = xButton;
}

void checkYButton() {
  yButton = nunchuck1.values[9];
  if (yButton == 255 and yButton != lastYButton) {
    usbMIDI.sendNoteOn(39, 127, 1);
    delay(5);
  }
  if (yButton == 0 and yButton != lastYButton) {
    usbMIDI.sendNoteOff(39, 127, 1);
    delay(5);
  }
  lastYButton = yButton;
}

void checkAButton() {
  aButton = nunchuck1.values[12];
  if (aButton == 255 and aButton != lastAButton) {
    usbMIDI.sendNoteOn(36, 127, 1);
    delay(5);
  }
  if (aButton == 0 and aButton != lastAButton) {
    usbMIDI.sendNoteOff(36, 127, 1);
    delay(5);
  }
  lastAButton = aButton;
}

void checkBButton() {
  bButton = nunchuck1.values[13];
  if (bButton == 255 and bButton != lastBButton) {
    usbMIDI.sendNoteOn(37, 127, 1);
    delay(5);
  }
  if (bButton == 0 and bButton != lastBButton) {
    usbMIDI.sendNoteOff(37, 127, 1);
    delay(5);
  }
  lastBButton = bButton;
}



// values[0]=JoyXLeft
// values[1]=JoyYLeft
// values[2]=JoyXRight
// values[3]=JoyYRight
// values[4]=Nothing
// values[5]=Nothing
// values[6]=Broken D Pad (?)
// values[7]=Broken D Pad (?)
// values[8]=X Button
// values[9]=Y Button
// values[10]=ZL
