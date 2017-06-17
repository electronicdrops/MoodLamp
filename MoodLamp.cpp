#include "Arduino.h"
#include "MoodLamp.h"



MoodLamp::MoodLamp(byte pin_red, byte pin_green, byte pin_blue){

  _pin_red    = pin_red;
  _pin_green  = pin_green;
  _pin_blue   = pin_blue;
  _color      = DEFAULT_COLOR;
  _brightness = DEFAULT_BRIGHTNESS;
  _last_brightness = _brightness;
}


void MoodLamp::begin(){

  pinMode(_pin_red,  OUTPUT);
  pinMode(_pin_green,OUTPUT);
  pinMode(_pin_blue, OUTPUT);

  digitalWrite(_pin_red,  LOW);
  digitalWrite(_pin_green,LOW);
  digitalWrite(_pin_blue, LOW);

  _wheel_time = 0;
  _fade_time = 0;
  _fade_offset = 0;
  _fade_min = 10;


  wheel(0);
  fade(0);
  fade_speed(DEFAULT_FADE_SPEED);
  wheel_speed(DEFAULT_WHEEL_SPEED);


}


int MoodLamp::color(){
  return _color;
}

int MoodLamp::color(int color){

  if ((color < 0) || (color > 360)){
    return -1;
  }

  _color = color;
  return _color;
}


int MoodLamp::brightness(){
  return _brightness;
}

int MoodLamp::brightness(int brightness){

  if ((brightness < 0) || (brightness > 100)){
    return -1;
  }
  _brightness = brightness;
  return _brightness;
}

int MoodLamp::last_brightness(){
  return _last_brightness;
}

int MoodLamp::last_brightness(int brightness){

  _last_brightness = brightness;
  return _last_brightness;
}

boolean MoodLamp::wheel(){
  return _wheel_state;
}
boolean MoodLamp::wheel(int state){

  if((state < 0) || (state > 1)){
    return false;
  }

  _wheel_state = state;
  return true;
}

int MoodLamp::wheel_speed(int speed){

  if((speed < MIN_WHEEL_SPEED) or (speed > MAX_WHEEL_SPEED)){
    return -1;
  }

  _wheel_speed = speed;
  return _wheel_speed;
}

int MoodLamp::wheel_speed(){
  return _wheel_speed;
}

boolean MoodLamp::fade(){
  return _fade_state;
}

boolean MoodLamp::fade(int state){

  if((state < 0) || (state > 1)){
    return false;
  }

  _fade_state = state;
  return true;
}



int MoodLamp::fade_speed(int speed){

  if((speed < MIN_FADE_SPEED) || (speed > MAX_FADE_SPEED)){
    return -1;
  }

  _fade_speed = speed;
  return _fade_speed;
}

int MoodLamp::fade_speed(){
  return _fade_speed;
}





void MoodLamp::update_color(){

 int color_ = map(color(), 0, 360, 0, 255);
 int brightness_ = map(brightness(), 0, 100, 0, 255);

  // Caso especial para 255, sera usado para a cor branca, e por isso eh necessario tratar o brightness diferente
  // inverto o brightness e subtraio esse valor das cores RGB do sistema.
  if (color_ == 255) {
    int aux_brightness = map(brightness_, 0, 255, 255, 0);

    _red   = 255 - aux_brightness;
    _green = 255 - aux_brightness;
    _blue  = 255 - aux_brightness;

  } else {
    hueToRGB(color_, brightness_); // caso nao for branca chama a funcao hueToRGB para atualizar os valores das variaveis

  }

  // Escrevo os valores nos pinos.
  analogWrite(_pin_red,   _red);
  analogWrite(_pin_green, _green);
  analogWrite(_pin_blue,  _blue);

}



void MoodLamp::update_color(int color_, int brightness_){


  color(color_);
  brightness(brightness_);

  color_ = map(color(), 0, 360, 0, 255);
  brightness_ = map(brightness(), 0, 100, 0, 255);

  // Caso especial para 255, sera usado para a cor branca, e por isso eh necessario tratar o brightness diferente
  // inverto o brightness e subtraio esse valor das cores RGB do sistema.
  if (color_ == 255) {
    int aux_brightness = map(brightness_, 0, 255, 255, 0);

    _red   = 255 - aux_brightness;
    _green = 255 - aux_brightness;
    _blue  = 255 - aux_brightness;

  } else {
    hueToRGB(color_, brightness_); // caso nao for branca chama a funcao hueToRGB para atualizar os valores das variaveis

  }

  // Escrevo os valores nos pinos.
  analogWrite(_pin_red,   _red);
  analogWrite(_pin_green, _green);
  analogWrite(_pin_blue,  _blue);

}


void MoodLamp::update(){

  if(wheel() == 1){
    color_wheel();
  }

  if(fade() == 1){
    color_fade();
  }
  update_color();
}




void MoodLamp::color_wheel() {

  int color_;

  if (millis() - _wheel_time > (unsigned long)wheel_speed()) {

    color_ = color();
    color_++;
    color_ = color_ % 359;

    color(color_);
    _wheel_time  = millis();

    //update_color();
  }

}


void MoodLamp::color_fade() {

 int brightness_;

if (millis() - _fade_time > (unsigned long)fade_speed()) {
 
 

 brightness_ = -abs(_fade_offset-100)+100;

  if(brightness_ < _fade_min){
   brightness_ = _fade_min;
   _fade_offset = 100 - abs(brightness_ - 100);
 }

 brightness(brightness_);
 _fade_time = millis();
 _fade_offset++;
 _fade_offset %= 200;

}

}

void MoodLamp::hueToRGB(int hue, int brightness) {

  unsigned int scaleHue = (hue * 6);
  unsigned int segment = scaleHue / 256;
  unsigned int segmentOffset = scaleHue - (segment * 256);

  unsigned int complement = 0;
  unsigned int prev = (brightness * (255 - segmentOffset)) / 256;
  unsigned int next = (brightness * segmentOffset) / 256;

  if (_invert) {
    brightness = 255 - brightness;
    complement = 255;
    prev = 255 - prev;
    next = 255 - next;
  }


  switch (segment) {
    case 0: //red
      _red = brightness;
      _green = next;
      _blue = complement;
      break;
    case 1: // yellow
      _red = prev;
       _green= brightness;
      _blue = complement;
      break;
    case 2: // green
    _red = complement;
      _green = brightness;
      _blue = next;
      break;
    case 3: // cyan
     _red= complement;
      _green = prev;
      _blue = brightness;
      break;
    case 4: // blue;
      _red = next;
      _green = complement;
      _blue = brightness;
      break;
    case 5: // magenta
      _red= brightness;
      _green = complement;
      _blue = prev;
      break;
  }


  #if defined(PWMRANGE)

  _red =   map(_red,  0,255,0,PWMRANGE);
  _green = map(_green,0,255,0,PWMRANGE);
  _blue =  map(_blue, 0,255,0,PWMRANGE);


  #endif




}
