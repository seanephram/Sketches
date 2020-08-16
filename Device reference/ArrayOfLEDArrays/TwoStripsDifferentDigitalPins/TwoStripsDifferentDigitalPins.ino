#include <FastLED.h>

#define PinA  8
#define PinB  9
#define LED_TYPE  WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  50

#define NUM_LEDS_PER_STRIP 5
#define NUM_STRIPS 2

CRGB  leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

void setup() 
{
  FastLED.addLeds<LED_TYPE, PinA, COLOR_ORDER>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, PinB, COLOR_ORDER>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() 
{
  for (int x = 0; x < 1; x++) //goes over each strip
    {
      // code for strip a
    } 

    
    delay(500); // delay between strips
  for (int x = 1; x < 2; x++)
    {
      //code for strip b
    }
}
