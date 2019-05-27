#include "stdafx.h"
#include "DoubleThreadedBinaryTree.h"
#include <iostream>

int main()
{
	std::cout << "Double Threaded Tree" << std::endl;
	auto double_threaded_binary = double_threaded_binary_tree();
	double_threaded_binary.unique_random_number_insert(7, 1, 50);
	std::cout << "InOrder" << std::endl;
	double_threaded_binary.print_in_order();
	std::cout << "PreOrder" << std::endl;
	double_threaded_binary.print_pre_order();
	return 0;
}
