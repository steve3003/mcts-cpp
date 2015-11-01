#pragma once
#include "TreeNode.h"

namespace mcts
{
	class UCTTreeNode :
		public TreeNode
	{
	public:
		UCTTreeNode(shared_ptr<const GameMove> move, shared_ptr<UCTTreeNode> parent, shared_ptr<const GameState> state, double constant = 1.0, bool generateUntriedMoves = true);
		virtual ~UCTTreeNode();
		virtual shared_ptr<TreeNode> AddChild(shared_ptr<const GameMove> move, shared_ptr<const GameState> state) override;
		virtual string ChildrenToString() const override;
		virtual shared_ptr<const GameMove> GetBestMove() const override;
		virtual bool HasChildren() const override;
		virtual bool HasMovesToTry() const override;
		virtual shared_ptr<const GameMove> GetMove() const override;
		virtual shared_ptr<TreeNode> GetParent() const override;
		virtual int GetPlayerWhoJustMoved() const override;
		virtual shared_ptr<TreeNode> SelectChild() const override;
		virtual shared_ptr<const GameMove> SelectUntriedMove() const override;
		virtual string ToString() const override;
		virtual string TreeToString(int indent) const override;
		virtual void Update(double result) override;
	protected:
		vector<shared_ptr<UCTTreeNode>> mChildNodes;
		vector<shared_ptr<const GameMove>> mUntriedMoves;
		int mVisits;
		double mConstant;
	private:
		shared_ptr<UCTTreeNode> mParent;
		shared_ptr<const GameMove> mMove;
		double mWins;
		int mPlayerWhoJustMoved;
		double UCTValue() const;
		string IndentString(int indent) const;
	};
}

