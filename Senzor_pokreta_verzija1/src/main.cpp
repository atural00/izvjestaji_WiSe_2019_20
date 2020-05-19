
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


int ledPin = 13;                // LED 
int pirPin = 2;                 // PIR Out pin 
int pirStat = 0;                   // PIR status

void setup()
{
   pinMode(ledPin, OUTPUT);     
 pinMode(pirPin, INPUT); 
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
    pirStat = digitalRead(pirPin); 
 if (pirStat == HIGH) {            // if motion detected
   digitalWrite(ledPin, HIGH);  // turn LED ON
   Serial.println("Hey I got you!!!");
 } 
 else {
   digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
 }

      state=RADIO_TX;
      break;
       case RADIO_TX:
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
