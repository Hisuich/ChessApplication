#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	firstPlayer = new Player('W');
	secondPlayer = new Player('B');
	console = new Console();
	isFirstPlayerTurn = true;
	isGameStarted = false;
}

GameManager::~GameManager()
{
	delete firstPlayer;
	delete secondPlayer;
	delete console;
}

GameManager* GameManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}
	return instance;
}

void GameManager::MainMenu()
{
	std::wstring str;

	str += L"Welcome, to realy cool, super hard and incrediably simple game:\n";
	str += L"────────────────────────\n";
	str += L"      CHESS\n";
	str += L"────────────────────────\n";
	str += L"Input: \n";
	str += L"Start - to start game\n";
	str += L"Load - load old saved game\n";
	str += L"────────────────────────\n";
	str += L"In-Game Input: \n";
	str += L"Save - save game to continue it another time\n";
	str += L"Move x0,y0 x1,y1 - move your chess on x0,y0 coord to x1,y1 coord, beat enemy chessman if can\n";
	str += L"────────────────────────\n";
	str += L"Good Luck";

	console->ShowInfo(str);
}

void GameManager::StartGame()
{
	firstPlayer->GenerateChessmen();
	secondPlayer->GenerateChessmen();
	firstPlayer->Rotate();
	isFirstPlayerTurn = true;
	isGameStarted = true;
	console->ShowChess(firstPlayer, secondPlayer);
}

void GameManager::SaveGame()
{
	if (!isGameStarted)
	{
		console->ShowAdditionalInfo(L"The is not started yet");
		return;
	}
	std::wofstream file;
	file.open("save.chess", std::fstream::out | std::fstream::trunc);

	if (file.is_open())
	{
		file << (isFirstPlayerTurn ? L"W" : L"B") << std::endl;
		file << L"Player " << firstPlayer->color << std::endl;
		for (const auto& chessman : firstPlayer->chessmen)
			file << chessman->GetChessmanType() << ' ' << chessman->GetChessCoord() << std::endl;

		file << L"Player " << secondPlayer->color << std::endl;
		for (const auto& chessman : secondPlayer->chessmen)
			file << chessman->GetChessmanType() << ' ' << chessman->GetChessCoord() << std::endl;
	}
	else
	{
		std::wcout << L"There is no file" << std::endl;
	}
	file.close();

}

void GameManager::LoadGame()
{
	std::wifstream file;
	file.open("save.chess", std::fstream::in);

	if (file.is_open())
	{
		std::wstring str;

		wchar_t loadPlayer = ' ';

		vector<Chessman*> firstPlayerChessmen;
		King* firstPlayerKing = nullptr;

		vector<Chessman*> secondPlayerChessmen;
		King* secondPlayerKing = nullptr;

		bool isFirstPlayerTurn = true;

		while (getline(file, str))
		{
			vector<std::wstring> info = split(str, ' ');
			
			if (info.at(0) == L"W")
				isFirstPlayerTurn = true;
			if (info.at(0) == L"B")
				isFirstPlayerTurn = false;
			
			if (info.at(0) == L"Player")
			{ 
				if (info.at(1) == L"W")
					loadPlayer = 'W';
				else if (info.at(1) == L"B")
					loadPlayer = 'B';
				continue;
			}
			
			if (loadPlayer == ' ') continue;
			ChessCoordinate coord = ChessCoordinate(info.at(1));
			if (!coord.ValidateCoordinate())
			{
				continue;
			}

			Chessman* chessman = nullptr;
			if (info.at(0) == L"P")
			{
				if (loadPlayer == 'W')
					chessman = new Pawn(coord, true);
				else
					chessman = new Pawn(coord, false);
			}
			if (info.at(0) == L"R")
			{
				chessman = new Rook(coord);
			}
			if (info.at(0) == L"N")
			{
				chessman = new Knight(coord);
			}
			if (info.at(0) == L"B")
			{
				chessman = new Bishop(coord);
			}
			if (info.at(0) == L"Q")
			{
				chessman = new Queen(coord);
			}
			if (info.at(0) == L"K")
			{
				chessman = new King(coord);
			}
			if (chessman != nullptr)
			{
				if (loadPlayer == 'W')
				{
					if (chessman->GetChessmanType() == 'K')
						firstPlayerKing = (King*)chessman;
					firstPlayerChessmen.push_back(chessman);
				}
				if (loadPlayer == 'B')
				{
					if (chessman->GetChessmanType() == 'K')
						secondPlayerKing = (King*)chessman;
					secondPlayerChessmen.push_back(chessman);
				}
			}
		}

		bool isLoad = true;
		if (firstPlayerChessmen.empty() || secondPlayerChessmen.empty())
		{
			std::wcout << L"Save file is no valid" << std::endl;
			isLoad = false;
		}
		if (firstPlayerKing == nullptr)
		{
			std::wcout << L"First player don't have the king in Save file" << std::endl;
			isLoad = false;
		}
		if (secondPlayerKing == nullptr)
		{
			std::wcout << L"Second player don't have the king in Save file" << std::endl;
			isLoad = false;
		}

		if (isLoad)
		{
			firstPlayer->SetChessmen(firstPlayerChessmen);
			secondPlayer->SetChessmen(secondPlayerChessmen);
			firstPlayer->SetKing(firstPlayerKing);
			secondPlayer->SetKing(secondPlayerKing);
			this->isFirstPlayerTurn = isFirstPlayerTurn;
			isGameStarted = true;
		
			console->ShowChess(firstPlayer, secondPlayer);
		}
		else
		{
			for (auto b = begin(firstPlayerChessmen); b != end(firstPlayerChessmen); b++)
			{
				delete* b;
			}
			for (auto b = begin(secondPlayerChessmen); b != end(secondPlayerChessmen); b++)
			{
				delete* b;
			}
		}
			
	}
	else
	{
		std::wcout << L"There is no file" << std::endl;
	}
	file.close();
}

