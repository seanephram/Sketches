#include "FastLED.h"
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define MASTER_BRIGHTNESS 255

#define DATA_PIN_A 8  // update pin numbers for data lines as needed
#define DATA_PIN_B 9
#define DATA_PIN_C 10
#define DATA_PIN_D 11
#define DATA_PIN_D 12


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
  FastLED.setBrightness(MASTER_BRIGHTNESS);
  FastLED.clear();
  Serial.println("Setup done.");
}//end_setup


/*********************************************************************/
void loop() {

    fill_solid(ledsA, NUM_LEDS_A, CRGB::Red);
    fill_solid(ledsB, NUM_LEDS_B, CRGB::Green);
    FastLED.show();
  }

  //------code for the second strip, ledsB here------
  // Putting the ledsB pattern inside this EVERY_N section allows
  // the speed for just this strip to be individually adjusted.
  // This will run every 500 milliseconds.
  // Use ledsB in this section, such as ledsB[i], and NUM_LEDS_B
  // with for loops so it uses the correct length of strip B.
  // For example:
