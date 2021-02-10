#include <FastLED.h>

class Bar {
        int num;
        int lastHeight;
    public:
        int position;
        float height;
        CRGB color;
        Bar(int, int, float, CRGB);
        void draw();
        void setHeight(int);
};

Bar::Bar(int NUM_LEDS, int startPosition, float startHeight, CRGB startColor) {
    position = startPosition;
    height = startHeight;
    color = startColor;
    num = NUM_LEDS;
}

void Bar::draw() {
    drawPixels(position, position+height, color);
}

void Bar::setHeight(int h) {
    lastHeight = height;
    height = h;
}