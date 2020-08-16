#include "FastLED.h"
#define LED_TYPE    WS2812B  //WS2811, WS2812, WS2812B
#define COLOR_ORDER GRB
#define DATA_PIN 2 
#define NUM_LEDS 21
#define BRIGHTNESS 100
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
CRGB leds[NUM_LEDS];

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


//---------------------------------------------------------------
void setup(){
  //Serial.begin(115200);  // Allows serial monitor output (check baud rate)
  int scales [] = {255, 0, 150, 0, 150, 0, 100, 0}; //for flicker iteration
  delay(2000);  // Startup delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  //Serial.println("Setup done.  \n");
}


//---------------------------------------------------------------
void loop(){
  float dV = ((exp(sin(pulseSpeed * millis()/2000.0*PI)) -0.36787944) * delta);
  val = valueMin + dV;
  hue = map(val, valueMin, valueMax, hueA, hueB);  // Map hue based on current val
  sat = map(val, valueMin, valueMax, satA, satB);  // Map sat based on current val

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, sat, val);

    // You can experiment with commenting out these dim8_video lines
    // to get a different sort of look.
    leds[i].r = dim8_video(leds[i].r);
    leds[i].g = dim8_video(leds[i].g);
    leds[i].b = dim8_video(leds[i].b);
  }

  FastLED.show();
   
} // end_main_loop
