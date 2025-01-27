#include <FastLED.h>
#define LED_PIN     10
#define NUM_LEDS    25
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600); 
}

void loop() {
  int defaultGreen = 255;
  int maxRed = 255;
  int delayTime = random(10, 30); //random time for keeping LEDs on, to simulate fire-like effect
  int flickerNumber = 150; //number of flickers per drought event

  for (int i = 0; i <= NUM_LEDS; i++) { // RGB strip color set default to green
          leds[i] = CRGB(0, defaultGreen, 0);
          FastLED.show();
  }
        
  if (Serial.available() > 0) { // check if data is available in the serial buffer
      int drought_value = Serial.parseInt(); // read the value from the serial buffer
      Serial.println("drought value: " + String(drought_value));
      
      int greenValue = map(drought_value, 0, 1, defaultGreen, 60); // 0 or 1 as input values are mapped to red-green spectrum
      int redValue = map(drought_value, 0, 1, 0, maxRed);

      if (drought_value > 0) { //if there is a serial communication input value
        for (int i = 0; i <= flickerNumber; i++) {
          for (int i = 0; i <= NUM_LEDS; i++) { // have a fire-like flickering effect by slighly changing the hue of the LEDs
            leds[i] = CRGB(random(redValue-30, redValue+30), random(greenValue-35, greenValue+5), 0);
            FastLED.show();
          }
          delay(delayTime); // leave the lights on for a random amount of time
        }

        
        for (int i = 0; i <= NUM_LEDS; i++) { // reset strip to original color
          leds[i] = CRGB(0, defaultGreen, 0);
          FastLED.show();
        }
      }  
  }
}
