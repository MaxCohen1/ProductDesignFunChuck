#include <WiiChuck.h>
Accessory nunchuck1;
Accessory classic1;
Accessory guitar1;

int modeButton = 35;
int button1 = 34; //roll
int button2 = 33; //pitch
int switchPin = 37;

int lastModeState = 0;

int currentMode = 0;

//nunchuck values------------------------------------------------------------------------------------------------------//
bool zStateNun = HIGH;
bool lastZStateNun = HIGH;
int currentNoteNun = 60;
int lastNoteNun = 60;

int yJoyValNun = 127;
int lastYJoyValNun = 127;
int xJoyValNun = 127;
int lastXJoyValNun = 127;

int rollValue = 0;
int rollStep = 0;
int rollCount = 0;
int rollTotal = 0;

int pitchValue = 0;
int pitchStep = 0;
int pitchCount = 0;
int pitchTotal = 0;

int xJoyEffectValNun = 63;
int yJoyEffectValNun = 63;

//classic values------------------------------------------------------------------------------------------------------//
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

//guitar values------------------------------------------------------------------------------------------------------//
int greenStateGuitar = 0;
int redStateGuitar = 0;
int yellowStateGuitar = 0;
int blueStateGuitar = 0;
int orangeStateGuitar = 0;

int lastGreenStateGuitar = 0;
int lastRedStateGuitar = 0;
int lastYellowStateGuitar = 0;
int lastBlueStateGuitar = 0;
int lastOrangeStateGuitar = 0;

int greenNoteGuitar = 60;
int redNoteGuitar = 64;
int yellowNoteGuitar = 67;
int blueNoteGuitar = 71;
int orangeNoteGuitar = 72;

int strumGuitar = 128;
int lastStrumGuitar = 128;

int plusMinusGuitar = 128;
int lastPlusMinusGuitar = 128;

