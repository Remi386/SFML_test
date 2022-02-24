#pragma once
#include <cstdint>

constexpr int32_t ScreenWidth = 400;
constexpr int32_t ScreenHeight = 400;

//Boundaries 32for game field
constexpr int32_t LeftBoundary = 50;
constexpr int32_t RightBoundary = 350;
constexpr int32_t UpperBoundary = 50;
constexpr int32_t LowerBoundary = 350;
//Game unit i32n real pixels
constexpr int32_t CellWidth = 4;
constexpr int32_t CellHeight = 4;

constexpr int32_t FieldWidth = (RightBoundary - LeftBoundary) / CellWidth;
constexpr int32_t FieldHeight = (LowerBoundary - UpperBoundary) / CellHeight;
constexpr uint32_t fieldSize = FieldHeight * FieldWidth;

constexpr uint32_t FPS = 30;
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
	LittleBonus
};
