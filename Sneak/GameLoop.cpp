#include "Funtions.h"
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include <list>
#include <vector>
#include <cstdint>
#include <random>

constexpr uint32_t fieldSize = FieldHeight * FieldWidth;

std::mt19937 mersenne(1234664);
std::uniform_int_distribution<> dis(0, fieldSize - 1);

std::list<uint16_t> sneak;
std::vector<uint16_t> gameField(FieldHeight* FieldWidth);


void Play(sf::RenderWindow& window)
{
	for (int i = 0; i < 20; ++i) {
		gameField[dis(mersenne)] = 1;
	}
	drawField(window, gameField);
}