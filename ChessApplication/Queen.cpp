#include "Queen.h"

Queen::Queen(ChessCoordinate coord) : Chessman(coord)
{
	moves = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,-1},{-1,1}};
	chessmanType = 'Q';
	scalable = true;
}

bool Queen::CanMove(ChessCoordinate nextCoord)
{
	if (!nextCoord.ValidateCoordinate())
		return false;
	ChessCoordinate tempCoord = this->coord - nextCoord;
	if (abs(tempCoord.x) == abs(tempCoord.y) || tempCoord.x == 0 || tempCoord.y == 0)
	{
		return true;
	}

	return false;
}