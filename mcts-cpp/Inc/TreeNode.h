#pragma once

#include "GameMove.h"
#include "GameState.h"
#include <memory>

namespace mcts
{
	class TreeNode
	{
	public:
		virtual ~TreeNode() = 0 {};
		virtual shared_ptr<TreeNode> AddChild(shared_ptr<const GameMove> move, const GameState& state) = 0;
		virtual shared_ptr<const GameMove> GetBestMove() const = 0;
		virtual bool HasChildren() const = 0;
		virtual bool HasMovesToTry() const = 0;
		virtual shared_ptr<const GameMove> GetMove() const = 0;
		virtual shared_ptr<TreeNode> GetParent() const = 0;
		virtual int GetPlayerWhoJustMoved() const = 0;
		virtual shared_ptr<TreeNode> SelectChild() const = 0;
		virtual shared_ptr<const GameMove> SelectUntriedMove() const = 0;
		virtual void Update(double result) = 0;

		virtual ostream& ChildrenToString(ostream& ostr) const = 0;
		virtual ostream& TreeToString(ostream& ostr, int indent) const = 0;
		friend ostream& operator<<(ostream& ostr, const TreeNode& treeNode);
	private:
		virtual ostream& ToString(ostream& ostr) const = 0;
	};
}

