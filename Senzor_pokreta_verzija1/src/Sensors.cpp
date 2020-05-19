#include "Sensors.h"


SENSORS::SENSORS() {}
SENSORS::~SENSORS() {}



//novi kod
byte SENSORS::procitaj()
{
  byte x;
  x=digitalRead(9);
  return x;
  }




