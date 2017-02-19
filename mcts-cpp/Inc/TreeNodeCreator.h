#pragma once

#include <memory>
#include "TreeNode.h"

namespace mcts
{
	class TreeNodeCreator
	{
	public:
		virtual ~TreeNodeCreator() = 0;
		virtual shared_ptr<TreeNode> GenRootNode(const GameState& rootState) const = 0;
		friend ostream& operator<<(ostream& ostr, const TreeNodeCreator& treeNodeCreator);
	private:
		virtual ostream& ToString(ostream& ostr) const = 0;
	};
}

