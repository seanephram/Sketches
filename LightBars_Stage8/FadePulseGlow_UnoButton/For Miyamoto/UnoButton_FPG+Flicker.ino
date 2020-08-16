#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    8
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    70
#define buttonPin   0
#define FRAMES_PER_SECOND 250
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

CRGB leds[NUM_LEDS];

int fadeAmount = 5;
  int brightness = 0;

void fadeall() 
  { 
  for(int i = 0; i < NUM_LEDS; i++) 
  { leds[i].nscale8(230); } 
  }

void setup() {
  delay(100); // 3 second delay for recovery
  pinMode (buttonPin,  INPUT_PULLUP);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { fadePulseGlow, flicker, };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{ 
  gPatterns[gCurrentPatternNumber]();

  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND); 
  EVERY_N_MILLISECONDS( 17 ) { gHue++; }
  
  if (digitalRead(buttonPin) == LOW)
  {
    delay(500);
    nextPattern();  // change patterns periodically
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))



void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void fadePulseGlow()
{ 
   for(int i = 0; i < NUM_LEDS; i++ )
   {
   leds[i].setRGB(0,255,250);  // Set Color HERE!!!
   leds[i].fadeLightBy(brightness);
  }
  FastLED.show();
  brightness = brightness + fadeAmount;
  // reverse the direction of the fading at the ends of the fade: 
  if(brightness == 0 || brightness == 255)
  {
    fadeAmount = -fadeAmount ; 
  }    
  delay(9);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
}

void flicker() 
{
  int scales [] = {255, 0, 150, 0, 150, 0, 100, 0};
  uint8_t hue = 50;
  uint8_t sat = 0;
  uint8_t val = 255;

  FastLED.showColor(CHSV(hue, sat, val), scales[0]);
  delay(8000); //global speed

  for(int i = 1; i < COUNT_OF(scales); i++) 
      {
        FastLED.showColor(CHSV(hue, sat, val), scales[i]);
        delay(40); // flicker speed
      }

  delay(60); //length of color stay 
}
