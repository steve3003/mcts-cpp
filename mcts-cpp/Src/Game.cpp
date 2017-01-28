#include "Game.h"
#include "UCTTreeNodeCreator.h"
#include <iostream>
#include "MCTSAlgorithm.h"

namespace mcts
{
	Game::Game(int numOfPlayers) :
		mNumOfPlayers(numOfPlayers)
	{
		for (int i = 0; i < mNumOfPlayers; ++i)
		{
			PlayerSettings playerSettings;
			mPlayersSettings.push_back(playerSettings);
		}
	}

	Game::~Game()
	{
	}

	void Game::Play(GameState& state)
	{
		UCTTreeNodeCreator treeCreator;
		MCTSAlgorithm mcts(treeCreator);

		shared_ptr<const GameMove> move = nullptr;
		while (!state.IsTerminal())
		{
			cout << state;
			do
			{
				int nextPlayer = (state.GetPlayerWhoJustMoved() + 1) % mNumOfPlayers;
				auto playerSettings = mPlayersSettings[nextPlayer];
				if (playerSettings.isHuman)
				{
					cout << "Select move -> " << endl;
					string input;
					cin >> input;
					move = state.ParseMove(input);
				}
				else
				{
					move = mcts.Search(state, playerSettings.mctsIterations);
				}
			} while (move == nullptr);
			state.DoMove(*move);
			cout << "Player " << state.GetPlayerWhoJustMoved() << " Best move: " << *move << endl;
			//getchar();
		}
		cout << state;

		int winner = state.GetWinner();
		if (winner != 0) {
			cout << "Player " << winner << " wins!" << endl;
		}
		else {
			cout << "Nobody wins!" << endl;
		}
		getchar();
	}

	Game::PlayerSettings& Game::GetPlayerSettings(int player)
	{
		return mPlayersSettings[player];
	}

	Game::PlayerSettings::PlayerSettings(bool isHuman /*= false*/, int mctsIterations /*= 100*/) :
		isHuman(isHuman),
		mctsIterations(mctsIterations)
	{
	}
}
