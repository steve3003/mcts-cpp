#include "GhostInTheCellGameState.h"
#include "GhostInTheCellGameMove.h"
#include <algorithm>

GhostInTheCellGameState::GhostInTheCellGameState(const int(&graph)[FACTORIES][FACTORIES], const vector<vector<int>>& entities, int turn, int maxDepth) :
	mPlayerWhoJustMoved(2),
	mWinner(0),
	mNotWin(true),
	mGraph(graph),
	mTurn(turn),
	mMaxDepth(maxDepth)
{
	for (auto const& entity : entities)
	{
		int entityType = entity[1];
		if (entityType == 0)
		{
			vector<int> factory = { entity[0], entity[2], entity[3], entity[4], entity[5] };
			mFactories.push_back(move(factory));
		}
		else if (entityType == 1)
		{
			vector<int> troop = { entity[0], entity[2], entity[3], entity[4], entity[5], entity[6] };
			mTroops.push_back(move(troop));
		}
		else
		{
			vector<int> bomb = { entity[0], entity[2], entity[3], entity[4], entity[5] };
			mBombs.push_back(move(bomb));
		}
	}

	CalculateMoves();

	random_device rndDevice;
	randomEng = make_shared<mt19937>(rndDevice());
}

GhostInTheCellGameState::~GhostInTheCellGameState()
{
}

shared_ptr<GameState> GhostInTheCellGameState::Clone() const
{
	return make_shared<GhostInTheCellGameState>(*this);
}

vector<shared_ptr<const GameMove>> GhostInTheCellGameState::GetMoves() const
{
	return mMoves;
}

void GhostInTheCellGameState::DoMove(const GameMove& move)
{
	const auto& myMove = dynamic_cast<const GhostInTheCellGameMove&>(move);
	mPlayerWhoJustMoved = 3 - mPlayerWhoJustMoved;
	if (mPlayerWhoJustMoved == 2)
	{
		if (mPreviousMove != nullptr)
		{
			// update the game only if both players decided the move

			// Move existing troops
			vector<vector<int>> arrivedCount(mFactories.size(), vector<int>(2, 0));
			for (auto& troop : mTroops)
			{
				--troop[5];
				if (troop[5] == 0)
				{
					int factory = troop[3];
					int player = int(0.5f * (1 - troop[1]));
					arrivedCount[factory][player] += troop[4];
				}
			}
			mTroops.erase(
				remove_if(mTroops.begin(), mTroops.end(), [](const vector<int>& x) {return x[5] == 0; }),
				mTroops.end()
			);

			// Execute user orders
			ExecuteMove(*mPreviousMove, 1);
			ExecuteMove(myMove, 2);

			// Produce new cyborgs in all factories
			for (auto& factory : mFactories)
			{
				if (factory[4] == 0)
				{
					if (factory[1] != 0)
					{
						factory[2] += factory[3];
					}
				}
				else
				{
					--factory[4];
				}
			}

			auto size = mFactories.size();
			// Solve battles
			for (size_t i = 0; i < size; ++i)
			{
				int cyborgDiff = arrivedCount[i][0] - arrivedCount[i][1];
				if (cyborgDiff == 0)
				{
					continue;
				}

				int winPlayer = 0;
				int remainingArrived = cyborgDiff;
				if (cyborgDiff < 0)
				{
					winPlayer = 1;
					remainingArrived = -cyborgDiff;
				}

				auto& factory = mFactories[i];
				int player = factory[1] != 0 ? int(0.5f * (1 - factory[1])) : -1;
				if (player == winPlayer)
				{
					factory[2] += remainingArrived;
				}
				else
				{
					factory[2] -= remainingArrived;
					if (factory[2] < 0)
					{
						factory[2] = -factory[2];
						factory[1] = -2 * (winPlayer + 1) + 3;
					}
				}
			}

			//Make the bombs explode
			for (auto& bomb : mBombs)
			{
				--bomb[4];
				if (bomb[4] == 0)
				{
					int factory = bomb[3];
					int player = int(0.5f * (1 - bomb[1]));
					mFactories[factory][4] = 5;
					int& cyborg = mFactories[factory][2];
					cyborg = max(0, min(cyborg - 10, (int)ceil(0.5 * cyborg)));
				}
			}
			mBombs.erase(
				remove_if(mBombs.begin(), mBombs.end(), [](const vector<int>& x) {return x[4] == 0; }),
				mBombs.end()
			);

			// Check end conditions
			++mTurn;
			--mMaxDepth;
			if (mTurn == 200 || mMaxDepth <= 0)
			{
				vector<int> cyborg(2, 0);
				for (auto& troop : mTroops)
				{
					int player = int(0.5f * (1 - troop[1]));
					cyborg[player] += troop[4];
				}

				for (auto& factory : mFactories)
				{
					if (factory[1] != 0)
					{
						int player = int(0.5f * (1 - factory[1]));
						cyborg[player] += factory[2];
					}
				}

				mNotWin = false;
				if (cyborg[0] > cyborg[1])
				{
					mWinner = 1;
				}
				else if (cyborg[1] > cyborg[0])
				{
					mWinner = 2;
				}
				else
				{
					mWinner = 0;
				}
			}
			else
			{
				if (CheckLost(1))
				{
					if (CheckLost(-1))
					{
						mWinner = 0;
						mNotWin = false;
					}
					else
					{
						mWinner = 2;
						mNotWin = false;
					}
				}
				else
				{
					if (CheckLost(-1))
					{
						mWinner = 1;
						mNotWin = false;
					}
				}
			}
		}
	}

	mPreviousMove = make_shared<GhostInTheCellGameMove>(myMove);
	mMoves.clear();
	CalculateMoves();
}

