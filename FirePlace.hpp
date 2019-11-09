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
    std::vector<FireParticle*> GetFireParticles();
};