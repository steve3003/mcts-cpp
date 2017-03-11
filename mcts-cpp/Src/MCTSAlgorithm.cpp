#undef DEBUG

#include "MCTSAlgorithm.h"
#include <chrono>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace mcts
{
	MCTSAlgorithm::MCTSAlgorithm(const TreeNodeCreator& treeCreator) : mTreeCreator(treeCreator), mbSearch(true), mLastIterations(0)
	{
	}

	void MCTSAlgorithm::DoIteration(const GameState& rootState, shared_ptr<TreeNode> rootNode)
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
	}

	shared_ptr<const GameMove> MCTSAlgorithm::Search(const GameState& rootState, int iterations)
	{
		if (!mbSearch) {
			mbSearch = true;
		}

		shared_ptr<TreeNode> rootNode = mTreeCreator.GenRootNode(rootState);
		for (int i = 0; i < iterations; ++i)
		{
			DoIteration(rootState, rootNode);

			if (!mbSearch) {
				mbSearch = true;
				break;
			}
		}

#ifdef DEBUG
		rootNode->ChildrenToString(cout) << endl;
		//rootNode->TreeToString(cout, 0) << endl;
#endif // DEBUG

		mLastIterations = iterations;

		return rootNode->GetBestMove();
	}

	shared_ptr<const GameMove> MCTSAlgorithm::Search(const GameState& rootState, float time)
	{
		auto start = chrono::system_clock::now();

		if (!mbSearch) {
			mbSearch = true;
		}

		mLastIterations = 0;

		shared_ptr<TreeNode> rootNode = mTreeCreator.GenRootNode(rootState);
		while (true)
		{
			++mLastIterations;
			auto iterationStart = chrono::system_clock::now();

			DoIteration(rootState, rootNode);

			auto now = chrono::system_clock::now();
			auto iterationTime = (chrono::duration<double>(now - iterationStart)).count();
			auto totalTime = (chrono::duration<double>(now - start)).count();
			if (iterationTime + totalTime > time)
			{
				break;
			}

			if (!mbSearch)
			{
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

	const TreeNodeCreator& MCTSAlgorithm::GetTreeCreator() const
	{
		return mTreeCreator;
	}

	int MCTSAlgorithm::GetLastIterations() const
	{
		return mLastIterations;
	}

	void MCTSAlgorithm::Abort()
	{
		mbSearch = false;
	}

	MCTSAlgorithm::~MCTSAlgorithm()
	{
	}
}