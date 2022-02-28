#pragma once
#include <cstdint>

constexpr int32_t ScreenWidth = 400;
constexpr int32_t ScreenHeight = 400;

//Boundaries for game field
constexpr int32_t LeftBoundary = 50;
constexpr int32_t RightBoundary = 350;
constexpr int32_t UpperBoundary = 50;
constexpr int32_t LowerBoundary = 350;
//Game unit in real pixels
constexpr int32_t CellWidth = 10;
constexpr int32_t CellHeight = 10;

constexpr int32_t FieldWidth = (RightBoundary - LeftBoundary) / CellWidth;
constexpr int32_t FieldHeight = (LowerBoundary - UpperBoundary) / CellHeight;
constexpr uint32_t fieldSize = FieldHeight * FieldWidth;

constexpr uint32_t FPS = 15;
constexpr uint32_t FontSize = 24;

enum class mKey
{
	MoveUp,
	MoveRight,
	MoveDown,
	MoveLeft,
	Nothing
};

enum class GameChars : uint8_t {
	Void,
	Sneak,
	Boundary,
	LittleBonus
};
