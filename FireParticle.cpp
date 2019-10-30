#include "FireParticle.h"
#include <random>
 
std::random_device rd;
std::mt19937_64 gen(rd());

FireParticle::FireParticle(sf::Vector2f circle, float rad, sf::Vector2f dir, float dev, float minsize, float maxsize, int pointCount) {
    float size = std::uniform_real_distribution<float>(minsize, maxsize)(gen);
    particle.setRadius(size);
    particle.setPointCount(pointCount);
    //find random size between min and max;
    //particle.setRadius()
    //First find a randiom point within circle and rad
        //then find a random deviation from 0 to dev an apply it to dir}
}
void FireParticle::Tick(float dt) {
    lifetime -= dt;
    if (lifetime < 0) {
        //Murder me
        return;
    }
    pos += dir * speed;
}


FireParticle::~FireParticle() {}
