#include "TreeNodeCreator.h"

namespace mcts
{
	ostream & operator<<(ostream & ostr, const TreeNodeCreator& treeNodeCreator)
	{
		return treeNodeCreator.ToString(ostr);
	}

	TreeNodeCreator::~TreeNodeCreator()
	{
	}
}
