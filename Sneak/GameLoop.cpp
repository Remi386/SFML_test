#include "Funtions.h"
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include <list>
#include <vector>
#include <cstdint>

std::list<uint16_t> sneak { (fieldSize / 2), ((fieldSize / 2) - 1)};
std::vector<GameChars> gameField(fieldSize + 1);
extern uint32_t score;

bool canGo(sf::RenderWindow& window, int16_t dist);
void moveSneak(sf::RenderWindow& window, int16_t dist);

void Play(sf::RenderWindow& window)
{
	mKey key = HandleInput();
	static int16_t oldDistance = 0;
	int16_t distance = 0;

	switch (key)
	{
	case mKey::MoveUp:
		distance = -FieldWidth;
		break;
	case mKey::MoveRight:
		distance = 1;
		break;
	case mKey::MoveDown:
		distance = FieldWidth;
		break;
	case mKey::MoveLeft:
		distance = -1;
		break;
	case mKey::Nothing:
		drawField(window, gameField);
		return;
	}
	
	if (canGo(window, distance)) 
		oldDistance = distance;

	moveSneak(window, oldDistance);
	
	drawField(window, gameField);
}

bool canGo(sf::RenderWindow& window, int16_t dist) {
	auto x = sneak.begin();
	auto first = *x;
	auto second = *(++x);

	return first + dist != second;
}

void moveSneak(sf::RenderWindow& window, int16_t dist) {

	auto prev = sneak.front();

	auto& head = sneak.front();
	head += dist;

	if (head < FieldWidth)
		head += FieldWidth * (FieldHeight - 1);

	if (head > FieldWidth * (FieldHeight))
		head %=  FieldWidth;

	if (head % FieldWidth == 0)
		head += FieldWidth - 2;

	if (head % FieldWidth == FieldWidth - 1)
		head -= FieldWidth - 2;

	gameField[head] = GameChars::Sneak;
	gameField[sneak.back()] = GameChars::Void;

	for (auto iter = std::next(sneak.begin()); iter != sneak.end(); ++iter) {
		std::swap(*iter, prev);
	}
	
}

