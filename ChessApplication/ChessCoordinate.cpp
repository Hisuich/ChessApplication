#include "ChessCoordinate.h"

ChessCoordinate::ChessCoordinate() 
{
	this->x = -1;
	this->y = -1;
}

ChessCoordinate::ChessCoordinate(int x, int y)
{
	this->x = x;
	this->y = y;
}

ChessCoordinate::ChessCoordinate(wchar_t ChessX, int ChessY)
{
	this->x = GetX(ChessX);
	this->y = ChessY - 1;
}

ChessCoordinate::ChessCoordinate(std::wstring ChessCoord)
{
	if (ChessCoord.size() != 2)
	{
		this->x = -1;
		this->y = -1;
	}
	this->x = GetX(ChessCoord[0]);
	this->y = ChessCoord[1] - 49;
}

bool ChessCoordinate::ValidateCoordinate()
{
	if (x < 0 || x > 7 || 
		y < 0 || y > 7)
	{
		return false;
	}
	return true;
}

int ChessCoordinate::GetX(wchar_t x)
{
	if (x < 97 || x > 104)
	{
		std::wcout << L"Incorrect X coordinate: " << x << std::endl;
		return -1;
	}
	return (x - 97);
}

std::wstring ChessCoordinate::GetChessCoord()
{
	wchar_t x = this->x + 97;
	std::wstring str;
	str += x;
	str += this->y + 49;
	return std::wstring(str);
}

ChessCoordinate ChessCoordinate::operator-(const ChessCoordinate& coord)
{
	return ChessCoordinate(this->x - coord.x, this->y - coord.y);
}

ChessCoordinate ChessCoordinate::operator+(const ChessCoordinate& coord)
{
	return ChessCoordinate(this->x + coord.x, this->y + coord.y);
}

ChessCoordinate ChessCoordinate::operator*(const int& number)
{
	return ChessCoordinate(this->x * number, this->y * number);
}

bool ChessCoordinate::operator==(const ChessCoordinate& coord)
{
	return (this->x == coord.x) && (this->y == coord.y);
}