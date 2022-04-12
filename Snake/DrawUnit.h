#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"

extern sf::Font font;

void drawField(sf::RenderWindow& window, std::vector<GameChars>& field);

void drawScore(sf::RenderWindow& window, uint16_t score);

void SetText(sf::RenderWindow& window, std::string str);