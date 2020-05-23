#include "Radio_nRF.h"
#include "main.h"

RF24 radio(CE_PIN, CSN_PIN); 

RADIO::RADIO() {}
RADIO::~RADIO() {}

const byte address[6] = {"3node"};

void RADIO::nRF_init()
{
    radio.begin();
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(112);
    radio.setPALevel(RF24_PA_MAX);
    radio.setRetries(3, 5); 
    radio.openWritingPipe(address);
}

bool RADIO::RF_send(struct SensorData sensorData)
{
    bool rslt = radio.write(&sensorData, sizeof(sensorData));
    if (rslt)
    {
        Serial.println("  Acknowledge received");
    }
    else
    {
        Serial.println("  Tx failed");
    }
    return rslt;
}

void RADIO::RF_receive(bool rslt)
{
 
}
void RADIO::RF_powerDown()
{
 radio.powerDown();
}
void RADIO::RF_powerUp()
{
 radio.powerUp();
}