#include "TreeNode.h"

namespace mcts
{
	ostream& operator<<(ostream & ostr, const TreeNode & treeNode)
	{
		return treeNode.ToString(ostr);
	}

	TreeNode::~TreeNode()
	{
	}
}
