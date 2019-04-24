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

	void set_real(double);
	void set_imaginary(double);

	double modulus() const;
	complex_number conjugate() const;

	friend complex_number& operator+=(complex_number&,const complex_number&);
	friend complex_number& operator-=(complex_number&,const complex_number&);
	friend complex_number& operator*=(complex_number&,const complex_number&);
	friend complex_number& operator/=(complex_number&,const complex_number&);

	friend complex_number operator+(const complex_number&, const complex_number&);
	friend complex_number operator-(const complex_number&, const complex_number&);
	friend complex_number operator*(const complex_number&, const complex_number&);
	friend complex_number operator/(const complex_number&, const complex_number&);

	friend std::istream& operator>>(std::istream&, complex_number&);
	friend std::ostream& operator<<(std::ostream&, const complex_number&);
};
