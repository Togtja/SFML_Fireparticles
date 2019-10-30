#include<SFML/Graphics.hpp>

const int SCREEN = 500;

const int WOODSIZE_X = 100;
const int WOODSIZE_Y = 20;

const float WOOD_ROT = 45;

const sf::Vector2f ORIGIN(WOODSIZE_X / 2, WOODSIZE_Y/2);
const sf::Vector2f WOODPOS(SCREEN / 2, SCREEN - WOODSIZE_Y);



int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN, SCREEN), "Events");
    //Create the wood
    sf::RectangleShape wood1(sf::Vector2f(WOODSIZE_X, WOODSIZE_Y));
    wood1.setFillColor(sf::Color(161, 64, 5, 255));

    wood1.setOrigin(ORIGIN);
    wood1.setPosition(WOODPOS);
    
    sf::RectangleShape wood2 = wood1;

    wood1.rotate(WOOD_ROT);
    wood2.rotate(-WOOD_ROT);
    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::MouseButtonPressed) {
                //Do Crackle
            }
        }
        window.clear();
        window.draw(wood1);
        window.draw(wood2);
        window.display();
    } 
}