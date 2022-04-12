#include "GameEvents.h"
#include "DrawUnit.h"

sf::Font font;

void WaitKeyPressed(sf::RenderWindow& window)
{
	sf::Event ev;
	while (true) {
		window.waitEvent(ev);

		if (ev.type == sf::Event::KeyPressed)
			return;

		if (ev.type == sf::Event::Closed)
			window.close();
	}
}

void StartGame(sf::RenderWindow& window) 
{
	font.loadFromFile("ayar.ttf");
	SetText(window, "Press any key to\n start the game");
	WaitKeyPressed(window);
}

void EndGame(sf::RenderWindow& window, uint16_t score) 
{
	SetText(window, "Game over!\nScore: " + std::to_string(score));
	WaitKeyPressed(window);
}

bool CheckCell(uint16_t position, std::vector<GameChars>& gameField)
{
	return gameField[position] == GameChars::Boundary
		|| gameField[position] == GameChars::Sneak;
}

