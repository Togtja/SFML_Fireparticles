#pragma once
#include <vector>
#include  "FireParticle.hpp"
class FirePlace {
private:
    std::vector<FireParticle*> fireParticles;
public:
    FirePlace();
    ~FirePlace();
    void draw();
    void createFire(FireParticle& pFire);
    void crackle(sf::Vector2f pos, float force);
    std::vector<FireParticle*> GetFireParticles();
};