#pragma once

#include "GameMove.h"
#include <vector>
#include <memory>

using namespace std;

namespace mcts
{
	class GameState
	{
	public:
		virtual ~GameState() = 0;
		virtual shared_ptr<GameState> Clone() const = 0;
		virtual vector<shared_ptr<const GameMove>> GetMoves() const = 0;
		virtual void DoMove(const GameMove& move) = 0;
		virtual double GetResult(int player) const = 0;
		virtual int GetWinner() const = 0;
		virtual const GameMove& GetSimulationMove() const = 0;
		virtual int GetPlayerWhoJustMoved() const = 0;
		virtual bool IsTerminal() const = 0;
		virtual shared_ptr<const GameMove> ParseMove(const string& move) const = 0;
	};
}

