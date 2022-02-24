#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.h"

void Play(sf::RenderWindow&);

void drawField(sf::RenderWindow&, std::vector<GameChars>&);

mKey HandleInput();

void WaitPlayerAction(sf::RenderWindow&);

void EndGame(sf::RenderWindow& window);

void GenerateBonuses(sf::RenderWindow& window, std::vector<GameChars>&);