#include "UCTTreeNodeCreator.h"
#include "UCTTreeNode.h"

using namespace mcts;

UCTTreeNodeCreator::UCTTreeNodeCreator(float constant /*= 1.0f*/)
	: mConstant(constant)
{
}

UCTTreeNodeCreator::~UCTTreeNodeCreator()
{
}

shared_ptr<TreeNode> UCTTreeNodeCreator::GenRootNode(const GameState& rootState) const
{
	return make_shared<UCTTreeNode>(nullptr, nullptr, rootState, mConstant);
}

ostream& UCTTreeNodeCreator::ToString(ostream & ostr) const
{
	ostr << "UCT" << mConstant;
	return ostr;
}