void GameManager::EndGame(std::wstring str)
{
	isGameStarted = false;
	std::wstring endMessage = str;
	endMessage += L"\nIf you want to start new game, pring \"Start\"\n";
	console->ShowAdditionalInfo(endMessage);

}

void GameManager::Turn()
{
	isFirstPlayerTurn = !isFirstPlayerTurn;

	firstPlayer->RemoveChessman();
	secondPlayer->RemoveChessman();

	firstPlayer->SetPossibleMoves(secondPlayer->chessmen);
	secondPlayer->SetPossibleMoves(firstPlayer->chessmen);

	firstPlayer->SetKingMoves(secondPlayer->possibleMoves);
	secondPlayer->SetKingMoves(firstPlayer->possibleMoves);

	firstPlayer->isCheck = secondPlayer->FindPossibleMove(firstPlayer->king->GetCoord());
	secondPlayer->isCheck = firstPlayer->FindPossibleMove(secondPlayer->king->GetCoord());

	isCheckMate();

	if (firstPlayer->isPawnInEnd() != nullptr)
	{
		Pawn* pawn = firstPlayer->isPawnInEnd();
		
		console->ShowAdditionalInfo(L"Congrats. Your pawn can transform.\n Choose one of this:\nRook, Knight, Bishop, Queen");
		while (firstPlayer->TransformPawn(pawn))
		{
			console->ShowAdditionalInfo(L"Congrats. Your pawn can transform.\n Choose one of this:\nRook, Knight, Bishop, Queen");
		}
	}
	
	if (secondPlayer->isPawnInEnd() != nullptr)
	{
		Pawn* pawn = secondPlayer->isPawnInEnd();
		
		console->ShowAdditionalInfo(L"Congrats. Your pawn can transform.\n Choose one of this:\nRook, Knight, Bishop, Queen");
		while (secondPlayer->TransformPawn(pawn))
		{
			console->ShowAdditionalInfo(L"Congrats. Your pawn can transform.\n Choose one of this:\nRook, Knight, Bishop, Queen");
		}
	}

	console->ShowChess(firstPlayer, secondPlayer);
	console->ShowAdditionalInfo(isFirstPlayerTurn ? L"White player turn" : L"Black player turn");

	if (firstPlayer->isCheckMate)
	{
		EndGame(L"Black Player win with incrediable checkmate. Congrats!!!");
	}
	else if (secondPlayer->isCheckMate)
	{
		EndGame(L"White Player win with incrediable checkmate. Congrats!!!");
	}

	else if (firstPlayer->StaleMate())
	{
		EndGame(L"Black Player set a stalemate. Bori-i-i-ing.");
	}
	else if (secondPlayer->StaleMate())
	{
		EndGame(L"White Player set a stalemate. Bori-i-i-ing.");
	}


}

