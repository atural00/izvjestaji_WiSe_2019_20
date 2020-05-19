
#include <Arduino.h>
#include <LowPower.h>
#include "main.h"
#include "Sensors.h"
#include "Radio_nRF.h"

SENSORS sensor;
RADIO radioNRF;

SensorData dataToSend;  //defirano za TX
StateType state = READ_SERIAL;

    bool rslt;       //nova varijabla !! (trebalo je def)

void setup()
{
  Serial.begin(115200);
 // sensor.DHT_init();
  //sensor.BH1750_init();

  radioNRF.nRF_init();
  delay(100);
}

void loop()
{
  switch (state)
  {
  case READ_SERIAL:

    state = READ_SENSORS;
    break;
  case READ_SENSORS:
    //novi kod
    dataToSend.pokret_rukom=sensor.procitaj();

 Serial.println(F("Pokret"));
      state=RADIO_TX;
      break;
       case RADIO_SLANJE:
        Serial.println(F("slanje"));
        radioNRF.nRF_init();
        delay(100);
        rslt=radioNRF.RF_send(dataToSend);
        state = RADIO_PRIMANJE;
        break;

      case RADIO_PRIMANJE:
        Serial.println(F("primanje"));
        radioNRF.RF_receive(rslt);
      
       state = SLEEP_STATE;

    break;

  case SLEEP_STATE:

    delay(50);
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    delay(50);

    state = READ_SERIAL;
    break;
        
  }
}
