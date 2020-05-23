#include "Sensors.h"

SENSORS::SENSORS() {}
SENSORS::~SENSORS() {}

byte SENSORS::procitaj()
{
  byte x;
  x=digitalRead(2);
  return x;
  }


const int PIRsensorInterrupt = 0; 
const int LedPin = 13;           
volatile int lastPIRsensorState = 1;  
volatile int PIRsensorState = 0; 


void wakeUpNow(){                
  PIRsensorState = !lastPIRsensorState;   
}

void SENSORS::Hibernate()       
{

attachInterrupt(PIRsensorInterrupt,wakeUpNow, CHANGE);   

delay(50);
 LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
 delay(50);          
 detachInterrupt(PIRsensorInterrupt);   
}



