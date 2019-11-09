#include "FireParticle.hpp"
#include <random>
#include <iostream>
#include "EventManager.hpp"
const float PI = 3.14159;
const int DEG = 180;
//Degree to radiants
float rad(const float deg) { return (deg*PI) / DEG; }
//Radiandst to degrees
float deg(const float rad) { return rad * (DEG / PI); }
std::random_device rd;
std::mt19937_64 gen(rd());



//EventManagerSingleton& EventM = EventManagerSingleton::getEventManager();
float magnitude(sf::Vector2f v) {
    return sqrt(v.x*v.x + v.y*v.y);
}
sf::Vector2f normilize(sf::Vector2f v) {
    float mag = magnitude(v);
    if (mag != 0) {
        return v / mag;
    }
    return v;
}
bool isInside(sf::Vector2f center,
              float rad, float x, float y) {
    // Compare radius of circle with distance  
    // of its center from given point 
    if ((x - center.x) * (x - center.x) +
        (y - center.y) * (y - center.y) <= rad * rad)
        return true;
    else
        return false;
}
FireParticle::FireParticle(sf::Vector2f circle, float radi, sf::Vector2f dir, float speed,
                           float minLife, float maxLife ,float maxrot, 
                           float minsize, float maxsize, int pointCount) {
    //Set the colors
    //yellow = 
    this->speed = speed;
    //find random size between min and max;
    float size = std::uniform_real_distribution<float>(minsize, maxsize)(gen);
    //Set the Radius
    particle.setRadius(size);
    particle.setOrigin(sf::Vector2f(size / 2, size / 2));
    particle.setPosition(circle);
    pos = circle;
    //Set the pointCount
    particle.setPointCount(pointCount);



    //Find a random point closely within circle and rad
    float x, y;
    x = std::uniform_real_distribution<float>(0, radi)(gen);
    y = std::uniform_real_distribution<float>(0, radi)(gen);
        //then find a random deviation from 0 to rotdev an apply it to dir}
    float rotDev = std::uniform_real_distribution<float>(-maxrot, maxrot)(gen);

    //Normilize the direction
    dir = normilize(dir);

    //give it a random rotation
    float dirx = dir.x, diry = dir.y;
    dir.x = dirx *cos(rad(rotDev)) - diry * sin(rad(rotDev));
    dir.y = dirx * sin(rad(rotDev)) + diry * cos(rad(rotDev));
    this->dir = dir;

    //Find life spam
    this->minLife = minLife;
    this->maxLife = maxLife;
    lifetime = std::uniform_real_distribution<float>(minLife, maxLife)(gen);

}
void FireParticle::Tick(float dt) {
    lifetime -= dt;
    if (lifetime < 0) {

        DeathEvent* death = new DeathEvent(*this);
        death->name = "Lit";
        death->id = EventID::Death;
        //ptr->name = "Ooufie";
        EventManagerSingleton::getEventManager().addEvent(death);
        //EventM.addEvent(death);
        return;
    }
    pos += dir * speed * dt;
    particle.setPosition(pos);

    float frac = ((lifetime - maxLife) / (maxLife - minLife));
    int r = (yellow.r - red.r) * frac + red.r;
    int g = (yellow.g - red.g) * frac + red.g;
    int b = (yellow.b - red.b) * frac + red.b;
    particle.setFillColor(sf::Color(r, g, b));


}

sf::CircleShape FireParticle::getParticle() {
    return particle;
}

void FireParticle::Crackle(sf::Vector2f origin, float force) {
    sf::Vector2f pushDir = pos - origin; //Direction this particale will be pushed
    float dis = magnitude(pushDir); //the distance, futher the distance, the wekk the crackle
    pushDir = normilize(pushDir);
    dir += pushDir*(force/dis);
}


FireParticle::~FireParticle() {}
