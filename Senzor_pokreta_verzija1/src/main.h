#ifndef main_h
#define main_h

struct SensorData
{
  
    //novi kod
    byte pokret_rukom;
};

typedef enum
{
    READ_SERIAL,
    READ_SENSORS,
   
    RADIO_TX,
  
    //novi
    RADIO_SLANJE,
    RADIO_PRIMANJE
} StateType;

#endif