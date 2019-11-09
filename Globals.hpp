#pragma once

#include <SFML/Graphics.hpp>
const int SCREEN = 500;

const int WOODSIZE_X = 100;
const int WOODSIZE_Y = 20;

const float WOOD_ROT = 45;

const sf::Vector2f ORIGIN(WOODSIZE_X / 2, WOODSIZE_Y / 2);
const sf::Vector2f WOODPOS(SCREEN / 2, SCREEN - WOODSIZE_Y);



//extern EventManagerSingleton& EventM;