#include "Funtions.h"
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include <list>
#include <vector>
#include <cstdint>

std::list<uint16_t> sneak { (fieldSize / 2), ((fieldSize / 2) - 1)};
std::vector<GameChars> gameField(fieldSize + 1);
uint32_t score = 0;

bool canGo(sf::RenderWindow& window, int16_t dist);
bool moveSneak(sf::RenderWindow& window, int16_t dist);
void checkBoundaries(uint16_t& head);

bool Play(sf::RenderWindow& window)
{
	mKey key = HandleInput();
	static int16_t oldDistance = 0;
	
	static uint8_t frameCounter = 0;
	int16_t distance = 0;

	++frameCounter;
	if (frameCounter == 5) {
		frameCounter = 0;
		GenerateBonus(window, gameField);
	}

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
		return false;
	}
	
	if (canGo(window, distance)) 
		oldDistance = distance;

	if (moveSneak(window, oldDistance))
		return true;
	
	drawField(window, gameField);
	drawScore(window, score);
	return false;
}

bool canGo(sf::RenderWindow& window, int16_t dist) 
{
	auto x = sneak.begin();
	auto first = *x;
	auto second = *(++x);

	return first + dist != second;
}

bool moveSneak(sf::RenderWindow& window, int16_t dist)
{
	auto prev = sneak.front();

	auto& head = sneak.front();
	head += dist;

	checkBoundaries(head);

	gameField[sneak.back()] = GameChars::Void;

	if (gameField[head] == GameChars::Sneak) {
		EndGame(window, score);
		return true;
	}

	if (gameField[head] == GameChars::LittleBonus) {
		score += 100;
		auto tail = sneak.back();
		auto prev = std::prev(sneak.end(), 2);
		sneak.push_back(tail + (tail - *prev));
	}

	gameField[head] = GameChars::Sneak;

	for (auto iter = std::next(sneak.begin()); iter != sneak.end(); ++iter) {
		std::swap(*iter, prev);
	}
	return false;
}

void checkBoundaries(uint16_t& head) 
{
	if (head < FieldWidth)
		head += FieldWidth * (FieldHeight - 1);

	if (head > FieldWidth * (FieldHeight))
		head = head % FieldWidth + FieldWidth;

	if (head % FieldWidth == 0)
		head += FieldWidth - 2;

	if (head % FieldWidth == FieldWidth - 1)
		head -= FieldWidth - 2;
}