/*
 * moodlamp-luminosity.ino
 * 
 * Created by Danilo Queiroz Barbosa, May 18, 2017.
 * Member of electronicdrops.com
 * 
 * 
 * This example shows how to use the MoodLamp library.
 * 
 * ldr with a 4.7k
 * Using map function to set the correct value 
 * 
 * 
 *long map(long x, long in_min, long in_max, long out_min, long out_max)
 *{
 *  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
 *}
 * 
 * 
 */


// class include
#include <MoodLamp.h> 


// These are the PWM pins that  control the colors.
const byte PIN_RED   = 3;
const byte PIN_GREEN = 5;
const byte PIN_BLUE  = 6;


int ldrPin = A0;


MoodLamp moodlamp(PIN_RED,PIN_GREEN,PIN_BLUE); // LAMP device. The constructor receive the pins in order RED, GREEN, BLUE.

void setup() {
  // put your setup code here, to run once:
  
  moodlamp.begin();    // set the pinModes
  moodlamp.color(COLOR_AQUA);
  Serial.begin(9600);
}

void loop() {


 int ldrValue = analogRead(ldrPin);

 Serial.println(ldrValue);

  int bright = map(ldrValue,700,980,0,100);
  bright = constrain(bright,0,100);

Serial.println(bright);
Serial.println();
  moodlamp.brightness(bright);
  // update the lamp color.
  moodlamp.update();
    

delay(100);
}
