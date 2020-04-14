#include "Chessman.h"

Chessman::Chessman(ChessCoordinate coord)
{
	this->coord = coord;
	canGoThrought = false;
	isBeated = false;
}

bool Chessman::Move(ChessCoordinate nextCoord)
{
	if (CanMove(nextCoord))
	{
		this->coord = nextCoord;
		return true;
	}

	return false;
}

bool Chessman::CanMove(ChessCoordinate nextCoord)
{
	if (!nextCoord.ValidateCoordinate())
		return false;

	for (auto& move : moves)
	{
		if (this->coord + move == nextCoord)
		{
			return true;
		}
	}
	std::wcout << L"Invalid coordinate: " << nextCoord.x << " " << nextCoord.y << std::endl;
	return false;
}

bool Chessman::Beat(ChessCoordinate nextCoord)
{
	if (CanBeat(nextCoord))
	{
		this->coord = nextCoord;
		return true;
	}

	return false;
}

bool Chessman::CanBeat(ChessCoordinate nextCoord)
{
	return CanMove(nextCoord);
}

wchar_t Chessman::GetChessmanType()
{
	return chessmanType;
}

std::vector<ChessCoordinate> Chessman::GetMoves()
{

	std::vector<ChessCoordinate> posMoves;
	
	if (scalable)
		for (auto& move : moves)
		{
			for (int i = 0; i < 8; i++)
			{
				posMoves.push_back(move * i);
			}
		}
	else
		posMoves = moves;

	return posMoves;
}

ChessCoordinate Chessman::GetCoord()
{
	return coord;
}

std::wstring Chessman::GetChessCoord()
{
	return this->coord.GetChessCoord();
}

void Chessman::Rotate()
{
	this->coord.y = abs(7 - this->coord.y);
}
