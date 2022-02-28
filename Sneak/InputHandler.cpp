#include <SFML/Window/Keyboard.hpp>
#include "Constants.h"


mKey HandleInput()
{
	static mKey CacheKey = mKey::Nothing;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		CacheKey = mKey::MoveUp;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		CacheKey = mKey::MoveRight;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		CacheKey = mKey::MoveDown;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		CacheKey = mKey::MoveLeft;
	}

	return CacheKey;
}
