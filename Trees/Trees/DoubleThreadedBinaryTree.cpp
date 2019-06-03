#include "DoubleThreadedBinaryTree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

double_threaded_binary_tree::double_threaded_binary_tree()
{
	head_ = new double_threaded_tree;
	head_->value = 0;
	head_->l_tag = 0;
	head_->r_tag = 0;
	head_->left = head_->right = head_;
}

double_threaded_binary_tree::double_threaded_binary_tree(double_threaded_binary_tree& copy): head_(nullptr)
{
	std::copy(this->head_, this->head_, copy.head_);
}

double_threaded_binary_tree::double_threaded_binary_tree(double_threaded_binary_tree&& copy) noexcept: head_(nullptr)
{
	std::copy(this->head_, this->head_, copy.head_);
}

double_threaded_binary_tree& double_threaded_binary_tree::operator=(const double_threaded_binary_tree& copy)
{
	std::copy(this->head_, this->head_, copy.head_);
	return *this;
}

double_threaded_binary_tree& double_threaded_binary_tree::operator=(double_threaded_binary_tree&& copy) noexcept
{
	std::copy(this->head_, this->head_, copy.head_);
	return *this;
}

void double_threaded_binary_tree::unique_random_number_insert(const int count, const int min, const int max)
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	const std::uniform_int_distribution<int> uniform_int_distribution(min, max);

	std::cout << "Values:" << std::endl;
	for (auto i = 0; i < count - 1; i++)
	{
		const auto new_val = uniform_int_distribution(generator);
		if (!find_val(new_val))
		{
			insert(new_val);
			std::cout << new_val << " ";
		}
		else
		{
			i--;
		}
	}
	std::cout << std::endl;
}

void double_threaded_binary_tree::insert(const int data)
{
	const auto new_item = new double_threaded_tree;
	new_item->value = data;
	if (head_ == head_->left && head_ == head_->right)
	{
		new_item->left = head_;
		new_item->right = head_;
		head_->left = new_item;
		head_->l_tag = 1;
		new_item->l_tag = 0;
		new_item->r_tag = 0;
	}
	else
	{
		auto current = head_->left;
		while (true)
		{
			if (current->value > new_item->value)
			{
				if (current->l_tag == 0)
				{
					direction_left_ = true;
					direction_right_ = false;
					break;
				}
				current = current->left;
			}
			else
			{
				if (current->r_tag == 0)
				{
					direction_left_ = false;
					direction_right_ = true;
					break;
				}
				current = current->right;
			}
		}
		if (direction_left_)
		{
			new_item->left = current->left;
			current->left = new_item;
			new_item->l_tag = 0;
			new_item->r_tag = 0;
			current->l_tag = 1;
			new_item->right = current;
		}
		else if (direction_right_)
		{
			new_item->right = current->right;
			current->right = new_item;
			new_item->r_tag = 0;
			new_item->l_tag = 0;
			current->r_tag = 1;
			new_item->left = current;
		}
	}
}

bool double_threaded_binary_tree::find_val(const int data) const
{
	auto current = head_->left;
	while (true)
	{
		if (current->value > data)
		{
			if (current->l_tag == 0)
				return false;

			current = current->left;
		}
		else if (current->value == data)
		{
			return true;
		}
		else
		{
			if (current->r_tag == 0)
				return false;

			current = current->right;
		}
	}
}

void double_threaded_binary_tree::print_in_order() const
{
	auto current = head_->left;
	while (current->l_tag == 1)
	{
		current = current->left;
	}
	while (current != head_)
	{
		std::cout << current->value << " ";

		if (current->r_tag == 0)
		{
			current = current->right;
		}
		else
		{
			current = current->right;
			while (current->l_tag != 0)
			{
				current = current->left;
			}
		}
	}
	std::cout << std::endl;
}

void double_threaded_binary_tree::print_pre_order()
{
	auto current = head_;
	do
	{
		current = find_next_pre_order(current);
		std::cout << current->value << " ";
	}
	while (current != head_ && !head_visited_);

	std::cout << std::endl;
	head_visited_ = false;
}

void double_threaded_binary_tree::print_post_order() const
{
	auto current = head_;
	do {
		current = find_next_post_order(current);
		std::cout << current->value << " ";
	} while (current != head_);
	std::cout << std::endl;
}

double_threaded_binary_tree::double_threaded_tree* double_threaded_binary_tree::find_next_in_order(
	double_threaded_tree* current)
{
	if (current->r_tag == 0)
	{
		return current->right;
	}
	current = current->right;
	while (current->l_tag == 1)
	{
		current = current->left;
	}
	return current;
}

double_threaded_binary_tree::double_threaded_tree* double_threaded_binary_tree::find_next_pre_order(
	double_threaded_tree* current)
{
	if (current->l_tag == 1)
	{
		return current->left;
	}

	current = current->right;
	if (current->r_tag == 1)
	{
		current = current->right;
	}

	return current;
}

double_threaded_binary_tree::double_threaded_tree* double_threaded_binary_tree::find_next_post_order(
	double_threaded_tree* current)
{
	if (current->r_tag == 1)
	{
		return current->right;
	}

	current = current->right;
	if (current->l_tag == 1)
	{
		current = current->left;
	}

	return current;
}

double_threaded_binary_tree::double_threaded_tree* double_threaded_binary_tree::in_successor(double_threaded_tree* current)
{
	if (current->r_tag == 0)
	{
		return current->right;
	}
	if (current->r_tag == 1)
	{
		while (current->l_tag == 1)
		{
			current = current->left;
		}
	}
	return current;
}

double_threaded_binary_tree::double_threaded_tree* double_threaded_binary_tree::pre_successor(double_threaded_tree* current)
{
	if (current->l_tag == 1)
	{
		return current->left;
	}

	while (current->r_tag == 1)
	{
		current = current->right;
	}
	return current;
}

double_threaded_binary_tree::double_threaded_tree* double_threaded_binary_tree::post_successor(double_threaded_tree* current)
{
	if (current->r_tag == 1)
	{
		return current->left;
	}

	while (current->l_tag == 1)
	{
		current = current->right;
	}
	return current;
}
