#ifndef MOODLAMP_H
#define MOODLAMP_H

#endif

#include "Arduino.h"

/*
 * MoodLamp -
 *
 * This device controls an RGB LED, for mutiple purposes.
 *
 * The device's color follows an circular pattern, it means, that the colors
 * vary form 0 to 360.
 *
 *  The available functions are:
 *
 *  - choose color by value : 0 - 360.   0 - red.  360 - white
 *  - choose brightness: 0 - 100.  0 - led off
 *
 *  - color transition effect. wheel.
 *  - it is possible to change the transition speed: from 0 to 100
 *
 *  - fade effect
 *  - it is possible to chance the fade speed from  0 to 10000
 *
 *  This device controls 3 PWM ports that change the colors
 *
*/
  /*

   COLORS CONSTANT
*/
  const byte  COLOR_RED      = 0;
  const byte  COLOR_ORANGE   = 30;
  const byte  COLOR_YELLOW   = 60;
  const byte  COLOR_LIME     = 90;
  const byte  COLOR_GREEN    = 120;
  const byte  COLOR_AQUA     = 150;
  const byte  COLOR_CYAN     = 180;
  const byte  COLOR_OCEAN    = 210;
  const byte  COLOR_BLUE     = 240;
  const byte  COLOR_PURPLE   = 255;
  const short  COLOR_VIOLET  = 270;
  const short  COLOR_MAGENTA = 300;
  const short  COLOR_PINK    = 330;
  const short  COLOR_WHITE   = 360;


  const int MIN_WHEEL_SPEED = 0;
  const int MAX_WHEEL_SPEED = 1000;
  const int DEFAULT_WHEEL_SPEED = 100;

  const int MIN_FADE_SPEED = 0;
  const int MAX_FADE_SPEED = 10000;
  const int DEFAULT_FADE_SPEED = 200;

  const int DEFAULT_COLOR = 360;
  const int DEFAULT_BRIGHTNESS = 100;



class MoodLamp{

  private:
    int _red;
    int _green;
    int _blue;
    int  _color;
    boolean _invert = false;
    int _brightness;
    int _last_brightness;
    int _last_color;

    byte _wheel_state;
    int  _wheel_speed;
    long _wheel_time;

    byte _fade_state;
    byte _fade_speed;
    long _fade_time;
    int _fade_offset;
    int _fade_min;


    byte _pin_red;
    byte _pin_green;
    byte _pin_blue;

    void hueToRGB(int hue, int brightness);
    void color_wheel();
    void color_fade();

  public:
    MoodLamp(byte pin_red, byte pin_green, byte pin_blue);
    void begin();

    int color();
    int color(int color_);
    int brightness();
    int brightness(int brightness_);
    int last_brightness();
    int last_brightness(int brightness_);
    boolean wheel();
    boolean wheel(int state);
    int wheel_speed();
    int wheel_speed(int speed);
    boolean fade();
    boolean fade(int state);
    int fade_speed();
    int fade_speed(int speed);

    void update_color();
    void update_color(int color_, int brightness_);


    void update();

};
