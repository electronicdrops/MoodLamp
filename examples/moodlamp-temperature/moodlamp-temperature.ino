/*
 * moodlamp-temperature.ino
 * 
 * 20170520-000
 * created by Danilo Queiroz Barbosa
 * member of Electronicdrops
 * 
 * The color of the lamp changes according to the measured temperature
 * Using a Dallas18S20 sensor
 */



#include <OneWire.h>
#include <DallasTemperature.h>
#include <MoodLamp.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// moodlamp device using PWM Pins 3,5 and 6
MoodLamp moodlamp(3,5,6);

void setup() {
  // put your setup code here, to run once:
  
    sensors.begin();
    moodlamp.begin();
    

}

void loop() {
  sensors.requestTemperatures(); 
  // put your main code here, to run repeatedly:
  float temp = sensors.getTempCByIndex(0);

  // this function let the led color to stay from blue to red.
  float f_color = 240.0 - 6.0* temp;
  int color = (int) f_color;

  // changing the color of the device and update.
  moodlamp.color(color);
  moodlamp.update();
  

delay(100);
}
