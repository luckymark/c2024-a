#pragma once
#include "Man.h"
#include "AI.h"
#include "Chess.h"
class ChessGame
{
public:

	ChessGame(Man* man, AI* ai, Chess* chess);
	void play();

	
private:
	Man* man;
	AI* ai;
	Chess* chess;
};