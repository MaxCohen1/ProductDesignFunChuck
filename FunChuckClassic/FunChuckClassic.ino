#include <WiiChuck.h>
Accessory classic1;

int joyLeftXValClassic = 0;
int joyLeftYValClassic = 0;
int joyRightXValClassic = 0;
int joyRightYValClassic = 0;
bool directionSwitchClassic = true;
int homeButtonValClassic = 0;
int lastHomeButtonValClassic = 0;

int lastXButtonClassic = 0;
int xButtonClassic = 0;
int lastYButtonClassic = 0;
int yButtonClassic = 0;
int lastAButtonClassic = 0;
int aButtonClassic = 0;
int lastBButtonClassic = 0;
int bButtonClassic = 0;

int lastLButtonClassic = 0;
int lButtonClassic = 0;
int lastZlButtonClassic = 0;
int zlButtonClassic = 0;
int lastRButtonClassic = 0;
int rButtonClassic = 0;
int lastZrButtonClassic = 0;
int zrButtonClassic = 0;

void setup() {
  Serial.begin(9600);
  classic1.begin();
  classic1.type = WIICLASSIC;
}

void loop() {
  classic1.readData();
  checkButtonClassic(8, xButtonClassic, lastXButtonClassic, 38);
  checkButtonClassic(9, yButtonClassic, lastYButtonClassic, 39);
  checkButtonClassic(12, aButtonClassic, lastAButtonClassic, 36);
  checkButtonClassic(13, bButtonClassic, lastBButtonClassic, 37);
  checkButtonClassic(11, lButtonClassic, lastLButtonClassic, 40);
  checkButtonClassic(17, rButtonClassic, lastRButtonClassic, 43);
  checkButtonClassic(10, zlButtonClassic, lastZlButtonClassic, 41);
  checkButtonClassic(18, zrButtonClassic, lastZrButtonClassic, 42);
  checkHomeButtonClassic();
  checkMinusPlusClassic();
  joyEffectsClassic();
}

void checkButtonClassic(int buttonNum, int &buttonVal, int &lastButtonVal, int note) {
  buttonVal = classic1.values[buttonNum];
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

void checkHomeButtonClassic() {
  homeButtonValClassic = classic1.values[15];
  if (homeButtonValClassic == 255 and lastHomeButtonValClassic != homeButtonValClassic) {
    directionSwitchClassic = ! directionSwitchClassic;
  }
  lastHomeButtonValClassic = homeButtonValClassic;
}

void checkMinusPlusClassic() {
  if (classic1.values[14] == 0) {
    if (directionSwitchClassic == true) {
      usbMIDI.sendControlChange(1, joyLeftXValClassic, 0);
    } else {
      usbMIDI.sendControlChange(2, joyLeftYValClassic, 0);
    }
  }
  if (classic1.values[14] == 255) {
    if (directionSwitchClassic == true) {
      usbMIDI.sendControlChange(3, joyRightXValClassic, 0);
    } else {
      usbMIDI.sendControlChange(4, joyRightYValClassic, 0);
    }
  }
}

void joyEffectsClassic() {
  if (classic1.values[0] >= 132 or classic1.values[0] <= 124 or classic1.values[1] >= 132 or classic1.values[1] <= 124 or classic1.values[2] >= 132 or classic1.values[2] <= 124 or classic1.values[3] >= 132 or classic1.values[3] <= 124) {
    if (classic1.values[0] >= 132 or classic1.values[0] <= 124) {
      joyLeftXValClassic = joyLeftXValClassic + map(classic1.values[0], 0, 256, -15, 15);
      if (joyLeftXValClassic > 127) {
        joyLeftXValClassic = 127;
      }
      if (joyLeftXValClassic < 0) {
        joyLeftXValClassic = 0;
      }
      usbMIDI.sendControlChange(1, joyLeftXValClassic, 0);
    }

    if (classic1.values[1] >= 132 or classic1.values[1] <= 124) {
      joyLeftYValClassic = joyLeftYValClassic + map(classic1.values[1], 0, 256, -15, 15);
      if (joyLeftYValClassic > 127) {
        joyLeftYValClassic = 127;
      }
      if (joyLeftYValClassic < 0) {
        joyLeftYValClassic = 0;
      }
      usbMIDI.sendControlChange(2, joyLeftYValClassic, 0);
    }

    if (classic1.values[2] >= 132 or classic1.values[2] <= 124) {
      joyRightXValClassic = joyRightXValClassic + map(classic1.values[2], 0, 256, -15, 15);
      if (joyRightXValClassic > 127) {
        joyRightXValClassic = 127;
      }
      if (joyRightXValClassic < 0) {
        joyRightXValClassic = 0;
      }
      usbMIDI.sendControlChange(3, joyRightXValClassic, 0);
    }

    if (classic1.values[3] >= 132 or classic1.values[3] <= 124) {
      joyRightYValClassic = joyRightYValClassic + map(classic1.values[3], 0, 256, -15, 15);
      if (joyRightYValClassic > 127) {
        joyRightYValClassic = 127;
      }
      if (joyRightYValClassic < 0) {
        joyRightYValClassic = 0;
      }
      usbMIDI.sendControlChange(4, joyRightYValClassic, 0);
    }
    delay(25);
  }
}
