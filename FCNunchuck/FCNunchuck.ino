#include <WiiChuck.h>
Accessory nunchuck1;

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

int button1 = 34;
int button2 = 33;
int switchPin = 37;

void setup() {
  Serial.begin(9600);
  pinMode(rollButtonPin, INPUT);
  pinMode(pitchButtonPin, INPUT);
  pinMode(switchPin, INPUT);
  nunchuck1.begin();
  nunchuck1.type = NUNCHUCK;
}

void loop() {
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
    if (digitalRead(button1) == HIGH) {
      usbMIDI.sendControlChange(1, rollValue, 0);
    }
    if (digitalRead(button2) == HIGH) {
      usbMIDI.sendControlChange(2, pitchValue, 0);
    }
  } else {
    if (digitalRead(button1) == HIGH) {
      usbMIDI.sendControlChange(3, xJoyEffectValNun, 0);
    }
    if (digitalRead(button2) == HIGH) {
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
