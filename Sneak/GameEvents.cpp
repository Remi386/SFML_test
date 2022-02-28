#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <random>

sf::Font font;

std::mt19937 mersenne(1234664);
std::uniform_int_distribution<> pos_dist(0, fieldSize - 1);

void WaitKeyPressed(sf::RenderWindow& window);

void SetText(sf::RenderWindow& window, std::string str) {
	window.clear(sf::Color::Black);

	sf::Text text(str, font, FontSize);
	text.setPosition(sf::Vector2f((RightBoundary - LeftBoundary) / 3,
		(LowerBoundary - UpperBoundary) / 2));
	window.draw(text);
	window.display();
}

void WaitPlayerAction(sf::RenderWindow& window) {
	
	font.loadFromFile("ayar.ttf");
	SetText(window, "Press any key to\n start the game");
	WaitKeyPressed(window);
}

void EndGame(sf::RenderWindow& window, uint16_t score) {
	SetText(window, "Game over!\nScore: " + std::to_string(score));
	WaitKeyPressed(window);
}

void GenerateBonus(sf::RenderWindow& window, std::vector<GameChars>& gameField) {
	uint16_t position;
	do {
		position = pos_dist(mersenne);

	} while (gameField[position] == GameChars::Boundary
			|| gameField[position] == GameChars::Sneak);

	gameField[position] = GameChars::LittleBonus;
}

void WaitKeyPressed(sf::RenderWindow& window) {
	sf::Event ev;
	while (true) {
		window.waitEvent(ev);

		if (ev.type == sf::Event::KeyPressed)
			return;

		if (ev.type == sf::Event::Closed)
			window.close();
	}
}