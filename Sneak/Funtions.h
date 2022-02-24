#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.h"

void Play(sf::RenderWindow&);

void drawField(sf::RenderWindow&, std::vector<uint16_t>&);

mKey HandleInput();