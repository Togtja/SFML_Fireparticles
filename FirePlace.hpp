#pragma once
#include <vector>
#include  "FireParticle.hpp"

class FirePlace {
private:
    std::vector<FireParticle*> fireParticles;

    float spread;
    float speed;
    float minLife;
    float maxLife;
    int points;
public:
    FirePlace();
    ~FirePlace();
    void draw();
    void createFire(FireParticle& pFire);
    void crackle(sf::Vector2f pos, float force);
    std::vector<FireParticle*> GetFireParticles();
    //Set and get for spread
    void setSpread(float spr);
    float getSpread();
    //Set anf get for speed
    void setSpeed(float spe);
    float getSpeed();
    //set and get for min life
    void setMinLife(float ml);
    float getMinLife();
    //set and get for max life
    void setMaxLife(float ml);
    float getMaxLife();
    //Increment points;
    void incPoints();
    //Decrement points
    void decPoints();
};