//setup and loop------------------------------------------------------------------------------------------------------//
void setup() {
  Serial.begin(9600);

  pinMode(modeButton, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(switchPin, INPUT);

  nunchuck1.begin();
  nunchuck1.type = NUNCHUCK;
  classic1.begin();
  classic1.type = WIICLASSIC;
  guitar1.begin();
  guitar1.type = GuitarHeroController;
}

void loop() {
  checkMode();
  if (currentMode == 0) {
    nunchuckMode();
  } else if (currentMode == 1) {
    classicMode();
  } else if (currentMode == 2) {
    guitarMode();
  }
}

void checkMode() {
  if (digitalRead(modeButton) == LOW and lastModeState == HIGH) {
    currentMode = currentMode + 1;
    if (currentMode > 2) {
      currentMode = 0;
    }
  }
  lastModeState = digitalRead(modeButton);
}

//nunchuck functions------------------------------------------------------------------------------------------------------//
void nunchuckMode() {
  usbMIDI.read();
  nunchuck1.readData();
  checkZNun();
  checkCNun();
  if (digitalRead(switchPin) == LOW) {
    checkJoyXNun();
    checkJoyYNun();
  } else {
    xJoyEffectNun();
    yJoyEffectNun();
  }
  setEffectsNun();
}

void checkZNun() {
  lastZStateNun = zStateNun;
  if (nunchuck1.values[10] == 0) {
    zStateNun = LOW;
  } else if (nunchuck1.values[10] == 255) {
    zStateNun = HIGH;
  }
  if (zStateNun == HIGH and lastZStateNun == LOW) {
    usbMIDI.sendNoteOn(currentNoteNun, 127, 1);
    delay(5);
  } else if (zStateNun == LOW and lastZStateNun == HIGH) {
    usbMIDI.sendNoteOff(currentNoteNun, 0, 1);
    delay(5);
  }
}

void checkCNun() {
  if (nunchuck1.values[11] == 255) {
    checkRollNun();
    checkPitchNun();
  }
}

void checkRollNun() {
  rollStep = map(nunchuck1.values[4], 75, 172, 0, 127); //converts tilt data to midi range
  if (rollStep > 127) {
    rollStep = 127;
  } else if (rollStep < 0) {
    rollStep = 0;
  }
  rollTotal = rollTotal + rollStep;
  rollCount = rollCount + 1;
  if (rollCount >= 15) { //uses an average of 15 for smoothness
    rollValue = (rollTotal / 15);
    rollCount = 0;
    rollTotal = 0;
    usbMIDI.sendControlChange(1, rollValue, 0);
  }
}

void checkPitchNun() {
  //Serial.println(nunchuck1.values[5]);
  pitchStep = map(nunchuck1.values[5], 80, 155, 0, 127);
  if (pitchStep > 127) {
    pitchStep = 127;
  } else if (pitchStep < 0) {
    pitchStep = 0;
  }
  pitchTotal = pitchTotal + pitchStep;
  pitchCount = pitchCount + 1;
  if (pitchCount >= 15) { //uses an average of ten for smoothness
    pitchValue = (pitchTotal / 15);
    pitchCount = 0;
    pitchTotal = 0;
    usbMIDI.sendControlChange(2, pitchValue, 0);
  }
}

void setEffectsNun() {
  if (digitalRead(switchPin) == LOW) {
    if (digitalRead(button1) == LOW) {
      usbMIDI.sendControlChange(1, rollValue, 0);
    }
    if (digitalRead(button2) == LOW) {
      usbMIDI.sendControlChange(2, pitchValue, 0);
    }
  } else {
    if (digitalRead(button1) == LOW) {
      usbMIDI.sendControlChange(3, xJoyEffectValNun, 0);
    }
    if (digitalRead(button2) == LOW) {
      usbMIDI.sendControlChange(4, yJoyEffectValNun, 0);
    }
  }
}

void checkJoyYNun() {
  lastYJoyValNun = yJoyValNun;
  yJoyValNun = nunchuck1.values[1];
  if ((yJoyValNun == 255) and (lastYJoyValNun != yJoyValNun)) {
    lastNoteNun = currentNoteNun; //changes note before turning off previous note for smooth playing
    currentNoteNun = currentNoteNun + 12;
    if (zStateNun == HIGH) {
      usbMIDI.sendNoteOn(currentNoteNun, 127, 1);
      usbMIDI.sendNoteOff(lastNoteNun, 0, 1);
    }
  } else if ((yJoyValNun == 0) and (lastYJoyValNun != yJoyValNun)) {
    lastNoteNun = currentNoteNun;
    currentNoteNun = currentNoteNun - 12;
    if (zStateNun == HIGH) {
      usbMIDI.sendNoteOn(currentNoteNun, 127, 1);
      usbMIDI.sendNoteOff(lastNoteNun, 0, 1);
    }
  }
}

void checkJoyXNun() {
  lastXJoyValNun = xJoyValNun;
  xJoyValNun = nunchuck1.values[0];
  if ((xJoyValNun == 255) and (lastXJoyValNun != xJoyValNun)) {
    lastNoteNun = currentNoteNun;
    currentNoteNun = currentNoteNun + 1;
    if (zStateNun == HIGH) {
      usbMIDI.sendNoteOn(currentNoteNun, 127, 1);
      usbMIDI.sendNoteOff(lastNoteNun, 0, 1);
    }
  } else if ((xJoyValNun == 0) and (lastXJoyValNun != xJoyValNun)) {
    lastNoteNun = currentNoteNun;
    currentNoteNun = currentNoteNun - 1;
    if (zStateNun == HIGH) {
      usbMIDI.sendNoteOn(currentNoteNun, 127, 1);
      usbMIDI.sendNoteOff(lastNoteNun, 0, 1);
    }
  }
}

void xJoyEffectNun() {
  if (nunchuck1.values[0] >= 130 or nunchuck1.values[0] <= 124) {
    xJoyValNun = map(nunchuck1.values[0], 0, 255, -15, 15);
    xJoyEffectValNun = xJoyEffectValNun + xJoyValNun;
    if (xJoyEffectValNun > 127) {
      xJoyEffectValNun = 127;
    }
    if (xJoyEffectValNun < 0) {
      xJoyEffectValNun = 0;
    }
    usbMIDI.sendControlChange(3, xJoyEffectValNun, 0);
    delay(25);
  }
}

void yJoyEffectNun() {
  if (nunchuck1.values[1] >= 130 or nunchuck1.values[1] <= 124) {
    yJoyValNun = map(nunchuck1.values[1], 0, 255, -15, 15);
    yJoyEffectValNun = yJoyEffectValNun + yJoyValNun;
    if (yJoyEffectValNun > 127) {
      yJoyEffectValNun = 127;
    }
    if (yJoyEffectValNun < 0) {
      yJoyEffectValNun = 0;
    }
    usbMIDI.sendControlChange(4, yJoyEffectValNun, 0);
    delay(25);
  }
}

//classic functions------------------------------------------------------------------------------------------------------//
void classicMode() {
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

//guitar functions------------------------------------------------------------------------------------------------------//
void guitarMode() {
  guitar1.readData();
  checkStrumGuitar();
  checkPlusMinusGuitar();
}

void checkPlusMinusGuitar() {
  plusMinusGuitar = guitar1.values[6];
  if (plusMinusGuitar == 255 and lastPlusMinusGuitar != plusMinusGuitar) {

    if (guitar1.values[10] == 255) {
      usbMIDI.sendNoteOff(greenNoteGuitar, 127, 1);
      greenNoteGuitar = greenNoteGuitar + 1;
      if (strumGuitar == 255 or strumGuitar == 0) {
        usbMIDI.sendNoteOn(greenNoteGuitar, 127, 1);
      }
    }
    if (guitar1.values[11] == 255) {
      usbMIDI.sendNoteOff(redNoteGuitar, 127, 1);
      redNoteGuitar = redNoteGuitar + 1;
      if (strumGuitar == 255 or strumGuitar == 0) {
        usbMIDI.sendNoteOn(redNoteGuitar, 127, 1);
      }
    }
    if (guitar1.values[12] == 255) {
      usbMIDI.sendNoteOff(yellowNoteGuitar, 127, 1);
      yellowNoteGuitar = yellowNoteGuitar + 1;
      if (strumGuitar == 255 or strumGuitar == 0) {
        usbMIDI.sendNoteOn(yellowNoteGuitar, 127, 1);
      }
    }
    if (guitar1.values[13] == 255) {
      usbMIDI.sendNoteOff(blueNoteGuitar, 127, 1);
      blueNoteGuitar = blueNoteGuitar + 1;
      if (strumGuitar == 255 or strumGuitar == 0) {
        usbMIDI.sendNoteOn(blueNoteGuitar, 127, 1);
      }
    }
    if (guitar1.values[14] == 255) {
      usbMIDI.sendNoteOff(orangeNoteGuitar, 127, 1);
      orangeNoteGuitar = orangeNoteGuitar + 1;
      if (strumGuitar == 255 or strumGuitar == 0) {
        usbMIDI.sendNoteOn(orangeNoteGuitar, 127, 1);
      }
    }
  }

  if (plusMinusGuitar == 0 and lastPlusMinusGuitar != plusMinusGuitar) {
    if (guitar1.values[10] == 255) {
      usbMIDI.sendNoteOff(greenNoteGuitar, 127, 1);
      greenNoteGuitar = greenNoteGuitar - 1;
      if (strumGuitar == 255 or strumGuitar == 0) {
        usbMIDI.sendNoteOn(greenNoteGuitar, 127, 1);
      }
    }
    if (guitar1.values[11] == 255) {
      usbMIDI.sendNoteOff(redNoteGuitar, 127, 1);
      redNoteGuitar = redNoteGuitar - 1;
      if (strumGuitar == 255 or strumGuitar == 0) {
        usbMIDI.sendNoteOn(redNoteGuitar, 127, 1);
      }
    }
    if (guitar1.values[12] == 255) {
      usbMIDI.sendNoteOff(yellowNoteGuitar, 127, 1);
      yellowNoteGuitar = yellowNoteGuitar - 1;
      if (strumGuitar == 255 or strumGuitar == 0) {
        usbMIDI.sendNoteOn(yellowNoteGuitar, 127, 1);
      }
    }
    if (guitar1.values[13] == 255) {
      usbMIDI.sendNoteOff(blueNoteGuitar, 127, 1);
      blueNoteGuitar = blueNoteGuitar - 1;
      if (strumGuitar == 255 or strumGuitar == 0) {
        usbMIDI.sendNoteOn(blueNoteGuitar, 127, 1);
      }
    }
    if (guitar1.values[14] == 255) {
      usbMIDI.sendNoteOff(orangeNoteGuitar, 127, 1);
      orangeNoteGuitar = orangeNoteGuitar - 1;
      if (strumGuitar == 255 or strumGuitar == 0) {
        usbMIDI.sendNoteOn(orangeNoteGuitar, 127, 1);
      }
    }
  }

  lastPlusMinusGuitar = plusMinusGuitar;
}

void checkStrumGuitar() {
  strumGuitar = guitar1.values[7];
  if (strumGuitar == 255 or strumGuitar == 0) {
    checkGreenGuitar();
    checkRedGuitar();
    checkYellowGuitar();
    checkBlueGuitar();
    checkOrangeGuitar();
  }
  if ((lastStrumGuitar == 255 or lastStrumGuitar == 0) and lastStrumGuitar != strumGuitar) {
    usbMIDI.sendNoteOff(greenNoteGuitar, 127, 1);
    usbMIDI.sendNoteOff(redNoteGuitar, 127, 1);
    usbMIDI.sendNoteOff(yellowNoteGuitar, 127, 1);
    usbMIDI.sendNoteOff(blueNoteGuitar, 127, 1);
    usbMIDI.sendNoteOff(orangeNoteGuitar, 127, 1);
    lastGreenStateGuitar = 0;
    lastRedStateGuitar = 0;
    lastYellowStateGuitar = 0;
    lastBlueStateGuitar = 0;
    lastOrangeStateGuitar = 0;
  }
  lastStrumGuitar = strumGuitar;
}

void checkGreenGuitar() {
  greenStateGuitar = guitar1.values[10];
  if (greenStateGuitar == 255 and greenStateGuitar != lastGreenStateGuitar) {
    usbMIDI.sendNoteOn(greenNoteGuitar, 127, 1);
    delay(5);
  }
  if (greenStateGuitar == 0 and greenStateGuitar != lastGreenStateGuitar) {
    usbMIDI.sendNoteOff(greenNoteGuitar, 127, 1);
    delay(5);
  }
  lastGreenStateGuitar = greenStateGuitar;
}

void checkRedGuitar() {
  redStateGuitar = guitar1.values[11];
  if (redStateGuitar == 255 and redStateGuitar != lastRedStateGuitar) {
    usbMIDI.sendNoteOn(redNoteGuitar, 127, 1);
    delay(5);
  }
  if (redStateGuitar == 0 and redNoteGuitar != lastRedStateGuitar) {
    usbMIDI.sendNoteOff(redNoteGuitar, 127, 1);
    delay(5);
  }
  lastRedStateGuitar = redStateGuitar;
}

void checkYellowGuitar() {
  yellowStateGuitar = guitar1.values[12];
  if (yellowStateGuitar == 255 and yellowStateGuitar != lastYellowStateGuitar) {
    usbMIDI.sendNoteOn(yellowNoteGuitar, 127, 1);
    delay(5);
  }
  if (yellowStateGuitar == 0 and yellowStateGuitar != lastYellowStateGuitar) {
    usbMIDI.sendNoteOff(yellowNoteGuitar, 127, 1);
    delay(5);
  }
  lastYellowStateGuitar = yellowStateGuitar;
}

void checkBlueGuitar() {
  blueStateGuitar = guitar1.values[13];
  if (blueStateGuitar == 255 and blueStateGuitar != lastBlueStateGuitar) {
    usbMIDI.sendNoteOn(blueNoteGuitar, 127, 1);
    delay(5);
  }
  if (blueStateGuitar == 0 and blueStateGuitar != lastBlueStateGuitar) {
    usbMIDI.sendNoteOff(blueNoteGuitar, 127, 1);
    delay(5);
  }
  lastBlueStateGuitar = blueStateGuitar;
}

void checkOrangeGuitar() {
  orangeStateGuitar = guitar1.values[14];
  if (orangeStateGuitar == 255 and orangeStateGuitar != lastOrangeStateGuitar) {
    usbMIDI.sendNoteOn(orangeNoteGuitar, 127, 1);
    delay(5);
  }
  if (orangeStateGuitar == 0 and orangeStateGuitar != lastOrangeStateGuitar) {
    usbMIDI.sendNoteOff(orangeNoteGuitar, 127, 1);
    delay(5);
  }
  lastOrangeStateGuitar = orangeStateGuitar;
}
