#ifndef main_h
#define main_h

struct SensorData
{
  byte pokret_rukom;
};

typedef enum
{
    READ_SERIAL,
    READ_SENSORS,
    RADIO_TX,
    SLEEP,
    } StateType;

#endif