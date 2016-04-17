#pragma once
#include "GameState.h"

using namespace mcts;

class Connect4GameState :
	public GameState
{
public:
	Connect4GameState();
	virtual ~Connect4GameState();
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
	int mPlayerWhoJustMoved;
	int mCols;
	int mRows;
	int mBoard[6][7];
	int mWinner;
	bool mNotWin;
	bool mStateChanged;
	vector<shared_ptr<const GameMove>> mMoves;
};

