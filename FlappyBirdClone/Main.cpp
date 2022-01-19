#include "Bird.h"
#include "Game.h"

int main()
{
	Game* game = new Game();
	game->gameInitialization();
	game->gameLoop();
	return 0;
}