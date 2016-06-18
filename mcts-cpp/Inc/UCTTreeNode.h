#pragma once
#include "TreeNode.h"
#include <random>

namespace mcts
{
	class UCTTreeNode :
		public TreeNode
	{
	public:
		UCTTreeNode(shared_ptr<const GameMove> move, shared_ptr<UCTTreeNode> parent, const GameState& state, double constant = 1.0, bool generateUntriedMoves = true);
		virtual ~UCTTreeNode();
		UCTTreeNode(const UCTTreeNode& src);
		UCTTreeNode& operator=(const UCTTreeNode& rhs);
		UCTTreeNode(UCTTreeNode&& src) noexcept;
		UCTTreeNode& operator=(UCTTreeNode&& rhs) noexcept;

		virtual shared_ptr<TreeNode> AddChild(shared_ptr<const GameMove> move, shared_ptr<TreeNode> parent, const GameState& state) override;
		virtual shared_ptr<const GameMove> GetBestMove() const override;
		virtual bool HasChildren() const override;
		virtual bool HasMovesToTry() const override;
		virtual shared_ptr<const GameMove> GetMove() const override;
		virtual shared_ptr<TreeNode> GetParent() const override;
		virtual int GetPlayerWhoJustMoved() const override;
		virtual shared_ptr<TreeNode> SelectChild() const override;
		virtual shared_ptr<const GameMove> SelectUntriedMove() const override;
		virtual void Update(double result) override;

		virtual ostream& ChildrenToString(ostream& ostr) const override;
		virtual ostream& TreeToString(ostream& ostr, int indent) const override;
	protected:
		vector<shared_ptr<UCTTreeNode>> mChildNodes;
		vector<shared_ptr<const GameMove>> mUntriedMoves;
		int mVisits;
		double mConstant;
	private:
		void CopyFrom(const UCTTreeNode& src);
		void FreeMemory();
		void MoveFrom(const UCTTreeNode& src);
		virtual ostream& ToString(ostream& ostr) const override;
		double UCTValue() const;
		ostream& IndentString(ostream&, int indent) const;
		shared_ptr<UCTTreeNode> mParent;
		shared_ptr<const GameMove> mMove;
		double mWins;
		int mPlayerWhoJustMoved;
		shared_ptr<mt19937> randomEng;
	};
}

