#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <vector>

void drawBoundaries(sf::RenderWindow& window);

void drawField(sf::RenderWindow& window, std::vector<GameChars>& field) {
	
	sf::RectangleShape cell;
	cell.setSize(sf::Vector2f(CellWidth, CellHeight));
	
	for (int i = 0; i < FieldHeight; ++i) {
		for (int j = 0; j < FieldWidth; ++j) {
			cell.setPosition(sf::Vector2f(LeftBoundary + j * CellWidth, UpperBoundary + i * CellHeight));
			switch (field[i * FieldWidth + j])
			{
			case GameChars::Void:
				cell.setFillColor(sf::Color::Black);
				break;
			case GameChars::Sneak:
				cell.setFillColor(sf::Color::White);
				break;
			case GameChars::LittleBonus:
				cell.setFillColor(sf::Color::Red);
				break;
			}
			window.draw(cell);
		}
	}
	drawBoundaries(window);
}

void drawBoundaries(sf::RenderWindow& window) {
	static sf::Vertex boundaries[5] = {
		sf::Vector2f(LeftBoundary, UpperBoundary),
		sf::Vector2f(RightBoundary, UpperBoundary),
		sf::Vector2f(RightBoundary, LowerBoundary),
		sf::Vector2f(LeftBoundary, LowerBoundary),
		sf::Vector2f(LeftBoundary, UpperBoundary)
	};
	window.draw(boundaries, 5, sf::PrimitiveType::LinesStrip);
}