#pragma once

#include "TreeNode.h"

namespace mcts
{
	class TreeNodeCreator
	{
	public:
		virtual ~TreeNodeCreator() = 0;
		virtual TreeNode& GenRootNode(const GameState& rootState) const = 0;
	};
}

