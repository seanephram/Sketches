//Libraries

#include <FastLED.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Pin assignment

#define LED_PIN 4              // which pin are LEDS connected to?
#define NUM_LEDS 70
#define COLOR_ORDER RGB
#define LED_TYPE WS2812B        // i'm using WS2811s, FastLED supports lots of different types.

//OLED Display

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define MAX_BRIGHTNESS 255      // Thats full on, watch the power!
#define MIN_BRIGHTNESS 50       // set to a minimum of 25%
#define OLED_RESET     -1 // Reset pin  (or -1 if sharing Arduino reset pin)
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Global Variables

int fadeAmount = 5; 

const int brightnessInPin = A0;  //Analog PIN: Brightness 
const int speedInPin = A1;       //Analog PIN: Speed 
const int colourInPin = A2;      //Analog PIN HUE

int brightnessInLED = 5;
int speedInLED = 6;
int colourInLED = 7;

struct CRGB leds[NUM_LEDS];

// Code

void setup() 
  {
    pinMode(brightnessInLED, OUTPUT);
    pinMode(speedInLED, OUTPUT);
    pinMode(colourInLED, OUTPUT);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(MAX_BRIGHTNESS);
  }

void loop() {

    testText();
  
// map fader to global LED brightness
  int mappedValue = map(analogRead(brightnessInPin), 0, 1023, 0, 255);

    if (mappedValue >= 50) 
      {
        digitalWrite(brightnessInLED, HIGH);
      }
    else
      {
        digitalWrite(brightnessInLED, LOW);
      }
  FastLED.setBrightness(constrain(mappedValue, MIN_BRIGHTNESS, MAX_BRIGHTNESS));

  // read the analog speed value:     
  // map it to a value used in delay();
  int delayValue = map(analogRead(speedInPin), 0, 1023, 0, 50);  

  int mappedHue;
  // read the analog brightness value:
  //int hueValue = analogRead(colourInPin);            
  // map it to the range of the FastLED brightness:

    // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) 
    {
      mappedHue = map(analogRead(colourInPin), 0, 1023, 0, 255);
    // Set the i'th led to the chosen colour
      leds[i] = CHSV(mappedHue, 255, 255);
    // Show the leds
      FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
      leds[i] = CRGB::Black;  
    }
  // Now go in the other direction.  
  for(int i = NUM_LEDS-1; i >= 0; i--) 
    {
      mappedHue = map(analogRead(colourInPin), 0, 1023, 0, 255);
    // Set the i'th led to the chosen colour 
      leds[i] = CHSV(mappedHue, 255, 255);
    // Show the leds
      FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
      leds[i] = CRGB::Black;
    // Wait a little bit before we loop around and do it again
    }
}

void testText()
  {
    display.clearDisplay();
    display.setTextSize(3); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 0);
    display.println(F("test"));
    display.display();      // Show initial text
      delay(100);
      
  // Scroll in various directions, pausing in-between:
    display.startscrollright(0x00, 0x0F);
      delay(300);
    display.stopscroll();
      delay(300);
    display.startscrollleft(0x00, 0x0F);
      delay(300);
    display.stopscroll();
      delay(300);
    display.startscrolldiagright(0x00, 0x07);
      delay(300);
    display.startscrolldiagleft(0x00, 0x07);
      delay(300);
    display.stopscroll();
      delay(300);
  }
