#include "TreeNode.h"

ostream& mcts::operator<<(ostream & ostr, const TreeNode & treeNode)
{
	return treeNode.ToString(ostr);
}
