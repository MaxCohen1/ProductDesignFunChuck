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
  checkXButton();
  checkYButton();
  checkAButton();
  checkBButton();
  checkLButton();
  checkRButton();
  checkZrButton();
  checkZlButton();
  checkHomeButton();
  checkMinusPlus();
  joyEffects();
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

void joyLeftXEffect() {
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
}

void joyLeftYEffect() {
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
}

void joyEffects() {
  if (nunchuck1.values[0] >= 132 or nunchuck1.values[0] <= 124 or nunchuck1.values[1] >= 132 or nunchuck1.values[1] <= 124 or nunchuck1.values[2] >= 132 or nunchuck1.values[2] <= 124 or nunchuck1.values[3] >= 132 or nunchuck1.values[3] <= 124) {
    if (nunchuck1.values[0] >= 132 or nunchuck1.values[0] <= 124) {
      joyLeftXVal = joyLeftXVal + map(nunchuck1.values[0], 0, 256, -15, 15);
      if (joyLeftXVal > 127) {
        joyLeftXVal = 127;
      }
      if (joyLeftXVal < 0) {
        joyLeftXVal = 0;
      }
      usbMIDI.sendControlChange(1, joyLeftXVal, 0);
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
    }

    delay(25);
  }
}
