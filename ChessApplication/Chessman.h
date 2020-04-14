#pragma once

#include "ChessCoordinate.h"
#include <iostream>
#include <vector>

class Chessman
{
public:
	bool isBeated;
	bool canGoThrought;

protected:
	ChessCoordinate coord;
	std::vector<ChessCoordinate> moves;
	wchar_t chessmanType;

	bool scalable;

public:
	Chessman(ChessCoordinate coord);

	virtual bool Move(ChessCoordinate nextCoord);
	virtual bool CanMove(ChessCoordinate nextCoord);
	virtual bool Beat(ChessCoordinate nextCoord);
	virtual bool CanBeat(ChessCoordinate nextCoord);

	wchar_t GetChessmanType();
	std::vector<ChessCoordinate> GetMoves();

	ChessCoordinate GetCoord();
	std::wstring GetChessCoord();
	void Rotate();

};