#pragma once
#include <cstdint>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <random>

extern std::mt19937 mersenne;
extern std::uniform_int_distribution<> pos_dist;

inline bool CheckCell(uint16_t position, std::vector<GameChars>& gameField);

class BigBonus {
public:
	BigBonus()
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

	void Update(sf::RenderWindow& window, std::vector<GameChars>& gameField)
	{
		static int frameCounter = 0;
		frameCounter++;

		if (frameCounter == FPS * 20) {
			frameCounter = 0;
			isActive = true;
			state = 100;
			GenerateBigBonus(window, gameField);
			bonus.setPosition(sf::Vector2f
			(LeftBoundary + (position % FieldWidth * CellWidth),
				UpperBoundary + (position / FieldHeight * CellHeight)));
		}

		if (!isActive) {
			return;
		}

		if (frameCounter == FPS * 5) {
			frameCounter = 0;
			DeleteBonus(gameField);
			isActive = false;
			return;
		}

		state -= 100. / (FPS * 5);

		progressBar.setSize(sf::Vector2f((FieldWidth - 2) * CellWidth * state / 100, CellHeight - 2));

		window.draw(bonus);
		window.draw(boundaries);
		window.draw(progressBar);

	}

	void DeleteBonus(std::vector<GameChars>& gameField)
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

private:

	void GenerateBigBonus(sf::RenderWindow& window, std::vector<GameChars>& gameField)
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

private:
	sf::RectangleShape boundaries;
	sf::RectangleShape progressBar;
	sf::CircleShape bonus;
	uint16_t position = 0;
	float state = 0;
	bool isActive = false;
};