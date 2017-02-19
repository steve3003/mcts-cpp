#include "GameState.h"

namespace mcts
{
	ostream& operator<<(ostream& ostr, const GameState& state)
	{
		return state.ToString(ostr);
	}

	GameState::~GameState()
	{
	}
}
