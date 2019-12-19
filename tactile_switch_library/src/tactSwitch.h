//
//  tactile switch library ( 20181015 ) by tarekichi
//

#ifndef tactSwitch_h
#define tactSwitch_h

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

enum PINS
{
  ARDUINO_D2_PIN = 2,
  ARDUINO_D3_PIN,
  ARDUINO_D4_PIN,
  ARDUINO_D5_PIN,
  ARDUINO_D6_PIN,
  ARDUINO_D7_PIN,
  ARDUINO_D8_PIN,
  ARDUINO_D9_PIN,
  ARDUINO_D10_PIN,
  ARDUINO_D11_PIN,
  ARDUINO_D12_PIN
};

enum trigger { _RISING_, _FALLING_, _CHANGE_, _HOLD_ };

class tactSwitch
{
  protected:

    int16_t _LongPushTime;
    int16_t _ReleaseTime;
    int16_t _DelayTime;
    uint8_t _DigitalPin;
    uint8_t _InputMode;
    boolean _PreviousSw;
    boolean _ReleaseFlag;

  public:

    bool  DirectInputSw;
    bool  EdgeTriggerSw;
    int16_t LongPushCounter;
    int16_t ReleaseCounter;

    tactSwitch(int16_t longPushTime, int16_t releaseTime, int16_t delayTime ); // constructor

    void switch_setup( uint8_t digitalPin, uint8_t inputMode );

    void switch_checker( uint8_t triggerType );

    bool is_long_push_enable( void );

    bool is_release_enable( void );
};

#endif
