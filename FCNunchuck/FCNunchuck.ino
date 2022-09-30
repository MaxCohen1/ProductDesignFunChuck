#include <WiiChuck.h>
Accessory nunchuck1;

bool zState = HIGH;
bool lastZState = HIGH;
int currentNote = 60;
int lastNote = 60;

int yJoyVal = 127;
int lastYJoyVal = 127;
int xJoyVal = 127;
int lastXJoyVal = 127;

int rollValue = 0;
int rollStep = 0;
int rollCount = 0;
int rollTotal = 0;

int pitchValue = 0;
int pitchStep = 0;
int pitchCount = 0;
int pitchTotal = 0;

int rollButtonPin = 33;
int pitchButtonPin = 34;
int switchPin = 37;

int xJoyEffectVal = 63;
int xJoyValConvert = 0;

int yJoyEffectVal = 63;
int yJoyValConvert = 0;

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
  checkZ();
  checkC();
  if (digitalRead(switchPin) == HIGH) {
    checkJoyX();
    checkJoyY();
  } else {
    xJoyEffect();
    yJoyEffect();
  }
  setEffects();
}

void checkZ() {
  lastZState = zState;
  if (nunchuck1.values[10] == 0) {
    zState = LOW;
  } else if (nunchuck1.values[10] == 255) {
    zState = HIGH;
  }
  if (zState == HIGH and lastZState == LOW) {
    usbMIDI.sendNoteOn(currentNote, 127, 1);
    delay(5);
  } else if (zState == LOW and lastZState == HIGH) {
    usbMIDI.sendNoteOff(currentNote, 0, 1);
    delay(5);
  }
}

void checkC() {
  if (nunchuck1.values[11] == 255) {
    checkRoll();
    checkPitch();
  }
}

void checkRoll() {
  //  Serial.println(nunchuck1.values[4]);
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

void checkPitch() {
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

void setEffects() {
  if (digitalRead(switchPin) == HIGH) {
    if (digitalRead(rollButtonPin) == HIGH) {
      usbMIDI.sendControlChange(1, rollValue, 0);
    }
    if (digitalRead(pitchButtonPin) == HIGH) {
      usbMIDI.sendControlChange(2, pitchValue, 0);
    }
  } else {
    if (digitalRead(rollButtonPin) == HIGH) {
      usbMIDI.sendControlChange(3, xJoyEffectVal, 0);
    }
    if (digitalRead(pitchButtonPin) == HIGH) {
      usbMIDI.sendControlChange(4, yJoyEffectVal, 0);
    }
  }
}

void checkJoyY() {
  lastYJoyVal = yJoyVal;
  yJoyVal = nunchuck1.values[1];
  if ((yJoyVal == 255) and (lastYJoyVal != yJoyVal)) {
    lastNote = currentNote; //changes note before turning off previous note for smooth playing
    currentNote = currentNote + 12;
    if (zState == HIGH) {
      usbMIDI.sendNoteOn(currentNote, 127, 1);
      usbMIDI.sendNoteOff(lastNote, 0, 1);
    }
  } else if ((yJoyVal == 0) and (lastYJoyVal != yJoyVal)) {
    lastNote = currentNote;
    currentNote = currentNote - 12;
    if (zState == HIGH) {
      usbMIDI.sendNoteOn(currentNote, 127, 1);
      usbMIDI.sendNoteOff(lastNote, 0, 1);
    }
  }
}

void checkJoyX() {
  lastXJoyVal = xJoyVal;
  xJoyVal = nunchuck1.values[0];
  if ((xJoyVal == 255) and (lastXJoyVal != xJoyVal)) {
    lastNote = currentNote;
    currentNote = currentNote + 1;
    if (zState == HIGH) {
      usbMIDI.sendNoteOn(currentNote, 127, 1);
      usbMIDI.sendNoteOff(lastNote, 0, 1);
    }
  } else if ((xJoyVal == 0) and (lastXJoyVal != xJoyVal)) {
    lastNote = currentNote;
    currentNote = currentNote - 1;
    if (zState == HIGH) {
      usbMIDI.sendNoteOn(currentNote, 127, 1);
      usbMIDI.sendNoteOff(lastNote, 0, 1);
    }
  }
}

//Consolidate joy effects functions

void xJoyEffect() {
  if (nunchuck1.values[0] >= 130 or nunchuck1.values[0] <= 124) {
    xJoyVal = nunchuck1.values[0];
    xJoyValConvert = map(xJoyVal, 0, 255, -15, 15);
    xJoyEffectVal = xJoyEffectVal + xJoyValConvert;
    if (xJoyEffectVal > 127) {
      xJoyEffectVal = 127;
    }
    if (xJoyEffectVal < 0) {
      xJoyEffectVal = 0;
    }
    usbMIDI.sendControlChange(3, xJoyEffectVal, 0);
    delay(25);
  }
}

void yJoyEffect() {
  if (nunchuck1.values[1] >= 130 or nunchuck1.values[1] <= 124) {
    yJoyVal = nunchuck1.values[1];
    yJoyValConvert = map(yJoyVal, 0, 255, -15, 15);
    yJoyEffectVal = yJoyEffectVal + yJoyValConvert;
    if (yJoyEffectVal > 127) {
      yJoyEffectVal = 127;
    }
    if (yJoyEffectVal < 0) {
      yJoyEffectVal = 0;
    }
    usbMIDI.sendControlChange(4, yJoyEffectVal, 0);
    delay(25);
  }
}
