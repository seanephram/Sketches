#include <FastLED.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    5
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    48
#define buttonPin   2
#define FRAMES_PER_SECOND 250
#define BACKLIGHT PIN 13
#define BRIGHTNESS         40

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); /* FOR LCD: SDA PINA4; SCL PIN A5 */

CRGB leds[NUM_LEDS];

void fadeall() 
  { 
  for(int i = 0; i < NUM_LEDS; i++) 
  { leds[i].nscale8(230); } 
  }

void setup() {
  delay(100); // 3 second delay for recovery
  pinMode (buttonPin,  INPUT_PULLUP);
  lcd.begin(16,2);
  patternDisplay();
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { HueFadeReset, FadePulseGlow, sinelon, juggle, bpm, cylon };

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
    lcd.clear();
    patternDisplay();
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void patternDisplay()
{
  switch(gCurrentPatternNumber)
    {
        lcd.clear();
      case  0:  lcd.print("HueFadeReset");
        break;
        lcd.clear();
      case  1:  lcd.print("FadePulseGlow");
        break;
        lcd.clear();
      case  2:  lcd.print("sinelon");
        break;
        lcd.clear();
      case  3:  lcd.print("bpm");
        break;
        lcd.clear();
      case  4:  lcd.print("juggle");
        break;
        lcd.clear();
      case  5:  lcd.print("cylon");
        break;
        lcd.clear();
      default:
        lcd.clear();
    }
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void HueFadeReset() 
{
   // Let's take 256 steps to get from blue to red
  // (the most possible with an LED with 8 bit RGB values)

  for( int colorStep=0; colorStep<256; colorStep++ ) {

      int r = colorStep;  // Redness starts at zero and goes up to full
      int b = 255-colorStep;  // Blue starts at full and goes down to zero
      int g = 0;              // No green needed to go from blue to red

      // Now loop though each of the LEDs and set each one to the current color

      for(int x = 0; x < NUM_LEDS; x++){
          leds[x] = CRGB(r,g,b);
      }



      // Display the colors we just set on the actual LEDs
      FastLED.show();

      delay(10); 
}

}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void FadePulseGlow() 
{
  int fadeAmount = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
  int brightness = 0;
  for(int i = 0; i < NUM_LEDS; i++ )
   {
   leds[i].setRGB(0,255,250);  // Set Color HERE!!!
   leds[i].fadeLightBy(brightness);
  }
  FastLED.show();
  brightness = brightness + fadeAmount;
  // reverse the direction of the fading at the ends of the fade: 
  if(BRIGHTNESS == 0 || BRIGHTNESS == 255)
  {
    fadeAmount = -fadeAmount ; 
  }    
  delay(9);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 40);
  int pos = beatsin16( 18, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 255);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 160;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void cylon()
    { 
      static uint8_t hue = 0;
      for(int i = 0; i < NUM_LEDS; i++) //  slide LEDs to one direction
      
        {
          leds[i] = CHSV(hue++, 255, 255);
          FastLED.show(); 
          fadeall();
          delay(10);
        }
 
      for(int i = (NUM_LEDS)-1; i >= 0; i--)   // other direction
      
        {
          leds[i] = CHSV(hue++, 255, 255);
          FastLED.show();
          fadeall();
          delay(10);
        }  
    }
