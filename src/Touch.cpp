#include "Arduino.h"
#include "Touch.h"

int TouchClass::read(byte ADCChannel, int samples)
{
  long _value = 0;
  for(int _counter = 0; _counter < samples; _counter ++)
  {
    // set the analog pin as an input pin with a pullup resistor
    // this will start charging the capacitive element attached to that pin
    pinMode(ADCChannel, INPUT_PULLUP);
    // connect the ADC input and the internal sample and hold capacitor to ground to discharge it
    ADMUX |=   0b11111;
    // start the conversion
    ADCSRA |= (1 << ADSC);
    // ADSC is cleared when the conversion finishes
    while((ADCSRA & (1 << ADSC)));
    pinMode(ADCChannel, INPUT);
    _value += analogRead(ADCChannel);
  }
  return _value / samples;
}
TouchClass Touch;
