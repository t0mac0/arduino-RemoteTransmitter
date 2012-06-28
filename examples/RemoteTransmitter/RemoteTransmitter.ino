#include <RemoteTransmitter.h>

RemoteTransmitterID tx(8);

void setup() {
  tx.begin();
  tx.setID(1234);
}

void loop() {
  tx.sendCode(5);
}
