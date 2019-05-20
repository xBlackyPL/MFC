#pragma once

class double_threaded_binary_tree
{
public:
	struct dt_tree
	{
		int value;
		dt_tree* left;
		dt_tree* right;
		int l_tag;
		int r_tag;
	};

	double_threaded_binary_tree();

	~double_threaded_binary_tree() = default;

	double_threaded_binary_tree(double_threaded_binary_tree&);

	double_threaded_binary_tree(double_threaded_binary_tree&&) noexcept;

	double_threaded_binary_tree& operator=(const double_threaded_binary_tree&);

	double_threaded_binary_tree& operator=(double_threaded_binary_tree&&) noexcept;

	void rand_insert(int count, int min, int max);

	void insert(int data);

	bool find_val(int data) const;

	void print_in_order() const;

	static dt_tree* find_next_in_order(dt_tree* current);

private:

	dt_tree* head_;
	int direction_left_{};
	int direction_right_{};
};
