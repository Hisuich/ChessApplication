#pragma once

#include "ChessCoordinate.h"
#include "Chessman.h"

class King : public Chessman
{
public:
	bool isFirstMove;
	bool isCastling;
	bool possibleMoves[8*8];
	bool canMove;

public:
	King(ChessCoordinate coord);
	~King();

	bool CanMove(ChessCoordinate nextCoord);
	bool Move(ChessCoordinate nextCoord);
	void SetPossibleMoves(bool possibleMove[]);
	void SetPossibleMovesWithEnemyMoves(bool enemyMoves[]);
};