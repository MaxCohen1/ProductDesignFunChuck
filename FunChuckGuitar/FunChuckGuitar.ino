#include <WiiChuck.h>
Accessory guitar1;

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

void setup() {
  Serial.begin(9600);
  guitar1.begin();
  guitar1.type = GuitarHeroController;
}

void loop() {
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
