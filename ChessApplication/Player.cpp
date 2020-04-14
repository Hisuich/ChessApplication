#include "Player.h"

Player::Player(wchar_t color)
{
	if (color != 'W' && color != 'B')
		this->color = 'W';

	else 
		this->color = color;
	
	this->chessmen = {};
	this->possibleMoves = new bool[8 * 8];
}

Player::~Player()
{
	delete[] possibleMoves;
	this->chessmen.clear();
	this->chessmen.shrink_to_fit();
}

void Player::GenerateChessmen()
{
	SetChessmen({});

	king = new King(ChessCoordinate(4, 0));
	for (int i = 0; i < 8; i++)
	{
		if (color == 'W')
			this->chessmen.push_back(new Pawn(ChessCoordinate(i, 1), true));
		else
			this->chessmen.push_back(new Pawn(ChessCoordinate(i, 1), false));
			
	}

	this->chessmen.push_back(new Rook(ChessCoordinate(0, 0)));
	this->chessmen.push_back(new Rook(ChessCoordinate(7, 0)));

	this->chessmen.push_back(new Knight(ChessCoordinate(1, 0)));
	this->chessmen.push_back(new Knight(ChessCoordinate(6, 0)));

	this->chessmen.push_back(new Bishop(ChessCoordinate(2, 0)));
	this->chessmen.push_back(new Bishop(ChessCoordinate(5, 0)));

	this->chessmen.push_back(new Queen(ChessCoordinate(3, 0)));

	this->chessmen.push_back(king);
}

void Player::SetChessmen(vector<Chessman*> chessmen)
{
	for (auto b = begin(this->chessmen); b != end(this->chessmen); b++)
	{
		delete* b;
	}
	this->chessmen.clear();
	this->chessmen.swap(chessmen);

}

void Player::SetKing(King* king)
{
	this->king = king;
}

void Player::Rotate()
{
	for (auto& chessman : this->chessmen)
	{
		chessman->Rotate();
	}
}

Chessman* Player::GetChessman(ChessCoordinate coord)
{
	for (const auto& chessman : this->chessmen)
	{
		if (chessman->GetCoord() == coord)
		{
			return chessman;
		}
	}
	return nullptr;
}

vector<ChessCoordinate> Player::GetPass(ChessCoordinate startCoord, ChessCoordinate destCoord)
{
	vector<ChessCoordinate> pass = {};
	ChessCoordinate passCoord = destCoord - startCoord;
	short xUnit = passCoord.x < 0 ? -1 : 1;
	short yUnit = passCoord.y < 0 ? -1 : 1;

	while (passCoord.x != 0 || passCoord.y != 0)
	{
		pass.push_back(startCoord + passCoord);
		passCoord.x = passCoord.x != 0 ? passCoord.x - xUnit : 0;
		passCoord.y = passCoord.y != 0 ? passCoord.y - yUnit : 0;
	}

	return pass;
}

bool Player::isChessBlocked(Chessman* chessman, ChessCoordinate moveCoord, vector<Chessman*> enemyChessmen)
{
	Chessman* chessmanOnCoord = GetChessman(moveCoord);

	if (chessmanOnCoord != nullptr)
		return true;

	if (chessman->canGoThrought)
	{
		return false;
	}

	vector<ChessCoordinate> pass = GetPass(chessman->GetCoord(), moveCoord);
	for (auto& coord : pass)
	{
		Chessman* chessmanOnPass = GetChessman(coord);
		if (chessmanOnPass != nullptr)
		{
			return true;
		}
		if (coord == moveCoord) continue;
		for (const auto& enemyChessman : enemyChessmen)
		{
			if (enemyChessman->GetCoord() == coord)
			{
				return true;
			}
		}
	}

	return false;
}

bool Player::Move(Chessman* chessman, ChessCoordinate nextCoord, vector<Chessman*> chessmen)
{
	if (CanMove(chessman, nextCoord, chessmen))
		return chessman->Move(nextCoord);
}

bool Player::CanMove(Chessman* chessman, ChessCoordinate nextCoord, vector<Chessman*> enemyChessmen)
{

	if (chessman->GetChessmanType() == 'K' && (king->GetCoord() + ChessCoordinate(2, 0) == nextCoord))
		return Castling(enemyChessmen, false);

	if (chessman->GetChessmanType() == 'K' && (king->GetCoord() + ChessCoordinate(-2, 0) == nextCoord))
		return Castling(enemyChessmen, true);

	if (chessman == nullptr)
	{
		return false;
	}

	if (isChessBlocked(chessman, nextCoord, enemyChessmen))
	{
		return false;
	}
	return true;
}

bool Player::Beat(Chessman* chessman, ChessCoordinate nextCoord, vector<Chessman*> chessmen)
{
	if (CanBeat(chessman, nextCoord, chessmen))
		return chessman->Beat(nextCoord);
}

