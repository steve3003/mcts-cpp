#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include "GhostInTheCellGameState.h"
#include "MCTSAlgorithm.h"
#include "UCTTreeNodeCreator.h"
#include "Constants.h"

using namespace std;

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/
int main()
{
	int graph[FACTORIES][FACTORIES];

	for (int i = 0; i < FACTORIES; ++i)
	{
		for (int j = 0; j < FACTORIES; ++j)
		{
			graph[i][j] = -1;
		}
	}

	int factoryCount; // the number of factories
	cin >> factoryCount;
	cin.ignore();
	//cerr << factoryCount << endl;
	int linkCount; // the number of links between factories
	cin >> linkCount;
	cin.ignore();
	//cerr << linkCount << endl;
	for (int i = 0; i < linkCount; ++i)
	{
		int factory1;
		int factory2;
		int distance;
		cin >> factory1 >> factory2 >> distance;
		cin.ignore();
		//cerr << factory1 << " " << factory2 << " " << distance << endl;
		graph[factory1][factory2] = distance;
		graph[factory2][factory1] = distance;
	}
	vector<vector<int>> bombs;
	bombs.reserve(4);
	vector<vector<int>> entities;
	entities.reserve(1000);

	UCTTreeNodeCreator treeCreator;
	MCTSAlgorithm mcts(treeCreator);
	auto turn = 0;

	// game loop
	while (true)
	{
		entities.clear();
		int entityCount; // the number of entities (e.g. factories and troops)
		cin >> entityCount;
		cin.ignore();
		//cerr << entityCount << endl;
		for (auto i = 0; i < entityCount; ++i)
		{
			int entityId;
			string entityType;
			int arg1;
			int arg2;
			int arg3;
			int arg4;
			int arg5;
			cin >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5;
			cin.ignore();
			//cerr << entityId << " " << entityType << " " << arg1 << " " << arg2 << " " << arg3 << " " << arg4 << " " << arg5 << endl;
			int entityTypeId = entityType == "FACTORY" ? 0 : (entityType == "TROOP" ? 1 : 2);
			if (entityTypeId == 2 && arg1 == -1)
			{
				auto last = bombs.end();
				auto pBomb = find_if(bombs.begin(), last, [entityId](const vector<int>& x) { return x[0] == entityId; });
				if (pBomb != last)
				{
					vector<int>& bomb = *pBomb;
					--bomb[2];
					if (bomb[2] < 0)
					{
						auto min = min_element(graph[arg2], graph[arg2] + FACTORIES, [](int x, int y) { return x < y && x != -1; });
						bomb[2] = *min;
					}
					arg3 = bomb[1];
					arg4 = bomb[2];
				}
				else
				{
					auto min = min_element(graph[arg2], graph[arg2] + FACTORIES, [](int x, int y) { return x < y && x != -1; });
					arg4 = *min;
					arg3 = distance(graph[arg2], min);
					vector<int> bomb = { entityId, arg3, arg4 };
					bombs.push_back(move(bomb));
				}
			}
			vector<int> entity = { entityId, entityTypeId, arg1, arg2, arg3, arg4, arg5 };
			entities.push_back(move(entity));
		}

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: //cerr << "Debug messages..." << endl;
		GhostInTheCellGameState state(graph, entities, turn++, 8);
		auto move = mcts.Search(state, turn > 1 ? 0.041f : 0.09f);
		//cerr << mcts.GetLastIterations() << endl;

		// Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
		cout << *move << endl;
	}
}
