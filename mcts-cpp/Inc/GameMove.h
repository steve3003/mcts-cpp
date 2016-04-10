#pragma once

#include <string>

using namespace std;

namespace mcts
{
	class GameMove
	{
	public:
		virtual ~GameMove() = 0;
		virtual string ToString() const = 0;
	};
}

