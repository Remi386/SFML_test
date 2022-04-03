#include <list>
#include <vector>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "BigBonusHandler.h"

//Create sneak in the middle of field
namespace {
	std::list<uint16_t> sneak{ (fieldSize / 2) + (FieldWidth / 2),
								((fieldSize / 2) + (FieldWidth / 2) - 1) };
	std::vector<GameChars> gameField(fieldSize);
	uint32_t score = 0;
	BigBonus bigBonus;
}

//external functions
void drawField(sf::RenderWindow&, std::vector<GameChars>&);
mKey HandleInput();
void WaitPlayerAction(sf::RenderWindow& window);
void EndGame(sf::RenderWindow&, uint16_t);
void GenerateLittleBonus(sf::RenderWindow& window, std::vector<GameChars>& gameField);
void drawScore(sf::RenderWindow& window, uint16_t score);

//iternal functions
bool moveSneak(sf::RenderWindow& window, mKey key);
void checkBoundaries(uint16_t& head, mKey key);
uint16_t CalculateDist(sf::RenderWindow& window, mKey key);

void PrepareGame(sf::RenderWindow& window) 
{
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
	
	static uint16_t frameCounter = 0;

	++frameCounter;
	if (frameCounter == FPS * 2) {
		frameCounter = 0;
		GenerateLittleBonus(window, gameField);
	}

	if (moveSneak(window, key))
		return true;

	bigBonus.Update(window, gameField);
	
	drawField(window, gameField);
	drawScore(window, score);
	return false;
}

void AddTail(int count = 1)
{
	auto tail = sneak.back();
	auto prev = std::prev(sneak.end(), 2);
	for (int i = 0; i < count; ++i) {
		sneak.push_back(tail + (tail - *prev));
		tail++; prev++;
	}
}

bool moveSneak(sf::RenderWindow& window, mKey key)
{
	auto dist = CalculateDist(window, key);

	auto prev = sneak.front();

	auto& head = sneak.front();
	head += dist;

	checkBoundaries(head, key);

	gameField[sneak.back()] = GameChars::Void;

	switch (gameField[head])
	{
	case GameChars::Sneak:
		EndGame(window, score);
		return true;

	case GameChars::LittleBonus:
		score += 100;
		AddTail();
		break;

	case GameChars::BigBonus:
		score += 500;
		bigBonus.DeleteBonus(gameField);
		AddTail(3);
		break;
	default:
		break;
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
			throw std::runtime_error("Wrong input in a game loop");
			break;
		}
	}
}

uint16_t CalculateDist(sf::RenderWindow& window, mKey key) 
{
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

	oldDistance = distance;

	return oldDistance;
}