bool Player::CanBeat(Chessman* chessman, ChessCoordinate nextCoord, vector<Chessman*> chessmen)
{
	if (chessman == nullptr)
	{
		return false;
	}

	if (isChessBlocked(chessman, nextCoord, chessmen))
	{
		return false;
	}

	return true;
}

bool Player::Castling(vector<Chessman*> enemyChessmen, bool isLeft)
{
	for (auto chessman : this->chessmen)
	{
		if (king->isFirstMove && chessman->GetChessmanType() == 'R' && ((Rook*)chessman)->isFirstMove)
		{
			if (isLeft)
			{
				ChessCoordinate dist = king->GetCoord() - chessman->GetCoord();
				if (dist.x < 0)
					continue;
				if (CanMove(chessman, king->GetCoord() + ChessCoordinate(-1, 0), enemyChessmen))
				{
					king->isCastling = true;
					chessman->Move(chessman->GetCoord() + ChessCoordinate(3, 0));
					return true;
				}
			}
			else
			{
				ChessCoordinate dist = king->GetCoord() - chessman->GetCoord();
				if (dist.x > 0)
					continue;
				if (CanMove(chessman, king->GetCoord()+ChessCoordinate(1,0), enemyChessmen))
				{
					king->isCastling = true;
					chessman->Move(chessman->GetCoord() + ChessCoordinate(-2, 0));
					return true;
				}
			}
		}
	}
	return false;
}

Pawn* Player::isPawnInEnd()
{
	for (auto chessman : this->chessmen)
	{
		if (chessman->GetChessmanType() == 'P')
		{
			Pawn* pawn = (Pawn*)chessman;
			if ((pawn->isDown && pawn->GetCoord().y == 0)
			|| (!pawn->isDown && pawn->GetCoord().y == 7))
			{
				TransformPawn(pawn);
			}
			
		}
	}
	return nullptr;
}

bool Player::TransformPawn(Pawn* pawn)
{
	std::wstring chessmanToTransform;
	std::wcin >> chessmanToTransform;

	Chessman* chessman;

	for (auto & ch : chessmanToTransform)
		ch = towlower(ch);

	if (chessmanToTransform == L"rook")
	{
		chessman = new Rook(pawn->GetCoord());
	}
	else if (chessmanToTransform == L"knight")
	{
		chessman = new Knight(pawn->GetCoord());
	}
	else if (chessmanToTransform == L"bishop")
	{
		chessman = new Bishop(pawn->GetCoord());
	}
	else if (chessmanToTransform == L"queen")
	{
		chessman = new Queen(pawn->GetCoord());
	}
	else
	{
		return false;
	}
	this->chessmen.push_back(chessman);
	pawn->isBeated = true;
	RemoveChessman();
}

void Player::SetPossibleMoves(vector<Chessman*> enemyChessmen)
{
	for (int i = 0; i < 64; i++)
	{
		possibleMoves[i] = false;
	}
	for (const auto& chessman : this->chessmen)
	{
		for (const auto& move : chessman->GetMoves())
		{
			ChessCoordinate nextMove = chessman->GetCoord() + move;
			if (!nextMove.ValidateCoordinate()) continue;
			if (CanMove(chessman, nextMove, enemyChessmen))
				possibleMoves[nextMove.y * 8 + nextMove.x] = true;
			if (CanBeat(chessman, nextMove, enemyChessmen))
				possibleMoves[nextMove.y * 8 + nextMove.x] = true;
		}
	}
}

void Player::SetKingMoves(bool* enemyMoves)
{
	king->SetPossibleMoves(this->possibleMoves);
	king->SetPossibleMovesWithEnemyMoves(enemyMoves);
}

bool Player::FindPossibleMove(ChessCoordinate coord)
{
	return possibleMoves[coord.y * 8 + coord.x];
}

bool Player::StaleMate()
{
	bool canMove = false;
	for (int i = 0; i < 64; i++)
		if (possibleMoves[i] == true)
			canMove = true;

	return !canMove;
}

void Player::RemoveChessman()
{
	auto beatedChessman = end(chessmen);
	for (auto chessman = begin(chessmen);chessman != end(chessmen);chessman++)
	{
		if ((*chessman)->isBeated)
		{
			beatedChessman = chessman;
			break;
		}
	}
	if (beatedChessman != end(chessmen))
	{
		chessmen.erase(beatedChessman);
		delete* beatedChessman;
	}
}

void Player::PossibleMovesWithMissingChessman(vector<Chessman*> enemyChessmen, Chessman* missChessman)
{

	for (const auto& chessman : this->chessmen)
	{
		if (missChessman == chessman)
			continue;

		for (const auto& move : chessman->GetMoves())
		{
			ChessCoordinate nextMove = chessman->GetCoord() + move;
			if (!nextMove.ValidateCoordinate()) continue;
			if (CanMove(chessman, nextMove, enemyChessmen))
				possibleMoves[nextMove.y * 8 + nextMove.x] = true;
			if (CanBeat(chessman, nextMove, enemyChessmen))
				possibleMoves[nextMove.y * 8 + nextMove.x] = true;
		}
	}

}

