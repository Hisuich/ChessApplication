#pragma once

#include "Player.h"
#include "Console.h"
#include <iostream>
#include <fstream>

class GameManager
{
public:
	bool isExit;

private:
	static GameManager* instance;

	Console* console;

	Player* firstPlayer;
	Player* secondPlayer;
	
	bool isFirstPlayerTurn;
	bool isGameStarted;

private:
	GameManager();

public:
	static GameManager* GetInstance();

	~GameManager();

	void MainMenu();
	void StartGame();
	void SaveGame();
	void LoadGame();
	void EndGame(std::wstring str);
	void Turn();
	void Move(std::wstring chessCoord, std::wstring moveCoord);
	void isCheckMate();
	void SetPlayersSteps();
	void AwaitCommand();

private:
	vector<std::wstring> split(std::wstring str, wchar_t delim);
	std::wstring trim(std::wstring str);
	std::wstring toLowerCase(std::wstring str);

	Player* GetCurrentPlayer();
	Player* GetEnemyPlayer();

	ChessCoordinate GetCoord(std::wstring str);
};