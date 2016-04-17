#include "TreeNodeCreator.h"

ostream & mcts::operator<<(ostream & ostr, const TreeNodeCreator& treeNodeCreator)
{
	return treeNodeCreator.ToString(ostr);
}
