//
//  tactile switch library ( 20181015 ) by tarekichi
//

#include "tactSwitch.h"

tactSwitch::tactSwitch( int16_t longPushTime, int16_t releaseTime, int16_t delayTime )
{
  _LongPushTime = longPushTime;
  _ReleaseTime  = releaseTime + 1;
  _DelayTime    = delayTime;
}

void tactSwitch::switch_setup( uint8_t digitalPin, uint8_t inputMode )
{
  _DigitalPin = digitalPin;
  _InputMode  = inputMode;
  pinMode( _DigitalPin, _InputMode );
}

void tactSwitch::switch_checker( uint8_t triggerType )
{
  switch ( _InputMode )
  {
    case INPUT_PULLUP : DirectInputSw = !digitalRead( _DigitalPin ); break;
    case INPUT        : DirectInputSw =  digitalRead( _DigitalPin ); break;
  }
  switch ( triggerType )
  {
    case _RISING_  : EdgeTriggerSw = DirectInputSw ^ _PreviousSw & DirectInputSw;  break;
    case _FALLING_ : EdgeTriggerSw = DirectInputSw & _PreviousSw ^ _PreviousSw; break;
    case _CHANGE_  : EdgeTriggerSw = DirectInputSw ^ _PreviousSw; break;
    case _HOLD_    : EdgeTriggerSw = DirectInputSw; break;
  }
  _PreviousSw = DirectInputSw;
  
  if ( DirectInputSw ) { LongPushCounter++; ReleaseCounter = _ReleaseTime; } else LongPushCounter = 0;
  if ( LongPushCounter > _LongPushTime ) { LongPushCounter--; ReleaseCounter = 0; return; }
  if ( ReleaseCounter ) ReleaseCounter--; else LongPushCounter = 0;
  if ( ReleaseCounter == 1 ) _ReleaseFlag = true;
}

bool tactSwitch::is_long_push_enable( void )
{
  if ( LongPushCounter == _LongPushTime ) return( true ); else return( false );
}

bool tactSwitch::is_release_enable( void )
{
  if ( _ReleaseFlag ) { _ReleaseFlag = false; return( true ); } else return( false );
}
