#pragma once

class double_threaded_binary_tree
{
public:
	struct dt_tree
	{
		int value;
		dt_tree* left;
		dt_tree* right;
		unsigned l_tag : 1;
		unsigned r_tag : 1;
	};

	double_threaded_binary_tree();

	~double_threaded_binary_tree() = default;

	double_threaded_binary_tree(double_threaded_binary_tree&);

	double_threaded_binary_tree(double_threaded_binary_tree&&) noexcept;

	double_threaded_binary_tree& operator=(const double_threaded_binary_tree&);

	double_threaded_binary_tree& operator=(double_threaded_binary_tree&&) noexcept;

	void unique_random_number_insert(int, int, int);

	void insert(int);

	bool find_val(int) const;

	void print_in_order();

	void print_pre_order();

	void print_post_order();

	dt_tree* find_next_in_order(dt_tree*);

	dt_tree* find_next_pre_order(dt_tree*);

	dt_tree* find_next_post_order(dt_tree*);

private:
	bool head_visited_ = false;
	dt_tree* head_;
	bool direction_left_{};
	bool direction_right_{};
};