void GameManager::Move(std::wstring strChessCoord, std::wstring strMoveCoord)
{
	ChessCoordinate chessCoord = GetCoord(strChessCoord);

	ChessCoordinate moveCoord = GetCoord(strMoveCoord);

	if (!(chessCoord.ValidateCoordinate()) || (!moveCoord.ValidateCoordinate()))
	{
		console->ShowAdditionalInfo(L"Incorrect input");
		return;
	}

	Player* currentPlayer = GetCurrentPlayer();
	Chessman* chessman = currentPlayer->GetChessman(chessCoord);
	if (currentPlayer->isCheck && chessman->GetChessmanType() != 'K')
	{
		console->ShowAdditionalInfo(L"You under check. Get your King out there.");
		return;
	}
	if (chessman == nullptr)
	{
		console->ShowAdditionalInfo(L"There is no chessman in set coord");
		return;
	}

	Chessman* enemyChessman = GetEnemyPlayer()->GetChessman(moveCoord);

	if (enemyChessman == nullptr)
	{
		bool isMove = currentPlayer->Move(chessman, moveCoord, GetEnemyPlayer()->chessmen);
		if (!isMove)
		{
			console->ShowAdditionalInfo(L"Can't move in set coord");
			return;
		}
		else
		{
		}
	}
	else
	{
		bool isBeat = currentPlayer->Beat(chessman, moveCoord, GetEnemyPlayer()->chessmen);
		if (!isBeat)
		{
			console->ShowAdditionalInfo(L"Can't beat chessman is set coord");
			return;
		}
		else
		{
			enemyChessman->isBeated = true;
		}
	}

	Turn();
	
}

void GameManager::isCheckMate()
{
	Player* curPlayer = GetCurrentPlayer();
	Player* enemyPlayer = GetEnemyPlayer();
	if (curPlayer->isCheck)
	{
		curPlayer->isCheckMate = true;
		for (const auto& chessman : enemyPlayer->chessmen)
		{
			enemyPlayer->PossibleMovesWithMissingChessman(curPlayer->chessmen, chessman);
			curPlayer->SetKingMoves(enemyPlayer->possibleMoves);

			curPlayer->isCheck = enemyPlayer->FindPossibleMove(curPlayer->king->GetCoord());

			if (curPlayer->king->canMove || !curPlayer->isCheck)
			{
				curPlayer->isCheckMate = false;
			}
		}
		curPlayer->isCheck = enemyPlayer->FindPossibleMove(curPlayer->king->GetCoord());
		enemyPlayer->SetPossibleMoves(curPlayer->chessmen);
		curPlayer->SetKingMoves(enemyPlayer->possibleMoves);
	}
}

void GameManager::SetPlayersSteps()
{
}

void GameManager::AwaitCommand()
{
	std::wstring cmd;
	getline(std::wcin, cmd);
	
	vector<std::wstring> cmds = split(cmd, ' ');
	
	if (cmds.empty())
		return;

	cmds[0] = toLowerCase(cmds[0]);

	if (cmds[0] == L"start")
	{
		StartGame();
	}
	else if (cmds[0] == L"save")
	{
		SaveGame();
	}
	else if (cmds[0] == L"load")
	{
		LoadGame();
	}
	else if (cmds[0] == L"exit")
	{
		isExit = true;
	}
	else if (cmds[0] == L"move")
	{
		if (!isGameStarted)
		{
			console->ShowAdditionalInfo(L"Game is not started");
			return;
		}

		if (cmds.size() != 3)
		{
			console->ShowAdditionalInfo(L"Incorrect input. Lacks parameters.");
			return;
		}
		
		Move(cmds[1],cmds[2]);
	}

}

vector<std::wstring> GameManager::split(std::wstring str, wchar_t delim)
{
	str = trim(str);
	vector<std::wstring> strs = {};
	size_t prev = 0;
	size_t cur = str.find(delim);
	while (cur != std::wstring::npos)
	{
		std::wstring curStr = str.substr(prev, cur-prev);
		//curStr = trim(curStr);
		if (curStr.empty())
		{
			prev = cur + 1;
			cur = str.find(delim, prev);
			continue;
		}
		strs.push_back(curStr);
		
		prev = cur + 1;
		cur = str.find(delim, prev);
	}
	strs.push_back(str.substr(prev, cur));
	return strs;
}

std::wstring GameManager::trim(std::wstring str)
{
	const std::wstring whitespaces = L"\t\n\v\f\r ";
	str.erase(0, str.find_first_not_of(whitespaces));
	str.erase(str.find_last_not_of(whitespaces) + 1);
	return str;
}

std::wstring GameManager::toLowerCase(std::wstring str)
{
	for (auto& ch : str)
	{
		ch = towlower(ch);
	}
	return str;
}

Player* GameManager::GetCurrentPlayer()
{
	if (isFirstPlayerTurn)
		return firstPlayer;
	else
		return secondPlayer;
}

Player* GameManager::GetEnemyPlayer()
{
	if (isFirstPlayerTurn)
		return secondPlayer;
	else
		return firstPlayer;
}

ChessCoordinate GameManager::GetCoord(std::wstring str)
{
	if (str.size() != 3)
	{
		return ChessCoordinate();
	}
	vector<std::wstring> moves = split(str, ',');
	wchar_t x = str[0];
	int y = -1;
	try {
		y = std::stoi(moves[1]);
	}
	catch (const std::invalid_argument& e)
	{

	}
	return ChessCoordinate(x, y);
}
