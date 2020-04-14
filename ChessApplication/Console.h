#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include "Player.h"

typedef wchar_t ChessName[2];


class Console
{
private:
	int screenWidth;
	int screenHeight;

	int infoOffsetX;
	int infoOffsetY;

	int mainOffsetX;
	int mainOffsetY;

	wchar_t* screen;

public:
	Console();
	~Console();

	void SetConsole();

	void Cleanse();

	void ShowChess(Player* first, Player* second);
	void ShowInfo(std::wstring str);
	void ShowAdditionalInfo(std::wstring str);
	
	
private:
	void SetText(std::wstring str, int offsetX, int offsetY);
	void Draw();
};