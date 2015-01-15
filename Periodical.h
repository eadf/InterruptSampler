#ifndef PERIODICAL_INCLUDE
#define PERIODICAL_INCLUDE
#include <stdint.h>

class Periodical {
public:
  Periodical(uint32_t period);
  bool howAboutNow();
  void reset();
protected:
  uint32_t lastSample;
  uint32_t period;
};

#endif
