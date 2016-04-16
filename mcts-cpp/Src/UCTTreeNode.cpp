#include "UCTTreeNode.h"
#include <algorithm>
#include <sstream>

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

	random_device rndDevice;
	randomEng = make_shared<mt19937>(rndDevice());
}

UCTTreeNode::~UCTTreeNode()
{
}

shared_ptr<TreeNode> UCTTreeNode::AddChild(shared_ptr<const GameMove> move, shared_ptr<const GameState> state)
{
	shared_ptr<UCTTreeNode> n = make_shared<UCTTreeNode>(move, make_shared<UCTTreeNode>(*this), state, mConstant);
	mUntriedMoves.erase(remove(mUntriedMoves.begin(), mUntriedMoves.end(), move), mUntriedMoves.end());
	mChildNodes.push_back(n);
	return n;
}

ostream& UCTTreeNode::ChildrenToString(ostream& ostr) const
{
	for (auto& c : mChildNodes) {
		ostr << c << endl;
	}
	return ostr;
}

shared_ptr<const GameMove> UCTTreeNode::GetBestMove() const
{
	vector<shared_ptr<UCTTreeNode>> sortedChildNodes(mChildNodes);
	sort(begin(sortedChildNodes), end(sortedChildNodes), [](shared_ptr<UCTTreeNode> x, shared_ptr<UCTTreeNode> y) { return x->mVisits > y->mVisits; });
	return sortedChildNodes[0]->mMove;
}

bool UCTTreeNode::HasChildren() const
{
	return mChildNodes.size() != 0;
}

bool UCTTreeNode::HasMovesToTry() const
{
	return mUntriedMoves.size() != 0;
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
	sort(begin(sortedChildNodes), end(sortedChildNodes), [](shared_ptr<UCTTreeNode> x, shared_ptr<UCTTreeNode> y) { return x->UCTValue() > y->UCTValue(); });
	return sortedChildNodes.at(0);
}

shared_ptr<const GameMove> UCTTreeNode::SelectUntriedMove() const
{
	uniform_int_distribution<int> dist(0, mUntriedMoves.size());
	return mUntriedMoves[dist(*randomEng)];
}

ostream& UCTTreeNode::ToString(ostream& ostr) const
{
	ostr << "[M:" << mMove << " W/V:" << mWins << "/" << mVisits + "]";
	return ostr;
}

ostream& UCTTreeNode::TreeToString(ostream& ostr, int indent) const
{
	IndentString(ostr, indent) << this;
	for (auto& c : mChildNodes)
	{
		c->TreeToString(ostr, indent + 1);
	}
	return ostr;
}

void UCTTreeNode::Update(double result)
{
	++mVisits;
	mWins += result;
}

double UCTTreeNode::UCTValue() const
{
	return mWins / mVisits + mConstant * sqrt(2 * log(mParent->mVisits) / mVisits);
}

ostream& UCTTreeNode::IndentString(ostream& ostr, int indent) const
{
	ostr << endl;
	for (int i = 1; i < indent + 1; ++i)
	{
		ostr << "| ";
	}
	return ostr;
}
