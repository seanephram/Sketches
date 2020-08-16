#include "FastLED.h"
#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN   2
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    21

CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

//my code

int scales [] = {255, 0, 150, 0, 150, 0, 100, 0}; // flicker iteration
static float pulseSpeed = random(0.5, 2);  // Larger value gives faster pulse.

uint8_t hueA = 359 ;  // Start hue at valueMin.
uint8_t satA = 0;  // Start saturation at valueMin.
float valueMin = 170.0;  // Pulse minimum value (Should be less then valueMax).

uint8_t hueB =  100;  // End hue at valueMax.
uint8_t satB = 0;  // End saturation at valueMax.
float valueMax = 250.0;  // Pulse maximum value (Should be larger then valueMin).

uint8_t hue = hueA;  // Do Not Edit
uint8_t sat = satA;  // Do Not Edit
float val = valueMin;  // Do Not Edit
uint8_t hueDelta = hueA - hueB;  // Do Not Edit
static float delta = (valueMax - valueMin) / 2.35040238;  // Do Not Edit

// List of patterns to cycle through.  Each is defined as a separate function below.

typedef void (*SimplePattern)();
typedef SimplePattern SimplePatternList[];
typedef struct { SimplePattern mPattern;  uint16_t mTime; } PatternAndTime;
typedef PatternAndTime PatternAndTimeList[];

// These times are in seconds, but could be changed to milliseconds if desired;
// there's some discussion further below.

// If you want the playlist to loop forever, set this to true.
// If you want the playlist to play once, and then stay on the final pattern 
// until the playlist is reset, set this to false.
bool gLoopPlaylist = true;

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  
  RestartPlaylist();
  Serial.begin(57600);
}


uint8_t gCurrentTrackNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
bool gRestartPlaylistFlag = false;

const PatternAndTimeList gPlaylist = { 
  { pulse,              random(10, 15) },
  { flicker,             0.05 }
};

void loop()
{
  // for pulse
  float dV = ((exp(sin(pulseSpeed * millis()/2000.0*PI)) -0.36787944) * delta);
  val = valueMin + dV;
  hue = map(val, valueMin, valueMax, hueA, hueB);  // Map hue based on current val
  sat = map(val, valueMin, valueMax, satA, satB);  // Map sat based on current val
  
  // Call the current pattern function once, updating the 'leds' array
  gPlaylist[gCurrentTrackNumber].mPattern();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // For demo purposes, restart the playlist any time we read
  // the letter "r" character from the serial port.  Type "r" into 
  // the Arduino serial monitor and press return to restart the playlist.
  // In practice, you could have this check a 'restart' button, or something similar.
  if( Serial.read() == 'r') RestartPlaylist();

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow

  // Here's where we do two things: switch patterns, and also set the
  // 'virtual timer' for how long until the NEXT pattern switch.
  //
  // Instead of EVERY_N_SECONDS(10) { nextPattern(); }, we use a special
  // variation that allows us to get at the pattern timer object itself,
  // and change the timer period every time we change the pattern.
  //
  // You could also do this with EVERY_N_MILLISECONDS_I and have the 
  // times be expressed in milliseconds instead of seconds.
  {
    EVERY_N_SECONDS_I(patternTimer,gPlaylist[gCurrentTrackNumber].mTime) { 
      nextPattern(); 
      patternTimer.setPeriod( gPlaylist[gCurrentTrackNumber].mTime);
    }

    // Here's where we handle restarting the playlist if the 'reset' flag
    // has been set. There are a few steps:  
    if( gRestartPlaylistFlag ) {
      
      // Set the 'current pattern number' back to zero
      gCurrentTrackNumber = 0;
      
      // Set the playback duration for this patter to it's correct time
      patternTimer.setPeriod( gPlaylist[gCurrentTrackNumber].mTime);
      // Reset the pattern timer so that we start marking time from right now
      patternTimer.reset();
      
      // Finally, clear the gRestartPlaylistFlag flag
      gRestartPlaylistFlag = false;
    }
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number
  gCurrentTrackNumber = gCurrentTrackNumber + 1;
  
  // If we've come to the end of the playlist, we can either 
  // automatically restart it at the beginning, or just stay at the end.
  if( gCurrentTrackNumber == ARRAY_SIZE( gPlaylist) ) {
    if( gLoopPlaylist == true) {
      // restart at beginning
      gCurrentTrackNumber = 0;
    } else {
      // stay on the last track
      gCurrentTrackNumber--;
    }
  }
}

void RestartPlaylist()
{
  gRestartPlaylistFlag = true;
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
        delay(random(30, 40)); // flicker speed
      }

    delay(random(45, 60)); //length of color stay 
}

void pulse()
  {
    for (int i = 0; i < NUM_LEDS; i++) 
      {
        leds[i] = CHSV(hue, sat, val);
      }
  }
