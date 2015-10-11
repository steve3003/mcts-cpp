#pragma once

#include "GameMove.h"
#include <vector>

using namespace std;

namespace mcts
{
	class GameState
	{
	public:
		virtual ~GameState() = 0;
		virtual vector<GameMove> GetMoves() const = 0;
		virtual void DoMove(const GameMove& move) = 0;
		virtual double GetResult(int player) const = 0;
		virtual int GetWinner() const = 0;
		virtual GameMove& GetSimulationMove() const = 0;
		virtual int GetPlayerWhoJustMoved() const = 0;
		virtual bool IsTerminal() const = 0;
		virtual GameMove& ParseMove(const string& move) const = 0;
	};
}

