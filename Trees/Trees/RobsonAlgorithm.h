#pragma once
#include "BinaryTree.h"

class robson_tree
{
	enum class visit_type { pre_order, in_order, post_order };

public:
	explicit robson_tree(tree*);

	~robson_tree() = default;

	explicit robson_tree(const tree&) = delete;

	explicit robson_tree(const tree&&) = delete;

	robson_tree& operator=(const robson_tree&);

	robson_tree& operator=(robson_tree&&) noexcept;

	void in_visit();

	void post_visit();

	void pre_visit();

private:
	void start();

	tree* root_;

	tree* previous_;

	tree* present_;

	tree* top_;

	tree* stack_;

	tree* avail_{};

	tree* next_{};

	visit_type visit_type_;
};
