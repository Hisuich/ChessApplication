
#include "Rook.h"

Rook::Rook(ChessCoordinate coord) : Chessman(coord)
{
	moves = { {1,0},{0,1},{-1,0},{0,-1} };
	chessmanType = 'R';
	scalable = true;
	isFirstMove = true;
}

bool Rook::Move(ChessCoordinate nextCoord)
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

bool Rook::CanMove(ChessCoordinate nextCoord)
{
	
	if (!nextCoord.ValidateCoordinate())
		return false;
		
	ChessCoordinate tempCoord = this->coord - nextCoord;
	if (tempCoord.x == 0 || tempCoord.y == 0)
	{
		return true;
	}

	return false;
}