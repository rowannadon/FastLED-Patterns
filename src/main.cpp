#include <Arduino.h>
#include <FastLED.h>
#include "Utils.h"
#include "ParticleContainer.h"

#define LED_PIN     2
#define NUM_LEDS    145
#define BRIGHTNESS  8
#define LED_TYPE    WS2812

CRGB leds[NUM_LEDS];
ParticleContainer p(32);


void setup() {
  delay(500);
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
}

void loop() {
  long c = 0;
  while (true) {
    if (c % random8() == 0) {
      p.emit(1, 3.2, -0.05, random8(), ColorFromPalette(HeatColors_p, random8(), 255, LINEARBLEND), 2);
    }
    p.update();
    p.render();
    c++;

    fadeToBlackBy(leds, NUM_LEDS, 100);
    FastLED.show();
    delay(10);
  }
}