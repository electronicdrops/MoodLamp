# MoodLamp
This is a simple Arduino Library that controls any RGB Led through 3 PWM Pins.

With an RGB Led you could create best light projects. But not only this, you could use and RGB Led to test a lot of sensor and other things with microcontrollers.

The idea of this library is to let your code clean, and provide a variet of functions to control your projects.

In this repository you will find a series of examples how to use MoodLamp.

## Steps:

1. Download the Library or clone it.
2. Open Arduino IDE and go to menu : Sketch > Include Library > Add .zip library. Then choose the downloaded file
3. See the Library examples that come with the library: File > Examples > MoodLamp


## Basics

To use this library in a new project do this:

- Include the library

``` c++
#include <MoodLamp.h>

```

- Define what PWM pins will control the led
``` c++
const byte PIN_RED   = 3;
const byte PIN_GREEN = 5;
const byte PIN_BLUE  = 6;
```

- Create the object passing the pins
``` c++
MoodLamp moodlamp(PIN_RED,PIN_GREEN,PIN_BLUE);
```

- on setup() function uses the begin() function to initialize the object
``` c++
void setup() {
  // put your setup code here, to run once:
  
  moodlamp.begin();    // set the pinModes
  
}
```

- You could set the main function of the object on setup() too. This examples sets the wheel() function to change the color over time

``` c++
void setup() {
  // put your setup code here, to run once:
  
  moodlamp.begin();    // set the pinModes
  moodlamp.wheel(1);   // wheel function. 
}
 ```

- in the loop() function, uses update() 

``` c++
void loop() {

  // update the lamp color.
  moodlamp.update();    

}
```

This is a basic example of how to use the library.

You could change the color using

``` c++
moodlamp.color(COLOR_CYAN);
```

Change the brightness

``` c++
moodlamp.brightness(50);
```

Or use the fade function

``` c++
moodlamp.fade(1)
```

And it's possible to change the speed of the function

``` c++
moodlamp.fade_speed(30);
```

To see more information about all the library functions please see the Wiki.

Thanks
 

