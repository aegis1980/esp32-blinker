#include <Arduino.h>
#include "Blinker.h"


void callbackFunc(Blinker* blinkerInstance) {
  blinkerInstance->toggle();
}

/*
 * Constructor. Only needs to know what pin to blink.
 */
Blinker::Blinker(int p) {
  pin = p;
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

void Blinker::blink(float on_for, float off_for) {
  _ticker.detach();
  _onForTime = on_for;
  _offForTime = off_for;

  _ticker.once(on_for, callbackFunc, this);
}

/*
 * Equivalent to delay(d), but updates the blink.
 */
void Blinker::blinkDelay(int d)
{

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
/*
 * Called in loop() subsequent to call to 'blinkOff()' or 'continuous()' to 
 * resume previous blinking.
 * Use 'blink(on_for, int off) to resume with new values.
 */
void Blinker::resume() {
  blink(_onForTime,_offForTime);  
}