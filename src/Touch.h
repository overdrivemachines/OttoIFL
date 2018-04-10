#ifndef Touch_h
#define Touch_h

#include "Arduino.h"

class TouchClass
{
  public:
  int read(byte ADCChannel, int samples = 100);
};
extern TouchClass Touch;

#endif
