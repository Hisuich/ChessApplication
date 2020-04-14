#pragma once

#include "ChessCoordinate.h"
#include "Chessman.h"

class Queen : public Chessman
{
public:
	Queen(ChessCoordinate coord);

	bool CanMove(ChessCoordinate nextCoord) override;
};