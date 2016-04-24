#pragma once
#include "GameMove.h"

using namespace mcts;

class Connect4GameMove :
	public GameMove
{
public:
	Connect4GameMove(int move);
	virtual ~Connect4GameMove();
	int GetMove() const;
	friend bool operator== (const Connect4GameMove& lhs, const Connect4GameMove& rhs);
private:
	virtual ostream& ToString(ostream& ostr) const override;
	int mMove;
};

namespace std
{
	template<> struct hash<Connect4GameMove>
	{
		typedef Connect4GameMove argument_type;
		typedef size_t result_type;
		result_type operator()(const argument_type& f) const
		{
			return std::hash<int>()(f.GetMove());
		}
	};
}

