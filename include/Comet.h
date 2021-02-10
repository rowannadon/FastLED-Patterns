#include <FastLED.h>

class Comet {
        int num;
        int lastPosition;
    public:
        int lifeTime;
        float position;
        float velocity;

        Comet(int, float, float, int);
        bool draw(CRGB color);
};

Comet::Comet(int NUM_LEDS, float startPosition, float startVelocity, int life) {
    position = startPosition;
    velocity = startVelocity;
    num = NUM_LEDS;
    lifeTime = life;
}

bool Comet::draw(CRGB color) {
    lifeTime--;
    if (lifeTime < 0) {
        return true;
    }
    lastPosition = position;
    position += velocity;
    velocity *= 0.98;

    if (position > float(num)) {
        velocity *= -1.0;
    }
    else if (position < 0) {
        velocity *= -1.0;
    }

    drawPixels(constrain(int(position), 0, num), constrain(int(lastPosition), 0, num), color);
    return false;
}