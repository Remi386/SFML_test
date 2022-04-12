#include "BonusesHandler.h"

namespace {
	std::mt19937 mersenne(1234664);
	std::uniform_int_distribution<> pos_dist(FieldWidth + 1, FieldSize - FieldWidth - 1);
}
extern constexpr uint32_t FontSize = 24;

BonusesHandler::BonusesHandler()
{
	boundaries.setSize(sf::Vector2f((FieldWidth - 2) * CellWidth, CellHeight));
	boundaries.setPosition(sf::Vector2f(LeftBoundary + CellWidth, FontSize + 5));
	boundaries.setFillColor(sf::Color::Black);
	boundaries.setOutlineColor(sf::Color::Red);
	boundaries.setOutlineThickness(1);

	progressBar.setFillColor(sf::Color::Red);
	progressBar.setPosition(sf::Vector2f(LeftBoundary + CellWidth, FontSize + 6));

	bonus.setRadius(std::min(CellHeight, CellWidth));
	bonus.setFillColor(sf::Color::Red);
};

void BonusesHandler::DeleteBonus(std::vector<GameChars>& gameField)
{
	if (gameField[position] != GameChars::Sneak)
		gameField[position] = GameChars::Void;

	if (gameField[position + 1] != GameChars::Sneak)
		gameField[position + 1] = GameChars::Void;

	if (gameField[position + FieldWidth] != GameChars::Sneak)
		gameField[position + FieldWidth] = GameChars::Void;

	if (gameField[position + FieldWidth + 1] != GameChars::Sneak)
		gameField[position + FieldWidth + 1] = GameChars::Void;

	isActive = false;
}

void BonusesHandler::GenerateBigBonus(sf::RenderWindow& window, std::vector<GameChars>& gameField)
{
	uint16_t _position;
	do {
		_position = pos_dist(mersenne);
	} while (CheckCell(_position, gameField)
		|| CheckCell(_position + 1, gameField)
		|| CheckCell(_position + FieldWidth, gameField)
		|| CheckCell(_position + FieldWidth + 1, gameField));

	gameField[_position] = GameChars::BigBonus;
	gameField[_position + 1] = GameChars::BigBonus;
	gameField[_position + FieldWidth] = GameChars::BigBonus;
	gameField[_position + FieldWidth + 1] = GameChars::BigBonus;

	position = _position;
}

void BonusesHandler::Update(sf::RenderWindow& window, std::vector<GameChars>& gameField)
{
	static int frameCounter = 0;
	frameCounter++;

	if (frameCounter % (FPS * 2) == 0) {
		GenerateLittleBonus(gameField);
	}

	if (frameCounter == FPS * 20) {
		frameCounter = 0;
		isActive = true;
		state = 100;
		GenerateBigBonus(window, gameField);
		bonus.setPosition(sf::Vector2f(
			LeftBoundary + (position % FieldWidth * CellWidth),
			UpperBoundary + (position / FieldHeight * CellHeight))
		);
	}

	if (isActive) {

		if (frameCounter == FPS * 5) {
			frameCounter = 0;
			DeleteBonus(gameField);
			return;
		}

		state -= 100. / (FPS * 5);

		progressBar.setSize(sf::Vector2f((FieldWidth - 2) * CellWidth * state / 100, CellHeight - 2));

		window.draw(bonus);
		window.draw(boundaries);
		window.draw(progressBar);
	}
}

void BonusesHandler::GenerateLittleBonus(std::vector<GameChars>& gameField)
{
	uint16_t _position;
	do {
		_position = pos_dist(mersenne);

	} while (CheckCell(_position, gameField));

	gameField[_position] = GameChars::LittleBonus;
}