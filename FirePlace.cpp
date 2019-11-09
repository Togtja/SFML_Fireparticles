#include "FirePlace.hpp"



FirePlace::FirePlace() {}

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

    pFire = FireParticle(WOODPOS, 10, sf::Vector2f(0, -1), 10, 5, 20, 90, 5, 10, 3);
}

void FirePlace::crackle(sf::Vector2f pos, float force) {
    for (auto& fire : fireParticles) {
        fire->Crackle(pos, force);
    }
}

std::vector<FireParticle*> FirePlace::GetFireParticles() {
    return fireParticles;
}