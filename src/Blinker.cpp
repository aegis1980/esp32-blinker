#include "Blinker.h"


void callbackFunc(Blinker* blinkerInstance) {
  blinkerInstance->toggle();
}

/*
 * Constructor. Only needs to know what pin to blink.
 */
Blinker::Blinker(int p) {
  pin = p;
  pinMode(p, OUTPUT);
}


void Blinker::toggle(){
  if (_blinkState == BLINK_ON){
    setBlinkState(BLINK_OFF);
     _ticker.once(_offForTime, callbackFunc, this);
  } else if (_blinkState == BLINK_OFF){
    setBlinkState(BLINK_ON);
    _ticker.once(_onForTime, callbackFunc, this);
  } else {
    _ticker.detach();
  }
}



/*
 * Sets the blink state ON or OFF
 */
void Blinker::setBlinkState(blink_t state)
{
  if (state == CONTINUOUS_ON || state == BLINK_ON){
    digitalWrite(pin, HIGH); 
  } else {
    digitalWrite(pin, LOW); 
  }
  _blinkState = state;
}

/*
 * Executes the blink. It allows to specify new on and off times. Use negative
 * values if you don't want to change what is already set.
 */

void Blinker::blink(float onFor, float offFor) {
  

  if (
      (_onForTime != onFor && _offForTime!=offFor) ||
      _blinkState == CONTINUOUS_ON ||
      _blinkState == CONTINUOUS_OFF
    ){
    _ticker.detach();
    _onForTime = onFor;
    _offForTime = offFor;
    _ticker.once(onFor, callbackFunc, this);
  }
}

/*
 * Turns off the blink. And turns on LED continously
 */
void Blinker::continuousOn() {
  _ticker.detach();
  setBlinkState(CONTINUOUS_ON);
}

/*
 * Turns off the blink. And turns off LED continously
 */
void Blinker::continuousOff() {
  _ticker.detach();
  setBlinkState(CONTINUOUS_OFF);
}


void Blinker::snapshot(){
  _previousOnForTime = _onForTime;
  _previoudOffForTime = _offForTime;
  _previousBlinkState = _blinkState;
}

/*
 * Resume from snapshot
 */
void Blinker::resume() {
  if (_previousBlinkState == CONTINUOUS_ON){
    continuousOn();
  } else if (_previousBlinkState == CONTINUOUS_OFF){
    continuousOff();
  } else {
    blink(_previousOnForTime,_previoudOffForTime);
  }  
}