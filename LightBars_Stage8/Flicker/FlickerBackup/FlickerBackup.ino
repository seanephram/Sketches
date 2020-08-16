#include <FastLED.h>

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#define NUM_LEDS 21
#define DATA_PIN 0
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

int scales [] = {255, 0, 150, 0, 150, 0, 100, 0};

void loop() {
  uint8_t hue = 50;
  uint8_t sat = 0;
  uint8_t val = 75;

  FastLED.showColor(CHSV(hue, sat, val), scales[0]);
  delay(8000); //global speed

  for(int i = 1; i < COUNT_OF(scales); i++) {
    FastLED.showColor(CHSV(hue, sat, val), scales[i]);
    delay(40); // flicker speed
  }

  delay(60); //length of color stay 
}
