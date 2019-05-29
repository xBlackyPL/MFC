#include <iostream>
#include <climits>
#include <ctime>

#include "BinaryTree.h"
#include <deque>
#include <random>

tree* create_rand_tree(const int count, const int min, const int max)
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	const std::uniform_int_distribution<int> uniform_int_distribution(min, max);

	const auto root = new_tree_node(rand() % (max - min + 1) + min);
	for (auto i = 0; i < count - 1; i++)
	{
		const auto new_val = uniform_int_distribution(generator);
		if (look_up(root, new_val) == nullptr)
		{
			insert_tree_node(root, new_val);
		}
		else
		{
			i--;
		}
	}
	return root;
}

tree* look_up(struct tree* node, const int key)
{
	if (node == nullptr)
	{
		return node;
	}
	if (node->data == key)
	{
		return node;
	}
	if (node->data < key)
	{
		return look_up(node->right, key);
	}
	return look_up(node->left, key);
}

tree* left_most(struct tree* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	while (node->left != nullptr)
	{
		node = node->left;
	}
	return node;
}

struct tree* new_tree_node(const int data)
{
	const auto node = new tree;
	node->data = data;
	node->left = nullptr;
	node->right = nullptr;
	node->parent = nullptr;

	return node;
}

struct tree* insert_tree_node(struct tree* node, const int data)
{
	static tree* p;
	if (node == nullptr)
	{
		const auto ret_node = new_tree_node(data);
		ret_node->parent = p;
		return ret_node;
	}
	if (data <= node->data)
	{
		p = node;
		node->left = insert_tree_node(node->left, data);
	}
	else
	{
		p = node;
		node->right = insert_tree_node(node->right, data);
	}
	return node;
}

void is_bst(struct tree* node)
{
	static auto last_data = INT_MIN;
	if (node == nullptr)
	{
		return;
	}

	is_bst(node->left);

	if (last_data < node->data)
	{
		last_data = node->data;
	}
	else
	{
		std::cout << "Not a BST" << std::endl;
		return;
	}
	is_bst(node->right);
}

int tree_size(struct tree* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	return tree_size(node->left) + 1 + tree_size(node->right);
}

int max_depth(struct tree* node)
{
	if (node == nullptr || (node->left == nullptr && node->right == nullptr))
	{
		return 0;
	}

	const auto left_depth = max_depth(node->left);
	const auto right_depth = max_depth(node->right);

	return left_depth > right_depth ? left_depth + 1 : right_depth + 1;
}

int min_depth(struct tree* node)
{
	if (node == nullptr || (node->left == nullptr && node->right == nullptr))
	{
		return 0;
	}

	const auto left_depth = min_depth(node->left);
	const auto right_depth = min_depth(node->right);

	return left_depth < right_depth ? left_depth + 1 : right_depth + 1;
}

bool is_balanced(struct tree* node)
{
	return max_depth(node) - min_depth(node) <= 1;
}

tree* min_tree(struct tree* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	while (node->left)
	{
		node = node->left;
	}
	return node;
}

tree* max_tree(struct tree* node)
{
	while (node->right)
	{
		node = node->right;
	}

	return node;
}

tree* successor_in_order(struct tree* node)
{
	if (node->right != nullptr)
	{
		return min_tree(node->right);
	}

	auto y = node->parent;
	while (y != nullptr && node == y->right)
	{
		node = y;
		y = y->parent;
	}
	return y;
}

tree* predecessor_in_order(struct tree* node)
{
	if (node->left != nullptr)
	{
		return max_tree(node->left);
	}

	auto y = node->parent;
	while (y != nullptr && node == y->left)
	{
		node = y;
		y = y->parent;
	}
	return y;
}

void reverse_order_print(struct tree* node)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->left == nullptr && node->right == nullptr)
	{
		std::cout << node->data << " ";
		return;
	}

	reverse_order_print(node->right);
	std::cout << node->data << " ";
	reverse_order_print(node->left);
}

tree* lowest_common_ancestor(tree* node, tree* p, tree* q)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	if (node->left == p || node->left == q || node->right == p || node->right == q)
	{
		return node;
	}

	auto left = lowest_common_ancestor(node->left, p, q);
	auto right = lowest_common_ancestor(node->right, p, q);
	if (left && right)
	{
		return node;
	}
	return (left) ? left : right;
}

