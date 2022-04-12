#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "Constants.h"

enum class mKey
{
	MoveUp,
	MoveRight,
	MoveDown,
	MoveLeft,
	Nothing
};

mKey HandleInput();