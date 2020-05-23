#include <Arduino.h>
#include <LowPower.h>
#include "main.h"
#include "Sensors.h"
#include "Radio_nRF.h"

SENSORS sensor;
RADIO radioNRF;

SensorData dataToSend; 
StateType state = READ_SERIAL;

    bool rslt;      

void setup()
{
  Serial.begin(115200);
  radioNRF.nRF_init();

  delay(100);
}
void loop()
{
  switch (state)
  {
  case READ_SERIAL:

    state = SLEEP;
    break;
    
    
  case SLEEP:
      Serial.println(F("spavanje"));
        delay(100);
        radioNRF.RF_powerDown();
        sensor.Hibernate();
        radioNRF.RF_powerUp();
        dataToSend.pokret_rukom=1;
        delay(100);
        Serial.println(F("buđenje"));
        state=RADIO_TX;
    break;
       
      case RADIO_TX:
        Serial.println(F("slanje"));
        Serial.println(dataToSend.pokret_rukom);
        delay(100);
        radioNRF.RF_send(dataToSend);
        state = SLEEP;
    break;
        
  }
}