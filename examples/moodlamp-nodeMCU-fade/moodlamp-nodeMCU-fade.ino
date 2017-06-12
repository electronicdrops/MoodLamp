/*
 * moodlamp-NodeMCU-fade.ino
 * 
 * Created by Danilo Queiroz Barbosa, May 18, 2017.
 * Member of electronicdrops.com
 * 
 * This example shows how to use the MoodLamp library.
 * 
 * In this sketch the fade function is set.
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

  moodlamp.color(COLOR_VIOLET); // it's possible to set the color
  
  moodlamp.fade(1);   // activate the fade function
  moodlamp.fade_speed(60); // it's possible to set the fade color.
}

void loop() {

  // update the lamp color.
  moodlamp.update();
    

}
