#pragma once

#include "ChessCoordinate.h"
#include "Chessman.h"

#include <iostream>
#include <string>

using std::string;

class Pawn : public Chessman
{
public:
	bool isDown;

private:
	bool isFirstMove;

public:
	Pawn(ChessCoordinate coord, bool isDown);

	bool Move(ChessCoordinate nextCoord);
	virtual bool CanMove(ChessCoordinate nextCoord) override;
	virtual bool CanBeat(ChessCoordinate nextCoord) override;
};