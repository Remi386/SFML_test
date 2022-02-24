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
constexpr int32_t CellWidth = 2;
constexpr int32_t CellHeight = 2;

constexpr int32_t FieldWidth = (RightBoundary - LeftBoundary) / CellWidth;
constexpr int32_t FieldHeight = (LowerBoundary - UpperBoundary) / CellHeight;

enum class mKey
{
	MoveUp,
	MoveRight,
	MoveDown,
	MoveLeft
};

