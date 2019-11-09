#include <vector>
#include <iostream>

#include "FirePlace.hpp"
#include "EventManager.hpp"
int main() {
    //EventManagerSingleton& EventM = EventManagerSingleton::getEventManager();
    sf::RenderWindow window(sf::VideoMode(SCREEN, SCREEN), "Events");
    //Create the wood
    sf::RectangleShape wood1(sf::Vector2f(WOODSIZE_X, WOODSIZE_Y));
    wood1.setFillColor(sf::Color(161, 64, 5, 255));

    wood1.setOrigin(ORIGIN);
    wood1.setPosition(WOODPOS);
    
    sf::RectangleShape wood2 = wood1;

    wood1.rotate(WOOD_ROT);
    wood2.rotate(-WOOD_ROT);

    

    sf::Clock deltaClock;

    FirePlace firePlace;
    float spawnTimer = .1;
    std::vector<std::unique_ptr<Event>>& events = EventManagerSingleton::getEventManager().getEvents();

    while(window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        sf::Event e;
        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::MouseButtonPressed) {
                for (auto& fire : firePlace.GetFireParticles()) {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    fire->Crackle((sf::Vector2f)pixelPos, 5);
                }

            }
        }
        spawnTimer -= dt;
        if (spawnTimer < 0) {
            firePlace.draw();
            spawnTimer = .1;
        }
        
        window.clear();
        window.draw(wood1);
        window.draw(wood2);
        for (auto& fire : firePlace.GetFireParticles()) {
            fire->Tick(dt);
            window.draw(fire->getParticle());
        }
        window.display();
        
        for (auto it = events.begin() ; it != events.end();) {
            
            if (it->get()->id == EventID::Death) {
                DeathEvent* death = static_cast<DeathEvent*>(it->get());
                firePlace.createFire(death->deadFire);
                it = events.erase(it);
            }
            else {
               it++;
            }
        }
    } 
}