void clear(struct tree* node)
{
	if (node != nullptr)
	{
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

void print_tree_in_order(struct tree* node)
{
	if (node == nullptr)
	{
		return;
	}

	print_tree_in_order(node->left);
	std::cout << node->data << " ";
	print_tree_in_order(node->right);
}

void print_tree_post_order(struct tree* node)
{
	if (node == nullptr)
	{
		return;
	}

	print_tree_post_order(node->left);
	print_tree_post_order(node->right);
	std::cout << node->data << " ";
}

void print_tree_pre_order(struct tree* node)
{
	if (node == nullptr)
	{
		return;
	}

	std::cout << node->data << " ";
	print_tree_pre_order(node->left);
	print_tree_pre_order(node->right);
}

void print_tree_reverse_order(struct tree* node)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->left == nullptr && node->right == nullptr)
	{
		std::cout << node->data << " ";
		return;
	}

	print_tree_reverse_order(node->right);
	std::cout << node->data << " ";
	print_tree_reverse_order(node->left);
}

void path_finder(struct tree* node, int path[], const int level)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->left == nullptr && node->right == nullptr)
	{
		path[level] = node->data;
		for (auto i = 0; i <= level; i++)
		{
			std::cout << static_cast<int>(path[i]);
		}
		std::cout << std::endl;
		return;
	}
	path[level] = node->data;
	path_finder(node->left, path, level + 1);
	path_finder(node->right, path, level + 1);
}

bool match_tree(tree* root1, tree* root2)
{
	if (root1 == nullptr && root2 == nullptr)
	{
		return true;
	}
	if (root1 == nullptr || root2 == nullptr)
	{
		return false;
	}
	if (root1->data != root2->data)
	{
		return false;
	}
	return (match_tree(root1->left, root2->left) &&
		match_tree(root1->right, root2->right));
}

bool sub_tree(tree* root1, tree* root2)
{
	if (root1 == nullptr)
	{
		return false;
	}
	if (root1->data == root2->data)
	{
		if (match_tree(root1, root2))
		{
			return true;
		}
	}
	return (sub_tree(root1->left, root2) || sub_tree(root1->right, root2));
}

bool is_sub_tree(tree* root1, tree* root2)
{
	if (root2 == nullptr)
	{
		return true;
	}
	return sub_tree(root1, root2);
}

void mirror(tree* root)
{
	if (root == nullptr)
	{
		return;
	}

	mirror(root->left);
	mirror(root->right);

	const auto tmp = root->right;
	root->right = root->left;
	root->left = tmp;
}

tree* add_to_bst(int array[], const int start, const int end)
{
	if (end < start)
	{
		return nullptr;
	}
	const auto mid = (start + end) / 2;

	const auto r = new tree;
	r->data = array[mid];
	r->left = add_to_bst(array, start, mid - 1);
	r->right = add_to_bst(array, mid + 1, end);
	return r;
}

tree* create_minimal_bst(int arr[], const int size)
{
	return add_to_bst(arr, 0, size - 1);
}

void breadth_first_traversal(tree* root)
{
	if (root == nullptr)
	{
		return;
	}
	std::deque<tree *> queue;
	queue.push_back(root);

	while (!queue.empty())
	{
		const auto p = queue.front();
		std::cout << p->data << " ";
		queue.pop_front();

		if (p->left != nullptr)
		{
			queue.push_back(p->left);
		}
		if (p->right != nullptr)
		{
			queue.push_back(p->right);
		}
	}
	std::cout << std::endl;
}

int get_level(struct tree* node, const int element, const int level)
{
	if (node == nullptr)
	{
		return 0;
	}
	if (element == node->data)
	{
		return level;
	}
	if (element < node->data)
	{
		return get_level(node->left, element, level + 1);
	}
	return get_level(node->right, element, level + 1);
}

void breadth_first_level_element_print(struct tree* root, std::vector<std::vector<int>>& vec)
{
	if (root == nullptr)
	{
		return;
	}
	std::deque<tree *> q;
	q.push_back(root);
	while (!q.empty())
	{
		const auto p = q.front();
		const auto lev = get_level(root, p->data, 0);
		vec[lev].push_back(p->data);
		q.pop_front();
		if (p->left) q.push_back(p->left);
		if (p->right)q.push_back(p->right);
	}
}

void tree_to_array(struct tree* node, int array[])
{
	static auto pos = 0;

	if (node)
	{
		tree_to_array(node->left, array);
		array[pos++] = node->data;
		tree_to_array(node->right, array);
	}
}

void level_even_odd(struct tree* node)
{
	if (node == nullptr)
	{
		return;
	}

	std::vector<int> even_vec;
	std::vector<int> odd_vec;
	std::deque<struct tree*> queue;
	queue.push_back(node);

	while (!queue.empty())
	{
		const auto p = queue.front();
		const auto level = get_level(node, p->data, 0);
		if (level % 2 == 0)
		{
			even_vec.push_back(p->data);
		}
		else
		{
			odd_vec.push_back(p->data);
		}
		queue.pop_front();
		if (p->left) queue.push_back(p->left);
		if (p->right) queue.push_back(p->right);
	}

	std::cout << "Even level elements : ";
	for (auto i : even_vec)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl << "Odd level elements : ";
	for (auto i : odd_vec)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}
