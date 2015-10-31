#include "UCTTreeNode.h"

using namespace mcts;

UCTTreeNode::UCTTreeNode(shared_ptr<const GameMove> move, shared_ptr<UCTTreeNode> parent, shared_ptr<const GameState> state,
	double constant /*= 1.0*/, bool generateUntriedMoves /*= true*/)
	: mMove(move), mParent(parent), mConstant(constant), mWins(0), mVisits(0)
{
	mPlayerWhoJustMoved = state->GetPlayerWhoJustMoved();
	if (generateUntriedMoves)
	{
		mUntriedMoves = state->GetMoves();
	}
}

int UCTTreeNode::GetPlayerWhoJustMoved() const
{
	return mPlayerWhoJustMoved;
}

shared_ptr<TreeNode> UCTTreeNode::GetParent() const
{
	return mParent;
}

shared_ptr<const GameMove> UCTTreeNode::GetMove() const
{
	return mMove;
}

UCTTreeNode::~UCTTreeNode()
{
}
