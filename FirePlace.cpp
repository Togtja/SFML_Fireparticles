#include "FirePlace.hpp"



FirePlace::FirePlace() {
    spread = 85;
    speed = 10;
    maxLife = 20;
    minLife = 5;
    points = 3;
}

FirePlace::~FirePlace() {}

void FirePlace::draw() {
    if (fireParticles.size() < 5000) {
        for (int i = 0; i < 5; i++) {
            FireParticle* fire = new FireParticle();
            createFire(*fire);
            fireParticles.push_back(fire);
        }
    }
}

void FirePlace::createFire(FireParticle& pFire) {

    pFire = FireParticle(WOODPOS, 10, sf::Vector2f(0, -1), speed, minLife, maxLife, spread, 5, 10, points);
}

void FirePlace::crackle(sf::Vector2f pos, float force) {
    for (auto& fire : fireParticles) {
        fire->Crackle(pos, force);
    }
}

std::vector<FireParticle*> FirePlace::GetFireParticles() {
    return fireParticles;
}

void FirePlace::setSpread(float spr) {
    spread = spr;
}

float FirePlace::getSpread() {
    return spread;
}

void FirePlace::setSpeed(float spe) {
    speed = spe;
}

float FirePlace::getSpeed() {
    return speed;
}

void FirePlace::setMinLife(float ml) {
    minLife = ml;
}

float FirePlace::getMinLife() {
    return minLife;
}

void FirePlace::setMaxLife(float ml) {
    maxLife = ml;
}

float FirePlace::getMaxLife() {
    return maxLife;
}

void FirePlace::incPoints() {
    if (points < 20) {
        points++;
    }
}

void FirePlace::decPoints() {
    if (points > 3) {
        points--;
    }
}
