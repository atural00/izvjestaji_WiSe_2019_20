//NAPOMENA:
//KOLEGICA ANDELA MARIC I JA SMO SURADIVALI I SKUPA RADILI ZADATAK, PREMA TOME SU POSTUPCI IDENTICNI !
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
 // sensor.BH1750_init();

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
    dataToSend.temp = sensor.readTemp();
    dataToSend.lightLevel = sensor.readLight();
    state = RADIO_TX;
    break;
  case RADIO_TX:

  rslt = radioNRF.RF_send(dataToSend);
    state = RADIO_RX;

    break;
  case RADIO_RX:
  
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
