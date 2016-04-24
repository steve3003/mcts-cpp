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

ostream& Connect4GameMove::ToString(ostream & ostr) const
{
	ostr << mMove;
	return ostr;
}

bool operator==(const Connect4GameMove & lhs, const Connect4GameMove & rhs)
{
	return lhs.mMove == rhs.mMove;
}
