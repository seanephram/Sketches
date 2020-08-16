#include <FastLED.h>

#define PinA  8
#define PinB  9
#define LED_TYPE  WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  50

#define NUM_LEDS_PER_STRIP 5
#define NUM_STRIPS 2

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

int fadeAmount = 5;
int brightness = 0;

CRGB  leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

int scales [] = {255, 0, 150, 0, 150, 0, 100, 0};
uint8_t hue = 50;
uint8_t sat = 0;
uint8_t val = 255;

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
      for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
        {
          FastLED.showColor(CHSV(hue, sat, val), scales[0]);
          delay(1000); //global speed

            for(int i = 1; i < COUNT_OF(scales); i++) 
              {
                FastLED.showColor(CHSV(hue, sat, val), scales[i]);
                delay(40); // flicker speed
              }
          delay(60); //length of color stay // code for strip a
        }
    }
    delay(500); // delay between strips
  for (int x = 1; x < 2; x++)
    {
      for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
        {
          FastLED.showColor(CHSV(hue, sat, val), scales[0]);
          delay(1000); //global speed

            for(int i = 1; i < COUNT_OF(scales); i++) 
              {
                FastLED.showColor(CHSV(hue, sat, val), scales[i]);
                delay(40); // flicker speed
              }
          delay(60); //length of color stay // code for strip b
        }
    }
}
