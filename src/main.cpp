#include <Arduino.h>
#include <FastLED.h>
#include "Utils.h"
#include "Comet.h"

#define LED_PIN     2
#define NUM_LEDS    145
#define BRIGHTNESS  255
#define LED_TYPE    WS2812

CRGB leds[NUM_LEDS];
bool direction = false;
Comet* comets[128];
int stackPos = 0;
int paletteIndex = 0;

void setup() {
  delay(500);
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);

  comets[0] = new Comet(NUM_LEDS, 1, 2, 100);
}

void loop() {
  for (int i = 0; i <= stackPos; i++) {
    bool isDead = comets[i]->draw(ColorFromPalette(RainbowColors_p, random8(), 255, LINEARBLEND));
    if (isDead) {
      float s = comets[i]->position;
      float v = comets[i]->velocity;
      stackPos++;
      Serial.println(stackPos);
      comets[i] = new Comet(NUM_LEDS, s, (v*-1)-1, 100);
      comets[stackPos] = new Comet(NUM_LEDS, s, 1+v, 100);
    }
  }
  
  paletteIndex++;
  fadeToBlackBy(leds, NUM_LEDS, 60);
  FastLED.show();
  delay(10);
}