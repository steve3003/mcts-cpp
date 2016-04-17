#pragma once
#include "TreeNodeCreator.h"

namespace mcts
{
	class UCTTreeNodeCreator :
		public TreeNodeCreator
	{
	public:
		UCTTreeNodeCreator(float constant = 1.0f);
		virtual ~UCTTreeNodeCreator();
		virtual shared_ptr<TreeNode> GenRootNode(const GameState& rootState) const  override;
	private:
		virtual ostream& ToString(ostream& ostr) const override;
		float mConstant;
	};
}

