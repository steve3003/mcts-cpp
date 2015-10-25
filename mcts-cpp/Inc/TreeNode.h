#pragma once

#include "GameMove.h"
#include "GameState.h"
#include <memory>

namespace mcts
{
	class TreeNode
	{
	public:
		virtual ~TreeNode() = 0;
		virtual shared_ptr<TreeNode> AddChild(shared_ptr<const GameMove> move, shared_ptr<const GameState> state) = 0;
		virtual string ChildrenToString() const = 0;
		virtual shared_ptr<const GameMove> GetBestMove() const = 0;
		virtual bool HasChildren() const = 0;
		virtual bool HasMovesToTry() const = 0;
		virtual shared_ptr<const GameMove> GetMove() const = 0;
		virtual shared_ptr<TreeNode> GetParent() const = 0;
		virtual int GetPlayerWhoJustMoved() const = 0;
		virtual shared_ptr<TreeNode> SelectChild() const = 0;
		virtual shared_ptr<const GameMove> SelectUntriedMove() const = 0;
		virtual string ToString() const = 0;
		virtual string TreeToString(int indent) const = 0;
		virtual void Update(double result) = 0;
	};
}

