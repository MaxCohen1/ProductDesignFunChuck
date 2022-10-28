#include <WiiChuck.h>
Accessory nunchuck1;

int joyLeftXVal = 0;
int joyLeftYVal = 0;
int joyRightXVal = 0;
int joyRightYVal = 0;
bool directionSwitch = true;
int homeButtonVal = 0;
int lastHomeButtonVal = 0;
int joyAdd = 0;

int lastXButton = 0;
int xButton = 0;
int lastYButton = 0;
int yButton = 0;
int lastAButton = 0;
int aButton = 0;
int lastBButton = 0;
int bButton = 0;

int lastLButton = 0;
int lButton = 0;
int lastZlButton = 0;
int zlButton = 0;
int lastRButton = 0;
int rButton = 0;
int lastZrButton = 0;
int zrButton = 0;

int rollButtonPin = 33;
int pitchButtonPin = 34;
int switchPin = 37;

void setup() {
  Serial.begin(9600);
  pinMode(rollButtonPin, INPUT);
  pinMode(pitchButtonPin, INPUT);
  pinMode(switchPin, INPUT);
  nunchuck1.begin();
  nunchuck1.type = WIICLASSIC;
}

void loop() {
  nunchuck1.readData();
  checkButton(8, xButton, lastXButton, 38);
  checkButton(9, yButton, lastYButton, 39);
  checkButton(12, aButton, lastAButton, 36);
  checkButton(13, bButton, lastBButton, 37);
  checkButton(11, lButton, lastLButton, 40);
  checkButton(17, rButton, lastRButton, 43);
  checkButton(10, zlButton, lastZlButton, 41);
  checkButton(18, zrButton, lastZrButton, 42);
  checkHomeButton();
  checkMinusPlus();
  joyEffects();
}

void checkButton(int buttonNum, int &buttonVal, int &lastButtonVal, int note) {
  buttonVal = nunchuck1.values[buttonNum];
  if (buttonVal == 255 and buttonVal != lastButtonVal) {
    usbMIDI.sendNoteOn(note, 127, 1);
    delay(5);
  }
  if (buttonVal == 0 and buttonVal != lastButtonVal) {
    usbMIDI.sendNoteOff(note, 127, 1);
    delay(5);
  }
  lastButtonVal = buttonVal;
}

void checkHomeButton() {
  homeButtonVal = nunchuck1.values[15];
  if (homeButtonVal == 255 and lastHomeButtonVal != homeButtonVal) {
    directionSwitch = ! directionSwitch;
  }
  lastHomeButtonVal = homeButtonVal;
}

void checkMinusPlus() {
  if (nunchuck1.values[14] == 0) {
    if (directionSwitch == true) {
      usbMIDI.sendControlChange(1, joyLeftXVal, 0);
    } else {
      usbMIDI.sendControlChange(2, joyLeftYVal, 0);
    }
  }
  if (nunchuck1.values[14] == 255) {
    if (directionSwitch == true) {
      usbMIDI.sendControlChange(3, joyRightXVal, 0);
    } else {
      usbMIDI.sendControlChange(4, joyRightYVal, 0);
    }
  }
}

void joyEffects() {
  if (nunchuck1.values[0] >= 132 or nunchuck1.values[0] <= 124) {
    joyLeftXVal = joyLeftXVal + map(nunchuck1.values[0], 0, 256, -15, 15);
    if (joyLeftXVal > 127) {
      joyLeftXVal = 127;
    }
    if (joyLeftXVal < 0) {
      joyLeftXVal = 0;
    }
    usbMIDI.sendControlChange(1, joyLeftXVal, 0);
    delay(25);
  }

  if (nunchuck1.values[1] >= 132 or nunchuck1.values[1] <= 124) {
    joyLeftYVal = joyLeftYVal + map(nunchuck1.values[1], 0, 256, -15, 15);
    if (joyLeftYVal > 127) {
      joyLeftYVal = 127;
    }
    if (joyLeftYVal < 0) {
      joyLeftYVal = 0;
    }
    usbMIDI.sendControlChange(2, joyLeftYVal, 0);
    delay(25);
  }

  if (nunchuck1.values[2] >= 132 or nunchuck1.values[2] <= 124) {
    joyRightXVal = joyRightXVal + map(nunchuck1.values[2], 0, 256, -15, 15);
    if (joyRightXVal > 127) {
      joyRightXVal = 127;
    }
    if (joyRightXVal < 0) {
      joyRightXVal = 0;
    }
    usbMIDI.sendControlChange(3, joyRightXVal, 0);
    delay(25);
  }

  if (nunchuck1.values[3] >= 132 or nunchuck1.values[3] <= 124) {
    joyRightYVal = joyRightYVal + map(nunchuck1.values[3], 0, 256, -15, 15);
    if (joyRightYVal > 127) {
      joyRightYVal = 127;
    }
    if (joyRightYVal < 0) {
      joyRightYVal = 0;
    }
    usbMIDI.sendControlChange(4, joyRightYVal, 0);
    delay(25);
  }
}
