#include "Pawn.h"

Pawn::Pawn(ChessCoordinate coord, bool isDown) : Chessman(coord)
{
	this->isDown = isDown;
	if (isDown)
		this->moves = { {0,-1} };
	else
		this->moves = { {0, 1}};
	this->chessmanType = 'P';
	isFirstMove = true;
}

bool Pawn::Move(ChessCoordinate nextCoord)
{
	if (CanMove(nextCoord))
	{
		if (isFirstMove)
			isFirstMove = false;
		this->coord = nextCoord;
		return true;
	}
	return false;
}

bool Pawn::CanMove(ChessCoordinate nextCoord)
{
	if (!nextCoord.ValidateCoordinate())
		return false;

	if (isFirstMove && 
		(this->coord + ChessCoordinate(0, 2)) == nextCoord)
	{
		return true;
	}
	ChessCoordinate nextMove = this->coord - ChessCoordinate(0, 2);
	
	if (isFirstMove &&
		(this->coord - ChessCoordinate(0, 2)) == nextCoord)
	{
		std::wstring what = L"what";
		return true;
	}
	return Chessman::CanMove(nextCoord);
}

bool Pawn::CanBeat(ChessCoordinate nextCoord)
{
	if (this->coord + (this->moves[0] + ChessCoordinate(1, 0)) == nextCoord ||
		this->coord + (this->moves[0] + ChessCoordinate(-1, 0)) == nextCoord)
	{
		return true;
	}

	return false;
}