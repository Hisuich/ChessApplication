#include "Knight.h"

Knight::Knight(ChessCoordinate coord) : Chessman(coord)
{
	moves = { {1,2},{2,1},{-1,2},{2,-1},{1,-2},{-2,1},{-1,-2},{-2,-1} };
	this->chessmanType = 'N';
	canGoThrought = true;
}