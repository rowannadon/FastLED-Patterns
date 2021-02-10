#include <FastLED.h>

class Particle {
    public:
        int id;
        float pos;
        float lastPos;
        float vel;
        float acc;
        int lifeTime;
        int splits;

        CRGB color;

        Particle();
};

Particle::Particle() {
    vel = 0;
}