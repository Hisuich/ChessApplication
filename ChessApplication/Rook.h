#pragma once

#include "ChessCoordinate.h"
#include "Chessman.h"

class Rook : public Chessman
{
public:
	bool isFirstMove;

public:
	Rook(ChessCoordinate coord);

	bool Move(ChessCoordinate nextCoord);
	bool CanMove(ChessCoordinate nextCoord) override;
};