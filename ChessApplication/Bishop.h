#pragma once

#include "ChessCoordinate.h"
#include "Chessman.h"


class Bishop : public Chessman
{
public:
	Bishop(ChessCoordinate coord);

public:
	bool CanMove(ChessCoordinate coord) override;
};
