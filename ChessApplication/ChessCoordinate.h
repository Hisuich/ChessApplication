#pragma once
#include <iostream>

class ChessCoordinate
{
public:
	int x;
	int y;

public:
	ChessCoordinate();
	ChessCoordinate(int x, int y);
	ChessCoordinate(wchar_t ChessX, int ChessY);
	ChessCoordinate(std::wstring ChessCoord);

	bool ValidateCoordinate();

	int GetX(wchar_t x);
	std::wstring GetChessCoord();

	ChessCoordinate operator-(const ChessCoordinate& coord);
	ChessCoordinate operator+(const ChessCoordinate& coord);
	ChessCoordinate operator*(const int& number);
	bool operator==(const ChessCoordinate& coord);
};