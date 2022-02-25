#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.h"

bool Play(sf::RenderWindow& window);

void drawField(sf::RenderWindow&, std::vector<GameChars>& );

mKey HandleInput();

void WaitPlayerAction(sf::RenderWindow& window);

void EndGame(sf::RenderWindow&, uint16_t);

void GenerateBonus(sf::RenderWindow& window, std::vector<GameChars>& gameField);

void drawScore(sf::RenderWindow& window, uint16_t score);