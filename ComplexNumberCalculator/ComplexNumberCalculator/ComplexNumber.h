#pragma once
#include <ostream>
#include <iostream>

class complex_number
{
private:
	double real_{};
	double imaginary_{};
public:
	complex_number();
	complex_number(double, double);
	complex_number(const complex_number&);
	complex_number(complex_number&&) noexcept;
	complex_number& operator=(const complex_number&);
	complex_number& operator=(complex_number&&) noexcept;
	~complex_number();

	double get_real() const;
	double get_imaginary() const;
	void set_real(double real);
	void set_imaginary(double imaginary);
	double modulus() const;
	complex_number conjugate() const;

	complex_number& operator+=(const complex_number& complex);
	complex_number& operator-=(const complex_number& complex);
	complex_number& operator*=(const complex_number& complex);
	complex_number& operator/=(const complex_number& complex);

	friend complex_number operator+(const complex_number& complex1, const complex_number& complex2);
	friend complex_number operator-(const complex_number& complex1, const complex_number& complex2);
	friend complex_number operator*(const complex_number& complex1, const complex_number& complex2);
	friend complex_number operator/(const complex_number& complex1, const complex_number& complex2);

	friend std::istream& operator>>(std::istream& input_stream, complex_number& complex);
	friend std::ostream& operator<<(std::ostream& outputs_stream, const complex_number& complex);
};
