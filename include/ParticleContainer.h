#include "Particle.h"

class ParticleContainer {
    public:
        Particle* particles;
        int maxParticles;
        int numAliveParticles;

        ParticleContainer(int maxParticles);
        void emit(float, float, float, int, CRGB, int);
        void kill(int);
        void update();
        void render();
};

ParticleContainer::ParticleContainer(int mp) {
    maxParticles = mp;
    particles = new Particle[maxParticles];
}

void ParticleContainer::emit(float p, float v, float a, int life, CRGB c, int s) {
    particles[numAliveParticles].pos = p;
    particles[numAliveParticles].lastPos = p;
    particles[numAliveParticles].vel = v;
    particles[numAliveParticles].acc = a;
    particles[numAliveParticles].lifeTime = life;
    particles[numAliveParticles].color = c;//(c/4)*(s+1);
    particles[numAliveParticles].splits = s;
    numAliveParticles++;
    Serial.println("new particle created...");
}

void ParticleContainer::kill(int index) {
    particles[index] = particles[numAliveParticles-1];
    numAliveParticles--;
}

void ParticleContainer::update() {
    Serial.println("-------------------");
    for (int i = 0; i < numAliveParticles; i++) {
        Serial.print("particle: ");
        Serial.print(i);
        Serial.print(", position: ");
        Serial.println(particles[i].pos);

        particles[i].lastPos = particles[i].pos;
        particles[i].pos += particles[i].vel;
        particles[i].vel += particles[i].acc;
        particles[i].lifeTime--;

        if (particles[i].pos < 0) {
            particles[i].vel *= -1;
        } else if (particles[i].pos > 144) {
            //particles[i].vel *= -1;
            kill(i);
        }

        if (particles[i].lifeTime < 0) {
            kill(i);
            if (particles[i].splits > 0) {
                emit(particles[i].pos, particles[i].vel, 0, 50, ColorFromPalette(HeatColors_p, random8(), 255, LINEARBLEND), particles[i].splits-1);
            }
        }
    }
}

void ParticleContainer::render() {
    for (int i = 0; i < numAliveParticles; i++) {
        drawPixels(constrain(particles[i].lastPos, 0, 144), constrain(particles[i].pos, 0, 144), particles[i].color);
    }
}