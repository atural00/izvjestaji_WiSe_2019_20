#ifndef Sensors_h
#define Sensors_h
#include <Arduino.h>
#include <LowPower.h>
#include <avr/interrupt.h>        
#include <avr/sleep.h>            

class SENSORS
{
public:
        SENSORS();
        ~SENSORS();

//novi kodovi
     byte procitaj();
  void Hibernate();
       

};

#endif