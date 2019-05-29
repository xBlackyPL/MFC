#include <iostream>
#include "RobsonAlgorithm.h"

robson_tree::robson_tree(tree* root): visit_type_()
{
	this->root_ = root;
	previous_ = present_ = root;
	top_ = stack_ = nullptr;
}

robson_tree& robson_tree::operator=(const robson_tree&) = default;

robson_tree& robson_tree::operator=(robson_tree&&) noexcept = default;

void robson_tree::in_visit()
{
	visit_type_ = visit_type::in_order;
	std::cout << std::endl << "Robson Algorithm InOrder: " << std::endl;
	start();
}

void robson_tree::post_visit()
{
	visit_type_ = visit_type::post_order;
	std::cout << std::endl << "Robson Algorithm PostOrder: " << std::endl;
	start();
}

void robson_tree::pre_visit()
{
	visit_type_ = visit_type::pre_order;
	std::cout << std::endl << "Robson Algorithm PreOrder: " << std::endl;
	start();
}

void robson_tree::start()
{
	auto move_value = 0;
	while (true)
	{
		if (move_value == 0)
		{
			if ((present_->left == nullptr) && (present_->right == nullptr))
			{
				std::cout << present_->data << " ";
				avail_ = present_;
			}
			else
			{
				if (present_->left != nullptr)
				{
					if (visit_type_ == visit_type::pre_order)
					{
						std::cout << present_->data << " ";
					}
					next_ = present_->left;
					present_->left = previous_;
					previous_ = present_;
					present_ = next_;
					continue;
				}
				if (visit_type_ == visit_type::pre_order)
				{
					std::cout << present_->data << " ";
				}
				else if (visit_type_ == visit_type::in_order)
				{
					std::cout << present_->data << " ";
				}
				next_ = present_->right;
				present_->right = previous_;
				previous_ = present_;
				present_ = next_;
				continue;
			}
		}
		move_value = 0;
		if (present_ == root_)
		{
			return;
		}
		if (previous_->right == nullptr)
		{
			if (visit_type_ == visit_type::in_order)
			{
				std::cout << previous_->data << " ";
			}
			else if (visit_type_ == visit_type::post_order)
			{
				std::cout << previous_->data << " ";
			}
			next_ = previous_->left;
			previous_->left = present_;
			present_ = previous_;
			previous_ = next_;
			move_value = 1;
			continue;
		}
		if (previous_->left == nullptr)
		{
			if (visit_type_ == visit_type::post_order)
			{
				std::cout << previous_->data << " ";
			}
			next_ = previous_->right;
			previous_->right = present_;
			present_ = previous_;
			previous_ = next_;
			move_value = 1;
			continue;
		}
		if (previous_ == top_)
		{
			if (visit_type_ == visit_type::post_order)
			{
				std::cout << previous_->data << " ";
			}
			next_ = stack_;
			top_ = stack_->right;
			stack_ = stack_->left;
			next_->left = next_->right = nullptr;
			next_ = previous_->left;
			previous_->left = previous_->right;
			previous_->right = present_;
			present_ = previous_;
			previous_ = next_;
			move_value = 1;
			continue;
		}

		if (visit_type_ == visit_type::in_order)
		{
			std::cout << previous_->data << " ";
		}
		avail_->left = stack_;
		avail_->right = top_;
		stack_ = avail_;
		top_ = previous_;
		next_ = previous_->right;
		previous_->right = present_;
		present_ = next_;
	}
}