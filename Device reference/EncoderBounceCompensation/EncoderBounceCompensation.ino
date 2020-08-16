#include <FastLED.h>
#include <Encoder.h>

Encoder knob(6,7);


void setup() 
{ 
  Serial.begin(9600);
}

int knobPosition = 0;

void loop() 
{ 
    int newKnob = (knob.read() / 3 * 5 );
    if (newKnob != knobPosition)
      {
        Serial.print(newKnob);
        knobPosition = newKnob;
      }
    else if (newKnob >= 30);
      {
        newKnob = 0;
        Serial.print(newKnob);
      }*/
}
