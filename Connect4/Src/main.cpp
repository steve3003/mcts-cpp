
#include <iostream>
#include "MCTSAlgorithm.h"
#include "UCTTreeNodeCreator.h"
#include "Connect4GameState.h"

using namespace std;
using namespace mcts;

int main(int argc, char *argv[])
{
	UCTTreeNodeCreator treeCreator;
	MCTSAlgorithm mcts(treeCreator);
	Connect4GameState state;

	shared_ptr<const GameMove> move = nullptr;
	while (!state.IsTerminal())
	{
		cout << state;
		do
		{
			if (state.GetPlayerWhoJustMoved() % 2 == 1)
			{
				move = mcts.Search(state, 1000);
			}
			else
			{
				cout << "Select move -> " << endl;
				string input;
				cin >> input;
				move = state.ParseMove(input);
			}
			state.DoMove(*move);
		} while (move == nullptr);
		cout << "Player " << state.GetPlayerWhoJustMoved() << " Best move: " << *move << endl;
		//getchar();
	}
	cout << state;

	int winner = state.GetWinner();
	if (winner != 0) {
		cout << "Player " << winner << " wins!" << endl;
	}
	else {
		cout << "Nobody wins!" << endl;
	}
	getchar();
	return 0;
}