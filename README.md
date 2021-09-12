# LED blinking library for ESP32 (Arduino Core framework)

Simple & easy-to-use library to control blink rates of LEDs. Uses Tickers (part of [Arduino core for ESP32](https://github.com/espressif/arduino-esp32)), which uses the ESP32 `SDK timer API`. 

## Usage

```C++
#include "Blinker.h"
#include "Ticker.h

#define BLINKER_PIN 10

#define ON_TIME 1.0f
#define OFF_TIME 0.5f

Blinker myBlinker(BLINKER_PIN);

Ticker changer;

void changeUp1(){
    myBlinker.snapshot();
    myBlinker.continuousOn();
}

void changeUp2(){
    myBlinker.resume(); //resume blink pattern snapped in changeup1
}

void setup(){
    myBlinker.blink(ON_TIME,OFF_TIME);
    changer1.once(10,changeUp1);
    changer2.once(20,changeUp2);
}

void loop(){
    //dont need to anything here with millis() and wotnot. 
}
```

## Todos

 - Put code above in `examples/` and make sure it runs!!
 - LED groups with 'in turn', 'simultaneous' etc modes
 - Blink patterns 
 - additional `n` parameter for number of blinks, with callback when done. 

