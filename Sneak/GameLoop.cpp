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
	mKey key = HandleInput();
	switch (key)
	{
	case mKey::MoveUp:
		for (int i = 0; i < 20; ++i) {
			gameField[dis(mersenne)] = 0;
		}
		break;
	case mKey::MoveRight:
		for (int i = 0; i < gameField.size(); ++i) {
			gameField[i] = 1;
		}
		break;
	case mKey::MoveDown:
		for (int i = 0; i < gameField.size(); ++i) {
			gameField[i] = 0;
		}
		break;
	case mKey::MoveLeft:
		for (int i = 0; i < FieldHeight; ++i) {
			for (int j = 0; j < FieldWidth; ++j) {
				if (i < FieldHeight / 2 && j < FieldWidth / 2) {
					gameField[i * FieldWidth + j] = 0;
				}
			}
		}
		break;
	}
	
	drawField(window, gameField);
}