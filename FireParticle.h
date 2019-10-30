#pragma once
#include<SFML/Graphics.hpp>
class FireParticle {
private:
    sf::CircleShape particle;

    sf::Vector2f pos; //Position current position
    sf::Vector2f dir; //Direction current direction

    float speed;

    float lifetime;

public:
    //A Particale need a start radius, a start direction with a deviation 
    FireParticle(sf::Vector2f circle, float rad, sf::Vector2f dir, float dev, float minsize = 1, float maxsize = 5, int pointCount = 3);
    void Tick(float dt);


    ~FireParticle();
};

