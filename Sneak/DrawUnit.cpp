#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <vector>

void drawField(sf::RenderWindow& window, std::vector<uint16_t>& field) {

	sf::RectangleShape cell;
	cell.setSize(sf::Vector2f(CellWidth, CellHeight));
	

	for (int i = 0; i < FieldHeight; ++i) {
		for (int j = 0; j < FieldWidth; ++j) {
			cell.setPosition(sf::Vector2f(LeftBoundary + j * CellWidth, UpperBoundary + i * CellHeight));
			cell.setFillColor(
				(field[i * FieldWidth + j] == 1) ? sf::Color::Black : sf::Color::White
			);
			window.draw(cell);
		}
	}
}