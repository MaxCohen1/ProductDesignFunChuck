#include <WiiChuck.h>
Accessory nunchuck1;

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
  checkXButton();
  checkYButton();
  checkAButton();
  checkBButton();
  checkLButton();
  checkRButton();
  checkZrButton();
  checkZlButton();
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

void checkLButton() {
  lButton = nunchuck1.values[11];
  if (lButton > 0 and lastLButton == 0) {
    usbMIDI.sendNoteOn(40, 127, 1);
    delay(5);
  }
  if (lButton == 0 and lButton != lastLButton) {
    usbMIDI.sendNoteOff(40, 127, 1);
    delay(5);
  }
  lastLButton = lButton;
}

void checkRButton() {
  rButton = nunchuck1.values[17];
  if (rButton > 0 and lastRButton == 0) {
    usbMIDI.sendNoteOn(43, 127, 1);
    delay(5);
  }
  if (rButton == 0 and rButton != lastRButton) {
    usbMIDI.sendNoteOff(43, 127, 1);
    delay(5);
  }
  lastRButton = rButton;
}

void checkZlButton() {
  zlButton = nunchuck1.values[10];
  if (zlButton == 255 and zlButton != lastZlButton) {
    usbMIDI.sendNoteOn(41, 127, 1);
    delay(5);
  }
  if (zlButton == 0 and zlButton != lastZlButton) {
    usbMIDI.sendNoteOff(41, 127, 1);
    delay(5);
  }
  lastZlButton = zlButton;
}

void checkZrButton() {
  zrButton = nunchuck1.values[18];
  if (zrButton == 255 and zrButton != lastZrButton) {
    usbMIDI.sendNoteOn(42, 127, 1);
    delay(5);
  }
  if (zrButton == 0 and zrButton != lastZrButton) {
    usbMIDI.sendNoteOff(42, 127, 1);
    delay(5);
  }
  lastZrButton = zrButton;
}

//Use - and + to set effects on joysticks, home switches between x and y

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
