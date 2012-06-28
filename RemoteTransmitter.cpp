#include "Arduino.h"
#include "RemoteTransmitter.h"

RemoteTransmitter::RemoteTransmitter(int pin)
  : mPin(pin)
{}

void RemoteTransmitter::begin() {
  pinMode(mPin, OUTPUT);
  digitalWrite(mPin, LOW);
}

void RemoteTransmitter::send(uint32_t bits) {
  uint8_t times = 5;

  while (times --> 0) {
    digitalWrite(mPin, HIGH);
    delayMicroseconds(shortPulseLen);
    digitalWrite(mPin, LOW);
    delayMicroseconds(syncLen);

    for (int8_t i = 23; i >= 0; i--) {
      bool val = bits & (((uint32_t)1) << i);
      if (val) {
	digitalWrite(mPin, HIGH);
	delayMicroseconds(longPulseLen);
	digitalWrite(mPin, LOW);
	delayMicroseconds(shortPulseLen);
      }
      else {
	digitalWrite(mPin, HIGH);
	delayMicroseconds(shortPulseLen);
	digitalWrite(mPin, LOW);
	delayMicroseconds(longPulseLen);
      }
    }
  }
}

RemoteTransmitterID::RemoteTransmitterID(int pin)
  : RemoteTransmitter(pin)
{}

void RemoteTransmitterID::sendCode(uint8_t code) {
  send(mID | (code & 0xf));
}

void RemoteTransmitterID::setID(uint32_t id) {
  mID = id << 4;
}
