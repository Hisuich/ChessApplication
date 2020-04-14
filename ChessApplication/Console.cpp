#include "Console.h"

Console::Console()
{
	SetConsole();
}

Console::~Console()
{
	delete[] screen;
}

void Console::SetConsole()
{
	screenWidth = 40;
	screenHeight = 30;
	
	infoOffsetX = 10;
	infoOffsetY = mainOffsetY + 22;

	mainOffsetX = 10;
	mainOffsetY = 1;

	screen = new wchar_t[screenWidth * screenHeight];
	
	Cleanse();

}

void Console::Cleanse()
{
	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
			screen[i * screenWidth + j] = ' ';

		screen[i * screenWidth + screenWidth - 1] = '\n';
	}
	screen[screenHeight * (screenWidth)] = '\0';
}

void Console::ShowInfo(std::wstring str)
{
	Cleanse();
	SetText(str, mainOffsetX, mainOffsetY);
	Draw();
}

void Console::ShowAdditionalInfo(std::wstring str)
{
	std::wstring newStr = L"\n─────────────────────────────\n";
	newStr += str;
	newStr += L"\n─────────────────────────────\n";
	SetText(newStr, infoOffsetX, infoOffsetY);
	Draw();
}

void Console::ShowChess(Player* first, Player* second)
{
	std::wstring str;
	
	ChessName chessmen[8 * 8];
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			Chessman* chessman;
			chessman = first->GetChessman({ j,i });
			if (chessman != nullptr)
			{
				chessmen[i * 8 + j][0] = first->color;
				chessmen[i * 8 + j][1] = chessman->GetChessmanType();
				continue;
			}
			chessman = second->GetChessman({ j,i });
			if (chessman != nullptr)
			{
				chessmen[i * 8 + j][0] = second->color;
				chessmen[i * 8 + j][1] = chessman->GetChessmanType();
				continue;
			}
			chessmen[i * 8 + j][0] = ' ';
			chessmen[i * 8 + j][1] = ' ';
		}
	}

	str += L"  a  b  c  d  e  f  g  h  \n";
	str += L" ┌──┬──┬──┬──┬──┬──┬──┬──┐\n";
	
	for (int i = 0; i < 8; i++)
	{
		str.push_back(49 + i);
		for (int j = 0; j < 8; j++)
		{
			str += L"|";
			str.push_back(chessmen[i * 8 + j][0]);
			str.push_back(chessmen[i * 8 + j][1]);
		}
		str += L"|\n";

		if (i < 7)
			str += L" ├──┼──┼──┼──┼──┼──┼──┼──┤\n";
		else
			str += L" └──┴──┴──┴──┴──┴──┴──┴──┘\n";
	}
	
	Cleanse();
	SetText(str, mainOffsetX, mainOffsetY);
	Draw();
}

void Console::SetText(std::wstring str, int offsetX, int offsetY)
{
	wchar_t* info = new wchar_t[str.size()];

	str.copy(info, str.size());
	//std::wcout << info;
	if (info != nullptr)
	{
		size_t chInd = 0;
		for (int i = offsetY; i < screenHeight; i++)
		{
			for (int j = offsetX; j < screenWidth - 1; j++)
			{
				if (chInd < str.size())
				{
					if (info[chInd] == '\n')
					{
						chInd++;
						break;
					}
					screen[i * screenWidth + j] = info[chInd];
					chInd++;
				}
				else
				{
					screen[i * screenWidth + j] = ' ';
				}
			}
		}
	}
}

void Console::Draw()
{
	system("cls");
	std::wcout << screen;
}