double GhostInTheCellGameState::GetResult(int player) const
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

int GhostInTheCellGameState::GetWinner() const
{
	return mWinner;
}

const GameMove& GhostInTheCellGameState::GetSimulationMove() const
{
	uniform_int_distribution<int> dist(0, mMoves.size() - 1);
	return *mMoves[dist(*randomEng)];
}

int GhostInTheCellGameState::GetPlayerWhoJustMoved() const
{
	return mPlayerWhoJustMoved;
}

bool GhostInTheCellGameState::IsTerminal() const
{
	return mMoves.size() == 0;
}

shared_ptr<const GameMove> GhostInTheCellGameState::ParseMove(const string & move) const
{
	return shared_ptr<const GameMove>();
}

ostream& GhostInTheCellGameState::ToString(ostream & ostr) const
{
	return ostr;
}

void GhostInTheCellGameState::CalculateMoves()
{
	if (mNotWin)
	{
		// WAIT move
		mMoves.push_back(make_shared<GhostInTheCellGameMove>(vector<GhostInTheCellSubMove> {GhostInTheCellSubMove(0, 0, 0, 0)}));

		vector<GhostInTheCellSubMove> subMoves;
		auto size = mFactories.size();
		subMoves.reserve(size*size);

		vector<GhostInTheCellSubMove> incMoves;
		incMoves.reserve(size);

		int player = 3 - mPlayerWhoJustMoved;
		auto playerId = -2 * player + 3;

		/*bool anyFactoryToConquer = false;
		for (auto const& factory : mFactories)
		{
			if (factory[3] > 1 && factory[1] != playerId)
			{
				anyFactoryToConquer = true;
				break;
			}
		}*/

		for (auto const& factory : mFactories)
		{
			int cyborg = factory[2];
			if (cyborg <= 0)
			{
				continue;
			}

			int factoryId = factory[0];
			auto factoryLinks = mGraph[factoryId];
			int factoryOwner = factory[1];

			if (playerId == factoryOwner)
			{
				if (cyborg > 10 && factory[3] < 3)
				{
					//incMoves.push_back(GhostInTheCellSubMove(3, factoryId, 0, 0));
					subMoves.push_back(GhostInTheCellSubMove(3, factoryId, 0, 0));
				}

				// the player owns the factory
				for (size_t i = 0; i < size; ++i)
				{
					auto distance = factoryLinks[i];
					if (distance > 0 && distance < 5)
					{
						auto const& otherFactory = mFactories[i];
						if (otherFactory[1] != playerId)
						{
							auto cyborgToSend = cyborg >> 1;
							if (/*(factory[3] == 3 || cyborg - cyborgToSend > 10) &&*/ otherFactory[3] >= /*anyFactoryToConquer ? 1 :*/ 0)
							{
								subMoves.push_back(GhostInTheCellSubMove(1, factoryId, i, cyborgToSend));
							}
							if (otherFactory[1] != 0 && otherFactory[3] == 3 && otherFactory[4] == 0)
							{
								auto last = mBombs.end();
								auto pBomb = find_if(mBombs.begin(), last, [i](const vector<int>& x) { return x[3] == i; });
								if (pBomb == last)
								{
									subMoves.push_back(GhostInTheCellSubMove(2, factoryId, i, 0));
								}
							}
						}
					}
				}
			}
		}

		int length = subMoves.size();
		if (length > 0)
		{
			for (int i = 0; i < length; ++i)
			{
				for (int j = i + 1; j < length; ++j)
				{
					auto cell_sub_moves = vector<GhostInTheCellSubMove>{ subMoves[i], subMoves[j] };
					//cell_sub_moves.insert(cell_sub_moves.end(), incMoves.begin(), incMoves.end());
					mMoves.push_back(make_shared<GhostInTheCellGameMove>(move(cell_sub_moves)));
				}
			}
		}
		/*else if (incMoves.size() > 0)
		{
			mMoves.push_back(make_shared<GhostInTheCellGameMove>(move(incMoves)));
		}*/
	}
}

void GhostInTheCellGameState::ExecuteMove(const GhostInTheCellGameMove& move, int player)
{
	for (auto const& subMove : move.mSubMoves)
	{
		if (subMove.mMoveType == 0)
		{
			continue;
		}

		if (subMove.mMoveType == 1)
		{
			int owner = -2 * player + 3;
			auto& factory = mFactories[subMove.mSource];
			factory[2] -= subMove.mCyborgCount;
			vector<int> troop = { -1, owner, subMove.mSource, subMove.mDestination, subMove.mCyborgCount, mGraph[subMove.mSource][subMove.mDestination] };
			mTroops.push_back(std::move(troop));
			continue;
		}

		if (subMove.mMoveType == 2)
		{
			int owner = -2 * player + 3;
			vector<int> bomb = { -1, owner, subMove.mSource, subMove.mDestination, mGraph[subMove.mSource][subMove.mDestination] };
			mBombs.push_back(std::move(bomb));
		}

		auto& factory = mFactories[subMove.mSource];
		++factory[3];
	}
}

bool GhostInTheCellGameState::CheckLost(int player)
{
	for (auto& troop : mTroops)
	{
		if (troop[1] == player)
		{
			return false;
		}
	}

	for (auto& factory : mFactories)
	{
		if (factory[1] == player)
		{
			if (factory[2] > 0)
			{
				return false;
			}

			if (factory[3] > 0)
			{
				return false;
			}
		}
	}

	return true;
}
