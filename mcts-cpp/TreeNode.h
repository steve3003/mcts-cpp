#pragma once

#include "GameMove.h"
#include "GameState.h"

namespace mcts
{
	class TreeNode
	{
		virtual TreeNode& AddChild(const GameMove& move, const GameState& state) = 0;
		virtual string ChildrenToString() const = 0;
		virtual GameMove& GetBestMove() const = 0;
		virtual bool HasChildren() const = 0;
		virtual bool HasMovesToTry() const = 0;
		virtual GameMove& GetMove() const = 0;
		virtual TreeNode& GetParent() const = 0;
		virtual int GetPlayerWhoJustMoved() const = 0;
		virtual TreeNode& SelectChild() const = 0;
		virtual GameMove& SelectUntriedMove() const = 0;
		virtual string ToString() const = 0;
		virtual string TreeToString(int indent) const = 0;
		virtual void Update(double result) = 0;
	};
}

