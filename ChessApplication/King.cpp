#include "King.h"

King::King(ChessCoordinate coord) : Chessman(coord)
{
	moves = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,-1},{-1,1} };
	chessmanType = 'K';
	isFirstMove = true;
	isCastling = false;
	canMove = false;
}

King::~King()
{
	delete[] possibleMoves;
}

bool King::Move(ChessCoordinate nextCoord)
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

bool King::CanMove(ChessCoordinate nextCoord)
{
	if (!nextCoord.ValidateCoordinate())
		return false;

	if (Chessman::CanMove(nextCoord))
	{
		if (possibleMoves[nextCoord.y * 8 + nextCoord.x])
			return true;
	}
	if (isCastling && isFirstMove)
	{
		if (this->coord + ChessCoordinate(2, 0) == nextCoord ||
			this->coord + ChessCoordinate(-2, 0) == nextCoord)
		{
			if (possibleMoves[nextCoord.y * 8 + nextCoord.x])
				return true;
		}
	}

	return false;	 
}

void King::SetPossibleMoves(bool possibleMoves[])
{
	canMove = false;

	for (auto& move : this->possibleMoves)
		move = false;

	for (const auto& move : moves)
	{
		ChessCoordinate newMove = this->coord + move;
		if (!newMove.ValidateCoordinate()) continue;
		this->possibleMoves[newMove.y * 8 + newMove.x] = possibleMoves[newMove.y * 8 + newMove.x];
		if (possibleMoves[newMove.y * 8 + newMove.x])
			canMove = true;
	}

	//Must comment it. For unknown reason, first player change chessmanType here. Just fix it with hardcode.
	chessmanType = 'K';
}

void King::SetPossibleMovesWithEnemyMoves(bool enemyMoves[])
{
	canMove = false;

	for (const auto& move : moves)
	{
		ChessCoordinate newMove = this->coord + move;
		if (!newMove.ValidateCoordinate()) continue;
		if (enemyMoves[newMove.y * 8 + newMove.x])
			this->possibleMoves[newMove.y * 8 + newMove.x] = false;

		if (this->possibleMoves[newMove.y * 8 + newMove.x])
			canMove = true;
	}

	//Must comment it. For unknown reason, first player change chessmanType here. Just fix it with hardcode.
	chessmanType = 'K';
}


