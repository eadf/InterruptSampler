#include "Periodical.h"
#include "Arduino.h"

Periodical::Periodical(uint32_t period) {
  this->period = period;
  lastSample =  micros();
}

bool Periodical::howAboutNow() {
  uint32_t now = micros();
  bool rv = false;
  if (now-lastSample>= period) {
    lastSample = now;
    rv = true;
  }
  return rv;
}

void Periodical::reset() {
  lastSample = micros();
}
