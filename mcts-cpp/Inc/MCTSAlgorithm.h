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

		shared_ptr<const GameMove> Search(const GameState& rootState, int iterations);
		shared_ptr<const GameMove> Search(const GameState& rootState, float time);
		void Abort();
		const TreeNodeCreator& GetTreeCreator() const;
		int GetLastIterations() const;
	private:
		const TreeNodeCreator& mTreeCreator;
		bool mbSearch;
		int mLastIterations;
		static void DoIteration(const GameState& rootState, shared_ptr<TreeNode> rootNode);
	};
}

