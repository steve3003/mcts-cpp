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
	};
}

