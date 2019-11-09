#pragma once
#include<SFML/Graphics.hpp>

#include"Globals.hpp"

class FireParticle {
private:
    sf::CircleShape particle;

    sf::Vector2f pos; //Position current position
    sf::Vector2f dir; //Direction current direction

    float speed;

    float lifetime;

    float minLife;
    float maxLife;

    sf::Color colour;
    //The colours we interpolate between
    sf::Color yellow = sf::Color::Yellow;
    sf::Color red = sf::Color::Red;

public:
    FireParticle() {}
    //A Particale need a start radius, a start direction with speed, life time and a rotation deviation, a size deviation, and what shape it should have
    FireParticle(sf::Vector2f circle, float rad, sf::Vector2f dir, float speed, float minLife, float maxLife, float maxrot, float minsize, float maxsize, int pointCount);
    void Tick(float dt);
    sf::CircleShape getParticle();
    void Crackle(sf::Vector2f origin, float force);

    ~FireParticle();
};

