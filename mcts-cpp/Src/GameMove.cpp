#include "GameMove.h"

ostream& mcts::operator<<(ostream & ostr, const GameMove & move)
{
	return move.ToString(ostr);
}
