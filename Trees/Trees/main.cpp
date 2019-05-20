#include "stdafx.h"
#include "DoubleThreadedBinaryTree.h"
#include <iostream>

int main()
{
	std::cout << std::endl << std::endl << "Double Threaded Tree" << std::endl;
	auto double_threaded_binary = double_threaded_binary_tree();
	double_threaded_binary.rand_insert(20, 1, 50);
	std::cout << "InOrder" << std::endl;
	double_threaded_binary.print_in_order();
	return 0;
}
