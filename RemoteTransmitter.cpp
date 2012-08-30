#include <util/delay.h>

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
    sendOnce(bits);
  }
}

void RemoteTransmitter::sendOnce(uint32_t bits) {
  digitalWrite(mPin, HIGH);
  _delay_us(shortPulseLen);
  digitalWrite(mPin, LOW);
  _delay_us(syncLen);

  for (int8_t i = 23; i >= 0; i--) {
    bool val = bits & (((uint32_t)1) << i);
    if (val) {
      digitalWrite(mPin, HIGH);
      _delay_us(longPulseLen);
      digitalWrite(mPin, LOW);
      _delay_us(shortPulseLen);
    }
    else {
      digitalWrite(mPin, HIGH);
      _delay_us(shortPulseLen);
      digitalWrite(mPin, LOW);
      _delay_us(longPulseLen);
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
