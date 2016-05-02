#include "Connect4GameState.h"
#include "Connect4GameMove.h"

const int Connect4GameState::directions[4][2] = { { 0, 1 },{ 1, 0 },{ 1, 1 },{ 1, -1 } };

Connect4GameState::Connect4GameState(int rows /*= 6*/, int cols /*= 7*/) :
	mPlayerWhoJustMoved(2),
	mCols(cols),
	mRows(rows),
	mWinner(0),
	mNotWin(true)
{
	vector<int> row(cols, 0);
	for (int i = 0; i < rows; ++i)
	{
		mBoard.push_back(row);
	}
	CalculateMoves();
}

shared_ptr<GameState> Connect4GameState::Clone() const
{
	return make_shared<Connect4GameState>(*this);
}

vector<shared_ptr<const GameMove>> Connect4GameState::GetMoves() const
{
	return mMoves;
}

void Connect4GameState::DoMove(const GameMove& move)
{
	const Connect4GameMove& f4Move = dynamic_cast<const Connect4GameMove&>(move);
	mPlayerWhoJustMoved = 3 - mPlayerWhoJustMoved;
	for (int i = mRows - 1; i >= 0; i--)
	{
		if (mBoard[i][f4Move.GetMove()] == 0)
		{
			mBoard[i][f4Move.GetMove()] = mPlayerWhoJustMoved;
			if (CheckWinDirections(mPlayerWhoJustMoved, i, f4Move.GetMove()))
			{
				mNotWin = false;
				mWinner = mPlayerWhoJustMoved;
			}
			break;
		}
	}

	CalculateMoves();
}

double Connect4GameState::GetResult(int player) const
{
	if (mWinner == 0)
	{
		return 0.5;
	}
	if (mWinner == player)
	{
		return 1.0;
	}
	return 0.0;
}

int Connect4GameState::GetWinner() const
{
	return mWinner;
}

const GameMove& Connect4GameState::GetSimulationMove() const
{
	return *mMoves[0];
}

int Connect4GameState::GetPlayerWhoJustMoved() const
{
	return mPlayerWhoJustMoved;
}

bool Connect4GameState::IsTerminal() const
{
	return mMoves.size() == 0;
}

shared_ptr<const GameMove> Connect4GameState::ParseMove(const string& move) const
{
	return dynamic_pointer_cast<const GameMove>(make_shared<const Connect4GameState>(stoi(move)));
}

ostream& Connect4GameState::ToString(ostream& ostr) const
{
	for (int i = 0; i < mRows; ++i)
	{
		for (int j = 0; j < mCols; ++j)
		{
			ostr << mBoard[i][j] << " ";
		}
		ostr << endl;
	}
	return ostr;
}

void Connect4GameState::CalculateMoves()
{
	if (mNotWin)
	{
		for (int j = 0; j < mCols; ++j)
		{
			if (mBoard[0][j] == 0)
			{
				mMoves.push_back(make_shared<Connect4GameMove>(j));
			}
		}
	}
}

bool Connect4GameState::CheckWinDirections(int player, int x, int y)
{
	for (int i = 0; i < 4; ++i)
	{
		if (Near(player, x, y, directions[i][0], directions[i][1])
			+ Near(player, x, y, -directions[i][0], -directions[i][1]) >= 3)
		{
			return true;
		}
	}

	return false;
}

int Connect4GameState::Near(int player, int x, int y, int dx, int dy)
{
	int count = 0;
	int i = x + dx;
	int j = y + dy;
	while (0 <= i && i < mRows && 0 <= j && j < mCols && mBoard[i][j] == player)
	{
		++count;
		i = i + dx;
		j = j + dy;
	}
	return count;
}
