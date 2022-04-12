#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "Constants.h"

extern sf::Font font;

void WaitKeyPressed(sf::RenderWindow& window);

void SetText(sf::RenderWindow& window, std::string str);

void StartGame(sf::RenderWindow& window);

void EndGame(sf::RenderWindow& window, uint16_t score);

bool CheckCell(uint16_t position, std::vector<GameChars>& gameField);