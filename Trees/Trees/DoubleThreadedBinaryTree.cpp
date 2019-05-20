#include "DoubleThreadedBinaryTree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

double_threaded_binary_tree::double_threaded_binary_tree()
{
	head_ = new dt_tree;
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

void double_threaded_binary_tree::rand_insert(const int count, const int min, const int max)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	std::cout << "Values:" << std::endl;
	for (auto i = 0; i < count - 1; i++)
	{
		const auto new_val = rand() % (max - min + 1) + min;
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
	const auto new_item = new dt_tree;
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
		current = find_next_in_order(current);
	}
	std::cout << std::endl;
}

double_threaded_binary_tree::dt_tree* double_threaded_binary_tree::find_next_in_order(dt_tree* current)
{
	if (current->r_tag == 0)
	{
		return current->right;
	}
	current = current->right;
	while (current->l_tag != 0)
	{
		current = current->left;
	}
	return current;
}