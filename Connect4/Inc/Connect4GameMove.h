#pragma once
#include "GameMove.h"

using namespace mcts;

class Connect4GameMove :
	public GameMove
{
public:
	Connect4GameMove(int move);
	virtual ~Connect4GameMove();
	int GetMove() const;
	bool operator== (const Connect4GameMove& move) const;
private:
	virtual ostream& ToString(ostream& ostr) const override;
	int mMove;
};

