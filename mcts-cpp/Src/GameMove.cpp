#include "GameMove.h"

namespace mcts
{
	ostream& operator<<(ostream & ostr, const GameMove & move)
	{
		return move.ToString(ostr);
	}

	GameMove::~GameMove()
	{
	}
}
