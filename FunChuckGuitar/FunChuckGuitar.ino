#include <WiiChuck.h>
Accessory nunchuck1;

int greenState = 0;
int redState = 0;
int yellowState = 0;
int blueState = 0;
int orangeState = 0;

int lastGreenState = 0;
int lastRedState = 0;
int lastYellowState = 0;
int lastBlueState = 0;
int lastOrangeState = 0;

int greenNote = 60;
int redNote = 64;
int yellowNote = 67;
int blueNote = 71;
int orangeNote = 72;

int strum = 128;
int lastStrum = 128;

int plusMinus = 128;
int lastPlusMinus = 128;

void setup() {
  Serial.begin(9600);
  nunchuck1.begin();
  nunchuck1.type = GuitarHeroController;
}

void loop() {
  nunchuck1.readData();
  checkStrum();
  checkPlusMinus();
}

void checkPlusMinus() {
  plusMinus = nunchuck1.values[6];
  if (plusMinus == 255 and lastPlusMinus != plusMinus) {

    if (nunchuck1.values[10] == 255) {
      usbMIDI.sendNoteOff(greenNote, 127, 1);
      greenNote = greenNote + 1;
      if (strum == 255 or strum == 0) {
        usbMIDI.sendNoteOn(greenNote, 127, 1);
      }
    }
    if (nunchuck1.values[11] == 255) {
      usbMIDI.sendNoteOff(redNote, 127, 1);
      redNote = redNote + 1;
      if (strum == 255 or strum == 0) {
        usbMIDI.sendNoteOn(redNote, 127, 1);
      }
    }
    if (nunchuck1.values[12] == 255) {
      usbMIDI.sendNoteOff(yellowNote, 127, 1);
      yellowNote = yellowNote + 1;
      if (strum == 255 or strum == 0) {
        usbMIDI.sendNoteOn(yellowNote, 127, 1);
      }
    }
    if (nunchuck1.values[13] == 255) {
      usbMIDI.sendNoteOff(blueNote, 127, 1);
      blueNote = blueNote + 1;
      if (strum == 255 or strum == 0) {
        usbMIDI.sendNoteOn(blueNote, 127, 1);
      }
    }
    if (nunchuck1.values[14] == 255) {
      usbMIDI.sendNoteOff(orangeNote, 127, 1);
      orangeNote = orangeNote + 1;
      if (strum == 255 or strum == 0) {
        usbMIDI.sendNoteOn(orangeNote, 127, 1);
      }
    }
  }

  if (plusMinus == 0 and lastPlusMinus != plusMinus) {
    if (nunchuck1.values[10] == 255) {
      usbMIDI.sendNoteOff(greenNote, 127, 1);
      greenNote = greenNote - 1;
      if (strum == 255 or strum == 0) {
        usbMIDI.sendNoteOn(greenNote, 127, 1);
      }
    }
    if (nunchuck1.values[11] == 255) {
      usbMIDI.sendNoteOff(redNote, 127, 1);
      redNote = redNote - 1;
      if (strum == 255 or strum == 0) {
        usbMIDI.sendNoteOn(redNote, 127, 1);
      }
    }
    if (nunchuck1.values[12] == 255) {
      usbMIDI.sendNoteOff(yellowNote, 127, 1);
      yellowNote = yellowNote - 1;
      if (strum == 255 or strum == 0) {
        usbMIDI.sendNoteOn(yellowNote, 127, 1);
      }
    }
    if (nunchuck1.values[13] == 255) {
      usbMIDI.sendNoteOff(blueNote, 127, 1);
      blueNote = blueNote - 1;
      if (strum == 255 or strum == 0) {
        usbMIDI.sendNoteOn(blueNote, 127, 1);
      }
    }
    if (nunchuck1.values[14] == 255) {
      usbMIDI.sendNoteOff(orangeNote, 127, 1);
      orangeNote = orangeNote - 1;
      if (strum == 255 or strum == 0) {
        usbMIDI.sendNoteOn(orangeNote, 127, 1);
      }
    }
  }

  lastPlusMinus = plusMinus;
}

void checkStrum() {
  strum = nunchuck1.values[7];
  if (strum == 255 or strum == 0) {
    checkGreen();
    checkRed();
    checkYellow();
    checkBlue();
    checkOrange();
  }
  if ((lastStrum == 255 or lastStrum == 0) and lastStrum != strum) {
    usbMIDI.sendNoteOff(greenNote, 127, 1);
    usbMIDI.sendNoteOff(redNote, 127, 1);
    usbMIDI.sendNoteOff(yellowNote, 127, 1);
    usbMIDI.sendNoteOff(blueNote, 127, 1);
    usbMIDI.sendNoteOff(orangeNote, 127, 1);
    lastGreenState = 0;
    lastRedState = 0;
    lastYellowState = 0;
    lastBlueState = 0;
    lastOrangeState = 0;
  }
  lastStrum = strum;
}

void checkGreen() {
  greenState = nunchuck1.values[10];
  if (greenState == 255 and greenState != lastGreenState) {
    usbMIDI.sendNoteOn(greenNote, 127, 1);
    delay(5);
  }
  if (greenState == 0 and greenState != lastGreenState) {
    usbMIDI.sendNoteOff(greenNote, 127, 1);
    delay(5);
  }
  lastGreenState = greenState;
}

void checkRed() {
  redState = nunchuck1.values[11];
  if (redState == 255 and redState != lastRedState) {
    usbMIDI.sendNoteOn(redNote, 127, 1);
    delay(5);
  }
  if (redState == 0 and redNote != lastRedState) {
    usbMIDI.sendNoteOff(redNote, 127, 1);
    delay(5);
  }
  lastRedState = redState;
}

void checkYellow() {
  yellowState = nunchuck1.values[12];
  if (yellowState == 255 and yellowState != lastYellowState) {
    usbMIDI.sendNoteOn(yellowNote, 127, 1);
    delay(5);
  }
  if (yellowState == 0 and yellowState != lastYellowState) {
    usbMIDI.sendNoteOff(yellowNote, 127, 1);
    delay(5);
  }
  lastYellowState = yellowState;
}

void checkBlue() {
  blueState = nunchuck1.values[13];
  if (blueState == 255 and blueState != lastBlueState) {
    usbMIDI.sendNoteOn(blueNote, 127, 1);
    delay(5);
  }
  if (blueState == 0 and blueState != lastBlueState) {
    usbMIDI.sendNoteOff(blueNote, 127, 1);
    delay(5);
  }
  lastBlueState = blueState;
}

void checkOrange() {
  orangeState = nunchuck1.values[14];
  if (orangeState == 255 and orangeState != lastOrangeState) {
    usbMIDI.sendNoteOn(orangeNote, 127, 1);
    delay(5);
  }
  if (orangeState == 0 and orangeState != lastOrangeState) {
    usbMIDI.sendNoteOff(orangeNote, 127, 1);
    delay(5);
  }
  lastOrangeState = orangeState;
}
