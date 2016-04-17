#include "Connect4GameState.h"



Connect4GameState::Connect4GameState()
{
}


Connect4GameState::~Connect4GameState()
{
}

shared_ptr<GameState> Connect4GameState::Clone() const
{
	return shared_ptr<GameState>();
}

vector<shared_ptr<const GameMove>> Connect4GameState::GetMoves() const
{
	return vector<shared_ptr<const GameMove>>();
}

void Connect4GameState::DoMove(const GameMove & move)
{
}

double Connect4GameState::GetResult(int player) const
{
	return 0.0;
}

int Connect4GameState::GetWinner() const
{
	return 0;
}

const GameMove& Connect4GameState::GetSimulationMove() const
{
	return *mMoves[0];
}

int Connect4GameState::GetPlayerWhoJustMoved() const
{
	return 0;
}

bool Connect4GameState::IsTerminal() const
{
	return false;
}

shared_ptr<const GameMove> Connect4GameState::ParseMove(const string & move) const
{
	return shared_ptr<const GameMove>();
}
