#include "Connect4GameState.h"
#include "Game.h"

using namespace mcts;

int main(int argc, char *argv[])
{
	Connect4GameState state;
	Game game(2);
	Game::PlayerSettings& p1Settings = game.GetPlayerSettings(0);
	p1Settings.isHuman = true;
	Game::PlayerSettings& p2Settings = game.GetPlayerSettings(1);
	p2Settings.mctsIterations = 10000;

	game.Play(state);

	return 0;
}