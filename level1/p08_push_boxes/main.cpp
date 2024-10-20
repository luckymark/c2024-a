#pragma optimize("t", on)
#include "Graphic_Logic.h"
#include "Game_Logic.h"
#include<Windows.h>
int WINAPI WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrev, _In_ LPSTR lpCline, _In_ int nCShow) {
	Game game;
	game.play();
	return 0;
}