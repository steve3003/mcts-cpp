#include "GhostInTheCellGameMove.h"


GhostInTheCellGameMove::GhostInTheCellGameMove(const vector<GhostInTheCellSubMove>& subMoves) :
	mSubMoves(subMoves)
{
}

GhostInTheCellGameMove::~GhostInTheCellGameMove()
{
}

ostream& GhostInTheCellGameMove::ToString(ostream& ostr) const
{
	int length = mSubMoves.size();
	if (length > 0)
	{
		ostr << mSubMoves[0];
		for (int i = 1; i < length; ++i)
		{
			ostr << ";" << mSubMoves[i];
		}
	}
	return ostr;
}

GhostInTheCellSubMove::GhostInTheCellSubMove(int moveType, int source, int destination, int cyborgCount) :
	mMoveType(moveType),
	mSource(source),
	mDestination(destination),
	mCyborgCount(cyborgCount)
{
}

GhostInTheCellSubMove::~GhostInTheCellSubMove()
{
}

ostream& operator<<(ostream& ostr, const GhostInTheCellSubMove& move)
{
	if (move.mMoveType == 0)
	{
		ostr << "WAIT";
	}
	else if (move.mMoveType == 1)
	{
		ostr << "MOVE " << move.mSource << " " << move.mDestination << " " << move.mCyborgCount;
	}
	else if (move.mMoveType == 2)
	{
		ostr << "BOMB " << move.mSource << " " << move.mDestination;
	}
	else if (move.mMoveType == 3)
	{
		ostr << "INC " << move.mSource;
	}
	return ostr;
}
