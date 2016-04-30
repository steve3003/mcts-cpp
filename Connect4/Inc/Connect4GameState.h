#pragma once
#include "GameState.h"

using namespace mcts;

class Connect4GameState :
	public GameState
{
public:
	Connect4GameState(int rows = 6, int cols = 7);
	virtual GameState& Clone() const override;
	virtual vector<shared_ptr<const GameMove>> GetMoves() const override;
	virtual void DoMove(const GameMove& move) override;
	virtual double GetResult(int player) const override;
	virtual int GetWinner() const override;
	virtual const GameMove& GetSimulationMove() const override;
	virtual int GetPlayerWhoJustMoved() const override;
	virtual bool IsTerminal() const override;
	virtual shared_ptr<const GameMove> ParseMove(const string& move) const override;
private:
	const static int directions[4][2];
	int mPlayerWhoJustMoved;
	int mCols;
	int mRows;
	vector<vector<int>> mBoard;
	int mWinner;
	bool mNotWin;
	vector<shared_ptr<const GameMove>> mMoves;
	void CalculateMoves();
	bool CheckWinDirections(int player, int x, int y);
	int Near(int player, int x, int y, int dx, int dy);
};

