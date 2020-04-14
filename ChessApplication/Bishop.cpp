#include "Bishop.h"

Bishop::Bishop(ChessCoordinate coord) : Chessman(coord)
{
	moves = { {1,1},{1,-1},{-1,1},{-1,-1} };
	chessmanType = 'B';
	scalable = true;
}

bool Bishop::CanMove(ChessCoordinate nextCoord)
{
	if (!nextCoord.ValidateCoordinate())
		return false;

	ChessCoordinate tempCoord = this->coord - nextCoord;
	if (abs(tempCoord.x) == abs(tempCoord.y))
	{
		return true;
	}

	return false;
}