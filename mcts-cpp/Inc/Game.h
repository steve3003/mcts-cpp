#pragma once
#include "GameState.h"

namespace mcts
{
	class Game
	{
	public:

		struct PlayerSettings
		{
		public:
			bool isHuman;
			int mctsIterations;
			PlayerSettings(bool isHuman = false, int mctsIterations = 100);
		};

		Game(int numOfPlayers);
		virtual ~Game();
		void Play(GameState& state);
		PlayerSettings& GetPlayerSettings(int player);

	private:
		int mNumOfPlayers;
		vector<PlayerSettings> mPlayersSettings;
	};
}

