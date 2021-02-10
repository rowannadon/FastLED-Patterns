#include <Arduino.h>
#include <FastLED.h>

void drawPixels(int start, int end, CRGB color) {
    for (int i = min(start,end); i < max(start,end); i++) {
        FastLED.leds()[i] = color;
    }
}