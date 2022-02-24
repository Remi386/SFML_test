#include "Funtions.h"
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include <list>
#include <vector>
#include <cstdint>

namespace {
	std::list<uint16_t> sneak;
	std::vector<uint16_t> gameField(FieldHeight * FieldWidth);
}

void Play(sf::RenderWindow& window)
{
	mKey = HandleInput();

}