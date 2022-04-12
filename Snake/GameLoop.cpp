#include <list>
#include <vector>
#include "Constants.h"
#include "BonusesHandler.h"
#include "GameLoop.h"
#include "InputHandler.h"
#include "DrawUnit.h"
#include "GameEvents.h"

//Create sneak in the middle of field
namespace {
	std::list<uint16_t> sneak{ (FieldSize / 2) + (FieldWidth / 2),
								((FieldSize / 2) + (FieldWidth / 2) - 1) };
	std::vector<GameChars> gameField(FieldSize);
	uint32_t score = 0;
	BonusesHandler bHandler;
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

uint16_t CalculateDist(sf::RenderWindow& window, mKey key)
{
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

	return distance;
}

void checkBoundaries(uint16_t& head, mKey key)
{
	if (gameField[head] == GameChars::Boundary) {
		switch (key)
		{
		case mKey::MoveUp:
			head = FieldSize - ((2 * FieldWidth) - head);
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
			break;
		}
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
		bHandler.DeleteBonus(gameField);
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

void PrepareGame(sf::RenderWindow& window)
{
	//Create upper and lower boundaries
	for (int i = 0; i < FieldWidth; ++i) {
		gameField[i] = GameChars::Boundary;
		gameField[FieldSize - i - 1] = GameChars::Boundary;
	}
	//Create right and left boundaries
	for (int i = 1; i < FieldHeight; ++i) {
		gameField[i * FieldWidth] = GameChars::Boundary;
		gameField[i * FieldWidth - 1] = GameChars::Boundary;
	}

	StartGame(window);
}

bool Play(sf::RenderWindow& window)
{
	mKey key = HandleInput();

	if (moveSneak(window, key))
		return true;

	bHandler.Update(window, gameField);

	drawField(window, gameField);
	drawScore(window, score);
	return false;
}