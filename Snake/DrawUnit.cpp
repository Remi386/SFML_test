#include "DrawUnit.h"

constexpr uint32_t FontSize = 24;

void drawBoundaries(sf::RenderWindow& window)
{
	static sf::Vertex boundaries[5] = {
		sf::Vector2f(LeftBoundary + CellWidth, UpperBoundary + CellHeight),
		sf::Vector2f(RightBoundary - CellWidth, UpperBoundary + CellHeight),
		sf::Vector2f(RightBoundary - CellWidth, LowerBoundary - CellHeight),
		sf::Vector2f(LeftBoundary + CellWidth, LowerBoundary - CellHeight),
		sf::Vector2f(LeftBoundary + CellWidth, UpperBoundary + CellHeight)
	};
	window.draw(boundaries, 5, sf::PrimitiveType::LinesStrip);
}

void drawField(sf::RenderWindow& window, std::vector<GameChars>& field) 
{
	
	sf::RectangleShape cell;
	cell.setSize(sf::Vector2f(CellWidth, CellHeight));
	
	for (int i = 0; i < FieldHeight; ++i) {
		for (int j = 0; j < FieldWidth; ++j) {

			cell.setPosition(sf::Vector2f(LeftBoundary + j * CellWidth, UpperBoundary + i * CellHeight));

			switch (field[i * FieldWidth + j])
			{
			case GameChars::Boundary:
				#ifdef _DEBUG
				cell.setFillColor(sf::Color::Green);
				break;
				#endif

			case GameChars::Void:
				#ifdef _DEBUG
				cell.setFillColor(sf::Color(150, 150, 150));
				break;
				#else
				continue;
				#endif

			case GameChars::Sneak:
				cell.setFillColor(sf::Color::White);
				break;

			case GameChars::LittleBonus:
				cell.setFillColor(sf::Color::Red);
				break;

			default:
				continue;
			}
			window.draw(cell);
		}
	}
	drawBoundaries(window);
}

void drawScore(sf::RenderWindow& window, uint16_t score) 
{

	sf::Text text("Score: " + std::to_string(score), font, FontSize);
	text.setPosition(sf::Vector2f((ScreenWidth) / 3, 0));

	window.draw(text);
}

void SetText(sf::RenderWindow& window, std::string str)
{
	window.clear(sf::Color::Black);

	sf::Text text(str, font, FontSize);
	text.setPosition(sf::Vector2f((RightBoundary - LeftBoundary) / 3,
		(LowerBoundary - UpperBoundary) / 2));
	window.draw(text);
	window.display();
}