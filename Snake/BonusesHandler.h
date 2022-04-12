#pragma once
#include <cstdint>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include "GameEvents.h"
#include "Constants.h"

class BonusesHandler {
public:
	BonusesHandler();
	BonusesHandler(const BonusesHandler&) = delete;
	BonusesHandler(BonusesHandler&&) = delete;
	void operator=(const BonusesHandler&) = delete;
	void operator=(BonusesHandler&&) = delete;

	void Update(sf::RenderWindow& window, std::vector<GameChars>& gameField);

	void DeleteBonus(std::vector<GameChars>& gameField);

private:

	void GenerateBigBonus(sf::RenderWindow& window, std::vector<GameChars>& gameField);

	void GenerateLittleBonus(std::vector<GameChars>& gameField);

private:
	sf::RectangleShape boundaries;
	sf::RectangleShape progressBar;
	sf::CircleShape bonus;
	uint16_t position = 0;
	float state = 0;
	bool isActive = false;
};