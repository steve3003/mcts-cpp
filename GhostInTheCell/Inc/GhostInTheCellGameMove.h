#pragma once
#include "GameMove.h"
#include <vector>

using namespace mcts;

class GhostInTheCellSubMove
{
public:
	GhostInTheCellSubMove(int moveType, int source, int destination, int cyborgCount);
	virtual ~GhostInTheCellSubMove();

	int mMoveType;
	int mSource;
	int mDestination;
	int mCyborgCount;

	friend ostream& operator<<(ostream& ostr, const GhostInTheCellSubMove& move);
};

class GhostInTheCellGameMove :
	public GameMove
{
public:
	GhostInTheCellGameMove(const vector<GhostInTheCellSubMove>& subMoves);
	virtual ~GhostInTheCellGameMove();
	const vector<GhostInTheCellSubMove> mSubMoves;
private:
	virtual ostream& ToString(ostream & ostr) const override;
};

