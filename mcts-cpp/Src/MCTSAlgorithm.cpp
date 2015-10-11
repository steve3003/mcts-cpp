#include "MCTSAlgorithm.h"

using namespace mcts;

MCTSAlgorithm::MCTSAlgorithm(const TreeNodeCreator& treeCreator) : mTreeCreator(treeCreator), mbSearch(true)
{
}

const GameMove& MCTSAlgorithm::Search(GameState& rootState, int iterations)
{
	if (!mbSearch) {
		mbSearch = true;
	}

	TreeNode& rootNode = mTreeCreator.GenRootNode(rootState);
	for (int i = 0; i < iterations; ++i)
	{
		TreeNode* node = &rootNode;
		GameState& state = rootState;

		// Select
		while (!node->HasMovesToTry() && node->HasChildren()) {
			node = &node->SelectChild();
			state.DoMove(node->GetMove());
		}

		// Expand
		if (node->HasMovesToTry()) {
			GameMove& move = node->SelectUntriedMove();
			state.DoMove(move);
			node = &node->AddChild(move, state);
		}

		// Rollout
		while (!state.IsTerminal()) {
			state.DoMove(state.GetSimulationMove());
		}

		// Backpropagate
		while (node != nullptr) {
			node->Update(state.GetResult(node->GetPlayerWhoJustMoved()));
			node = &node->GetParent();
		}

		if (!mbSearch) {
			mbSearch = true;
			break;
		}
	}

	return rootNode.GetBestMove();
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
