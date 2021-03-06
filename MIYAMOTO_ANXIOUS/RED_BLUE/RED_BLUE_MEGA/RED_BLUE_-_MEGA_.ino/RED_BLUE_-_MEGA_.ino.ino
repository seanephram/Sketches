#include "FastLED.h"
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define MASTER_BRIGHTNESS 255

#define DATA_PIN_A 33  // update pin numbers for data lines as needed
#define DATA_PIN_B 37
#define DATA_PIN_C 41
#define DATA_PIN_D 45
#define DATA_PIN_E 49

#define NUM_LEDS_A 62  // adjust number of pixels as needed
#define NUM_LEDS_B 62
#define NUM_LEDS_C 62
#define NUM_LEDS_D 62
#define NUM_LEDS_E 62

CRGB ledsA[NUM_LEDS_A];
CRGB ledsB[NUM_LEDS_B];
CRGB ledsC[NUM_LEDS_C];
CRGB ledsD[NUM_LEDS_D];
CRGB ledsE[NUM_LEDS_E];

/*********************************************************************/
void setup() {
  Serial.begin(115200);  //allow for output to serial monitor
  delay(2500);  //power up delay
  FastLED.addLeds<LED_TYPE, DATA_PIN_A, COLOR_ORDER>(ledsA, NUM_LEDS_A);
  FastLED.addLeds<LED_TYPE, DATA_PIN_B, COLOR_ORDER>(ledsB, NUM_LEDS_B);
  FastLED.addLeds<LED_TYPE, DATA_PIN_C, COLOR_ORDER>(ledsC, NUM_LEDS_C);
  FastLED.addLeds<LED_TYPE, DATA_PIN_D, COLOR_ORDER>(ledsD, NUM_LEDS_D);
  FastLED.addLeds<LED_TYPE, DATA_PIN_E, COLOR_ORDER>(ledsE, NUM_LEDS_E);
  FastLED.setBrightness(MASTER_BRIGHTNESS);
  FastLED.clear();
  Serial.println("Setup done.");
}//end_setup


/*********************************************************************/
void loop() {

    fill_solid(ledsA, NUM_LEDS_A, CRGB::Red);
    fill_solid(ledsB, NUM_LEDS_B, CRGB::Blue);
    fill_solid(ledsC, NUM_LEDS_C, CRGB::Red);
    fill_solid(ledsD, NUM_LEDS_D, CRGB::Blue);
    fill_solid(ledsE, NUM_LEDS_E, CRGB::Red);
    FastLED.show();
  }



  //------code for the second strip, ledsB here------
  // Putting the ledsB pattern inside this EVERY_N section allows
  // the speed for just this strip to be individually adjusted.
  // This will run every 500 milliseconds.
  // Use ledsB in this section, such as ledsB[i], and NUM_LEDS_B
  // with for loops so it uses the correct length of strip B.
  // For example:
