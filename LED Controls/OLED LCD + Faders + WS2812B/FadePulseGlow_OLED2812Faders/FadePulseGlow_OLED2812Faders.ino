//by Scott Kletzien
/*
Put together & tested by:
Scottie Digital
 */
#include "FastLED.h"
#define NUM_LEDS 21  // # of LEDS in the strip#define LED_PIN 2 // Output Pin to Data Line on Strip
#define COLOR_ORDER RGB  // I had to change this for my strip if your color is off then you know.
#define LED_TYPE WS2812B
#define LED_PIN 1 

//integers 

int fadeAmount = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int brightness = 0;

#define MAX_BRIGHTNESS 200      // Thats full on, watch the power!
#define MIN_BRIGHTNESS 50       // set to a minimum of 25%

// set pinout

const int brightnessInPin = A0;  // The Analog input pin that the brightness control potentiometer is attached to.
const int speedInPin = A1;       // Analog input pin that the speed control potentiometer is attached to.
const int colorInPin = A2;      // The Analog input pin that the colour control potentiometer is attached to.

//map 

   int mappedValue = map(analogRead(colorInPin), 0, 1023, 0, 255);
   
   int mappedBrighness = map(analogRead(brightnessInPin), 0, 1023, 0, 255);

// LEDs

struct CRGB leds[NUM_LEDS];

void setup()
{
  LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(MAX_BRIGHTNESS);
}

void loop()
{ 
   int mappedBrighness = map(analogRead(brightnessInPin), 0, 1023, 0, 255);
   for(int i = 0; i < NUM_LEDS; i++ )
   {
   int mappedValue = map(analogRead(colorInPin), 0, 1023, 0, 255);
   leds[i] = CHSV(mappedValue, 255, 255);
   leds[i].fadeLightBy(brightness);
  }
  FastLED.show();
  brightness = brightness + fadeAmount;
  // reverse the direction of the fading at the ends of the fade: 
  if(brightness == 0 || brightness == 255)
  {
    fadeAmount = -fadeAmount ; 
  }  
  int delayValue = map(analogRead(speedInPin), 0, 512, 0, 75);  
  delay(delayValue);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
}
