#ifndef RemoteTransmitter_h
#define RemoteTransmitter_h

#include "Arduino.h"

class RemoteTransmitter {
  static const unsigned int fundamentalUnit = 500;
  static const unsigned int syncLen = fundamentalUnit * 31;
  static const unsigned int longPulseLen = fundamentalUnit * 3;
  static const unsigned int shortPulseLen = fundamentalUnit;

  int mPin;
public:
  RemoteTransmitter(int pin);
  void begin();
  void send(uint32_t bits);
};

class RemoteTransmitterID : public RemoteTransmitter {
  uint32_t mID; // shifted up to ID space
public:
  RemoteTransmitterID(int pin);
  void setID(uint32_t id);
  void sendCode(uint8_t code);
};

#endif
