#include "FastLED.h"
#define LED_TYPE    WS2812B 
#define COLOR_ORDER GRB
#define DATA_PIN 2 
#define NUM_LEDS 21
#define BRIGHTNESS 100
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#define FRAMES_PER_SECOND  120


CRGB leds[NUM_LEDS];

int scales [] = {255, 0, 150, 0, 150, 0, 100, 0}; // flicker iteration

static float pulseSpeed = random(0.5, 2.0);  // Larger value gives faster pulse.

uint8_t hueA = 359 ;  // Start hue at valueMin.
uint8_t satA = 0;  // Start saturation at valueMin.
float valueMin = 170.0;  // Pulse minimum value (Should be less then valueMax).

uint8_t hueB =  100;  // End hue at valueMax.
uint8_t satB = 0;  // End saturation at valueMax.
float valueMax = 255.0;  // Pulse maximum value (Should be larger then valueMin).

uint8_t hue = hueA;  // Do Not Edit
uint8_t sat = satA;  // Do Not Edit
float val = valueMin;  // Do Not Edit
uint8_t hueDelta = hueA - hueB;  // Do Not Edit
static float delta = (valueMax - valueMin) / 2.35040238;  // Do Not Edit

void setup()
  {
    delay(3000); // 3 second delay for recovery
    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS); 

  }

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {flicker, pulse};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
//uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop()
  {
    float dV = ((exp(sin(pulseSpeed * millis()/2000.0*PI)) -0.36787944) * delta);
    val = valueMin + dV;
    hue = map(val, valueMin, valueMax, hueA, hueB);  // Map hue based on current val
    sat = map(val, valueMin, valueMax, satA, satB);  // Map sat based on current val

    gPatterns[gCurrentPatternNumber]();

    FastLED.show();  
    FastLED.delay(1000/FRAMES_PER_SECOND); 

    //EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
    EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
    
  }

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void flicker() 
  {
    uint8_t hue = 50;
    uint8_t sat = 0;
    uint8_t val = 100;

    FastLED.showColor(CHSV(hue, sat, val), scales[0]);
    delay(10); //global speed
    
    for(int s = 1; s < COUNT_OF(scales); s++) 
      {
        FastLED.showColor(CHSV(hue, sat, val), scales[s]);
        delay(40); // flicker speed
      }

    delay(60); //length of color stay 
}

void pulse()
  {
    for (int i = 0; i < NUM_LEDS; i++) 
      {
        leds[i] = CHSV(hue, sat, val);
      }
  }
