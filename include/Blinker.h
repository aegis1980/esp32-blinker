
#ifndef __Blinker__H__
#define __Blinker__H__

#include <Ticker.h>
#include <Arduino.h>

enum blink_t {BLINK_ON, BLINK_OFF, CONTINUOUS_ON, CONTINUOUS_OFF};

class Blinker {
  private:
    Ticker _ticker;
    float _onForTime;
    float _offForTime;
    blink_t _blinkState;
    short pin;

    float _previousOnForTime ;
    float _previoudOffForTime;
    blink_t _previousBlinkState;
    
    void setBlinkState(blink_t state);

  public:

    Blinker(int pin);
    void toggle();
    void blink(float on_for, float off_for);
    void continuousOn();
    void continuousOff();

    void snapshot();
    void resume();
};

#endif // __Blinker__H__
