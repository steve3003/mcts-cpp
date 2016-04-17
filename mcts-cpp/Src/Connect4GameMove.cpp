#include "Connect4GameMove.h"



Connect4GameMove::Connect4GameMove(int move) :
	mMove(move)
{
}


Connect4GameMove::~Connect4GameMove()
{
}

int Connect4GameMove::GetMove() const
{
	return mMove;
}

bool Connect4GameMove::operator==(const Connect4GameMove& move) const
{
	return mMove == move.mMove;
}

ostream & Connect4GameMove::ToString(ostream & ostr) const
{
	ostr << mMove;
	return ostr;
}
