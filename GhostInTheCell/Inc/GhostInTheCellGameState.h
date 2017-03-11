#pragma once
#include "GameState.h"
#include "Constants.h"
#include "GhostInTheCellGameMove.h"
#include <random>

using namespace mcts;

class GhostInTheCellGameState :
	public GameState
{
public:
	GhostInTheCellGameState(const int(&graph)[FACTORIES][FACTORIES], const vector<vector<int>>& entities, int turn, int maxDepth);
	virtual ~GhostInTheCellGameState();
	virtual shared_ptr<GameState> Clone() const override;
	virtual vector<shared_ptr<const GameMove>> GetMoves() const override;
	virtual void DoMove(const GameMove& move) override;
	virtual double GetResult(int player) const override;
	virtual int GetWinner() const override;
	virtual const GameMove& GetSimulationMove() const override;
	virtual int GetPlayerWhoJustMoved() const override;
	virtual bool IsTerminal() const override;
	virtual shared_ptr<const GameMove> ParseMove(const string& move) const override;
private:
	virtual ostream& ToString(ostream& ostr) const override;
	int mPlayerWhoJustMoved;
	int mWinner;
	bool mNotWin;
	const int(&mGraph)[FACTORIES][FACTORIES];
	vector<vector<int>> mFactories;
	vector<vector<int>> mTroops;
	vector<vector<int>> mBombs;
	vector<shared_ptr<const GameMove>> mMoves;
	shared_ptr<const GhostInTheCellGameMove> mPreviousMove;
	int mTurn;
	int mMaxDepth;
	void CalculateMoves();
	void ExecuteMove(const GhostInTheCellGameMove& move, int player);
	bool CheckLost(int player);
	shared_ptr<mt19937> randomEng;
};

