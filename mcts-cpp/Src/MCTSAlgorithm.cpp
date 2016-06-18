#define DEBUG

#include "MCTSAlgorithm.h"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace mcts
{
	MCTSAlgorithm::MCTSAlgorithm(const TreeNodeCreator& treeCreator) : mTreeCreator(treeCreator), mbSearch(true)
	{
	}

	const shared_ptr<const GameMove> MCTSAlgorithm::Search(const GameState& rootState, int iterations)
	{
		if (!mbSearch) {
			mbSearch = true;
		}

		shared_ptr<TreeNode> rootNode = mTreeCreator.GenRootNode(rootState);
		for (int i = 0; i < iterations; ++i)
		{
			shared_ptr<TreeNode> node = rootNode;
			shared_ptr<GameState> state = rootState.Clone();

			// Select
			while (!node->HasMovesToTry() && node->HasChildren()) {
				node = node->SelectChild();
				state->DoMove(*node->GetMove());
			}

			// Expand
			if (node->HasMovesToTry()) {
				shared_ptr<const GameMove> move = node->SelectUntriedMove();
				state->DoMove(*move);
				node = node->AddChild(move, node, *state);
			}

			// Rollout
			while (!state->IsTerminal()) {
				state->DoMove(state->GetSimulationMove());
			}

			// Backpropagate
			while (node != nullptr) {
				node->Update(state->GetResult(node->GetPlayerWhoJustMoved()));
				node = node->GetParent();
			}

			if (!mbSearch) {
				mbSearch = true;
				break;
			}
		}

#ifdef DEBUG
		rootNode->ChildrenToString(cout) << endl;
		//rootNode->TreeToString(cout, 0) << endl;
#endif // DEBUG

		return rootNode->GetBestMove();
	}

	const TreeNodeCreator& MCTSAlgorithm::GetTreeCreator()
	{
		return mTreeCreator;
	}

	void MCTSAlgorithm::Abort()
	{
		mbSearch = false;
	}

	MCTSAlgorithm::~MCTSAlgorithm()
	{
	}
}