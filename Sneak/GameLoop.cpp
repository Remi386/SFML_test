#include "Funtions.h"
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include <list>
#include <vector>
#include <cstdint>

std::list<uint16_t> sneak { (fieldSize / 2) + (FieldWidth / 2),
							((fieldSize / 2) + (FieldWidth / 2) - 1) };
std::vector<GameChars> gameField(fieldSize + 1);
uint32_t score = 0;

bool canGo(sf::RenderWindow& window, int16_t dist);
bool moveSneak(sf::RenderWindow& window, mKey key);
void checkBoundaries(uint16_t& head, mKey key);
uint16_t CalculateDist(sf::RenderWindow& window, mKey key);

void PrepareGame(sf::RenderWindow& window) {
	//Create upper and lower boundaries
	for (int i = 0; i < FieldWidth; ++i) {
		gameField[i] = GameChars::Boundary;
		gameField[fieldSize - i - 1] = GameChars::Boundary;
	}
	//Create right and left boundaries
	for (int i = 1; i < FieldHeight; ++i) {
		gameField[i * FieldWidth] = GameChars::Boundary;
		gameField[i * FieldWidth - 1] = GameChars::Boundary;
	}

	WaitPlayerAction(window);
}

bool Play(sf::RenderWindow& window)
{
	mKey key = HandleInput();
	
	static uint8_t frameCounter = 0;

	++frameCounter;
	if (frameCounter == 5) {
		frameCounter = 0;
		GenerateBonus(window, gameField);
	}

	if (moveSneak(window, key))
		return true;
	
	drawField(window, gameField);
	drawScore(window, score);
	return false;
}

// Moving to inside the sneak in not allowed
bool canGo(sf::RenderWindow& window, int16_t dist) 
{
	auto x = sneak.begin();
	auto first = *x;
	auto second = *(++x);

	return first + dist != second;
}

bool moveSneak(sf::RenderWindow& window, mKey key)
{
	auto dist = CalculateDist(window, key);

	auto prev = sneak.front();

	auto& head = sneak.front();
	head += dist;

	checkBoundaries(head, key);

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

void checkBoundaries(uint16_t& head, mKey key) 
{
	if (gameField[head] == GameChars::Boundary) {
		switch (key)
		{
		case mKey::MoveUp:
			head = fieldSize - ((2 * FieldWidth) - head);
			break;
		case mKey::MoveRight:
			head -= FieldWidth - 2;
			break;
		case mKey::MoveDown:
			head = head % FieldWidth + FieldWidth;
			break;
		case mKey::MoveLeft:
			head += FieldWidth - 2;
			break;
		case mKey::Nothing:
			std::terminate();
			break;
		}
	}
		
}

uint16_t CalculateDist(sf::RenderWindow& window, mKey key) {
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
		return 0;
	}

	if (canGo(window, distance))
		oldDistance = distance;
	return oldDistance;
}