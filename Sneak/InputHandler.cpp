#include <SFML/Window/Keyboard.hpp>
#include "Constants.h"

mKey HandleInput()
{
	static mKey CacheKey = mKey::Nothing;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if(CacheKey != mKey::MoveDown)
			CacheKey = mKey::MoveUp;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (CacheKey != mKey::MoveLeft)
			CacheKey = mKey::MoveRight;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (CacheKey != mKey::MoveUp)
			CacheKey = mKey::MoveDown;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (CacheKey != mKey::MoveRight)
			CacheKey = mKey::MoveLeft;
	}

	return CacheKey;
}
