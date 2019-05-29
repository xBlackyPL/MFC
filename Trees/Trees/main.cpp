#include <iostream>

#include "stdafx.h"
#include "DoubleThreadedBinaryTree.h"
#include "BinaryTree.h"
#include "RobsonAlgorithm.h"

#define IN_ORDER 
#define POST_ORDER 
#define PRE_ORDER 

int main()
{
	// DOUBLE THREADED TREE
	std::cout << "Double Threaded Tree" << std::endl;
	auto double_threaded_binary = double_threaded_binary_tree();
	double_threaded_binary.unique_random_number_insert(7, 1, 50);
	std::cout << "InOrder" << std::endl;
	double_threaded_binary.print_in_order();
	// std::cout << "PreOrder" << std::endl;
	// double_threaded_binary.print_pre_order();

	// ROBSON ALGORITHM TREE

	std::cout << std::endl << std::endl << "Robson Algorithm" << std::endl;
	const auto root = create_rand_tree(20, 1, 50);
	is_bst(root);

	std::cout << "| Size: \t" << tree_size(root) << std::endl;
	std::cout << "| Max depth: \t" << max_depth(root) << std::endl;
	std::cout << "| Min depth: \t" << min_depth(root) << std::endl;

	robson_tree robson_tree(root);
#ifdef IN_ORDER
	robson_tree.in_visit();
	std::cout << std::endl << "Ordinary Binary Tree InOrder:" << std::endl;
	print_tree_in_order(root);
#endif

#ifdef POST_ORDER
	std::cout << std::endl;
	robson_tree.post_visit();
	std::cout << std::endl << "Ordinary Binary Tree PostOrder:" << std::endl;
	print_tree_post_order(root);
#endif

#ifdef PRE_ORDER
	std::cout << std::endl;
	robson_tree.pre_visit();
	std::cout << std::endl << "Ordinary Binary Tree PreOrder:" << std::endl;
	print_tree_pre_order(root);
#endif
	clear(root);
	std::cout << std::endl << std::endl;
	return 0;
}
