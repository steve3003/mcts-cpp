#pragma once

#include "TreeNodeCreator.h"

namespace mcts
{
	class MCTSAlgorithm
	{
	public:
		MCTSAlgorithm(const TreeNodeCreator& treeCreator);
		~MCTSAlgorithm();
		const shared_ptr<const GameMove> Search(const GameState& rootState, int iterations);
		void Abort();
		const TreeNodeCreator& GetTreeCreator();
	private:
		const TreeNodeCreator& mTreeCreator;
		bool mbSearch;
	};
}

