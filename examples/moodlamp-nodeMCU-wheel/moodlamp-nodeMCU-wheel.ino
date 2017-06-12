/*
 * moodlamp-wheel.ino
 * 
 * Created by Danilo Queiroz Barbosa, May 18, 2017.
 * Member of electronicdrops.com
 * 
 * This example shows how to use the MoodLamp library.
 * 
 * In this sketch the wheel function is set. Passing through all colors.
 * 
 * 
 */


// class include
#include <MoodLamp.h> 


// These are the PWM pins that  control the colors.
// THESE ARE THE PWM PINS FOR ESP8266 NODEMCU modules
const byte PIN_RED   = D1;
const byte PIN_GREEN = D2;
const byte PIN_BLUE  = D3;



MoodLamp moodlamp(PIN_RED,PIN_GREEN,PIN_BLUE); // LAMP device. The constructor receive the pins in order RED, GREEN, BLUE.

void setup() {
  // put your setup code here, to run once:
  
  moodlamp.begin();    // set the pinModes
  
  moodlamp.wheel(1);   // wheel function.
}

void loop() {

  // update the lamp color.
  moodlamp.update();    

}
