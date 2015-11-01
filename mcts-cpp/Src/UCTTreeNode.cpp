#include "UCTTreeNode.h"
#include <algorithm>

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

UCTTreeNode::~UCTTreeNode()
{
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

shared_ptr<TreeNode> UCTTreeNode::SelectChild() const
{
	vector<shared_ptr<UCTTreeNode>> sortedChildNodes(mChildNodes);
	sort(begin(sortedChildNodes), end(sortedChildNodes), [](shared_ptr<UCTTreeNode> x, shared_ptr<UCTTreeNode> y){ return x->UCTValue() > y->UCTValue(); });
	return sortedChildNodes.at(0);
}
