#pragma once

#include "ChessCoordinate.h"
#include "Chessman.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <vector>


using std::vector;

class Player
{
public:
	bool* possibleMoves;
	vector<Chessman*> chessmen;

	King* king;
	wchar_t color;

	bool isCheck;
	bool isCheckMate;

public:
	Player(wchar_t color);
	~Player();
	
	void Rotate();

	Chessman* GetChessman(ChessCoordinate coord);

	vector<ChessCoordinate> GetPass(ChessCoordinate startCoord, ChessCoordinate destCoord);
	bool isChessBlocked(Chessman* chessman, ChessCoordinate moveCoord, vector<Chessman*> enemyChessmen);

	bool Move(Chessman* chessman, ChessCoordinate nextCoord, vector<Chessman*> enemyChessmen);
	bool CanMove(Chessman* chessman, ChessCoordinate nextCoord, vector<Chessman*> enemyChessmen);

	bool Beat(Chessman* chessman, ChessCoordinate nextCoord, vector<Chessman*> enemyChessmen);
	bool CanBeat(Chessman* chessman, ChessCoordinate nextCoord, vector<Chessman*> enemyChessmen);

	bool Castling(vector<Chessman*> enemyChessmen, bool isLeft);
	Pawn* isPawnInEnd();
	bool TransformPawn(Pawn* pawn);

	void SetPossibleMoves(vector<Chessman*> enemyChessmen);
	void SetKingMoves(bool* enemyMoves);
	bool FindPossibleMove(ChessCoordinate coord);

	bool StaleMate();

	void GenerateChessmen();
	void SetChessmen(vector<Chessman*> chessmen);
	void SetKing(King* king);

	void RemoveChessman();
	void PossibleMovesWithMissingChessman(vector<Chessman*> enemyChessmen, Chessman* chessman);
};