#pragma once
#include <cstdint>

inline constexpr int32_t ScreenWidth = 400;
inline constexpr int32_t ScreenHeight = 400;

inline constexpr int32_t OffsetFromScreen = 50;

//Boundaries for game field
inline constexpr int32_t LeftBoundary = OffsetFromScreen;
inline constexpr int32_t RightBoundary = ScreenWidth - OffsetFromScreen;
inline constexpr int32_t UpperBoundary = OffsetFromScreen;
inline constexpr int32_t LowerBoundary = ScreenHeight - OffsetFromScreen;
//Game unit in real pixels
inline constexpr int32_t CellWidth = 10;
inline constexpr int32_t CellHeight = 10;

inline constexpr int32_t FieldWidth = (RightBoundary - LeftBoundary) / CellWidth;
inline constexpr int32_t FieldHeight = (LowerBoundary - UpperBoundary) / CellHeight;
inline constexpr uint32_t FieldSize = FieldHeight * FieldWidth;

inline constexpr uint16_t FPS = 15;

enum class GameChars : uint8_t {
	Void,
	Sneak,
	Boundary,
	LittleBonus,
	BigBonus
};
