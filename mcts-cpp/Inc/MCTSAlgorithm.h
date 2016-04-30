#pragma once

#include "TreeNodeCreator.h"

namespace mcts
{
	class MCTSAlgorithm
	{
	public:
		MCTSAlgorithm(const TreeNodeCreator& treeCreator);
		virtual ~MCTSAlgorithm();
		MCTSAlgorithm(const MCTSAlgorithm& src) = delete;
		MCTSAlgorithm& operator=(const MCTSAlgorithm& rhs) = delete;
		MCTSAlgorithm(MCTSAlgorithm&& src) noexcept = delete;
		MCTSAlgorithm& operator=(MCTSAlgorithm&& rhs) noexcept = delete;

		const shared_ptr<const GameMove> Search(const GameState& rootState, int iterations);
		void Abort();
		const TreeNodeCreator& GetTreeCreator();
	private:
		const TreeNodeCreator& mTreeCreator;
		bool mbSearch;
	};
}

