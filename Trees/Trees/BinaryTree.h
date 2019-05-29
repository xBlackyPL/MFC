#pragma once
#include <vector>

struct tree
{
	int data;
	tree* left;
	tree* right;
	tree* parent;
};

tree* look_up(struct tree* node, int key);

tree* left_most(struct tree* node);

tree* min_tree(struct tree* node);

tree* max_tree(struct tree* node);

tree* successor_in_order(struct tree* node);

tree* predecessor_in_order(struct tree* node);

tree* new_tree_node(int data);

tree* insert_tree_node(struct tree* node, int data);

tree* lowest_common_ancestor(tree* node, tree* p, tree* q);

tree* add_to_bst(int array[], int start, int end);

tree* create_minimal_bst(int arr[], int size);

tree* create_rand_tree(int count, int min, int max);

void is_bst(tree* node);

int tree_size(tree* node);

int max_depth(tree* node);

int min_depth(tree* node);

bool is_balanced(tree* node);

void reverse_order_print(tree* node);

void clear(tree* node);

void print_tree_in_order(tree* node); ;

void print_tree_post_order(tree* node);

void print_tree_pre_order(tree* node);

void print_tree_reverse_order(tree* node);

void path_finder(tree* node, int path[], int level);

bool match_tree(tree* root1, tree* root2);

bool sub_tree(tree* root1, tree* root2);

bool is_sub_tree(tree* root1, tree* root2);

void mirror(tree* root);

void breadth_first_traversal(tree* root);

int get_level(tree* node, int element, int level);

void breadth_first_level_element_print(tree* root, std::vector<std::vector<int>>& vec);

void tree_to_array(tree* node, int array[]);

void level_even_odd(tree* node);
