#include "stdafx.h"
#include "ComplexNumber.h"
#include <complex>

complex_number::complex_number() = default;

complex_number::~complex_number() = default;

complex_number::complex_number(const complex_number& complex) = default;

complex_number& complex_number::operator=(const complex_number& complex) = default;

complex_number::complex_number(const double real, const double imaginary) :
	real_(real), imaginary_(imaginary)
{
}

complex_number::complex_number(complex_number&& complex) noexcept :
	real_(complex.real_), imaginary_(complex.imaginary_)
{
}

complex_number& complex_number::operator=(complex_number&& complex) noexcept
{
	this->real_ = complex.real_;
	this->imaginary_ = complex.imaginary_;
	return *this;
}

double complex_number::get_real() const
{
	return real_;
}

double complex_number::get_imaginary() const
{
	return imaginary_;
}

void complex_number::set_real(const double real)
{
	real_ = real;
}

void complex_number::set_imaginary(const double imaginary)
{
	imaginary_ = imaginary;
}

double complex_number::modulus() const
{
	return std::sqrtl(real_ * real_ + imaginary_ * imaginary_);
}

complex_number complex_number::conjugate() const
{
	return complex_number(real_, imaginary_ * (-1));
}

complex_number& operator+=(complex_number& left, const complex_number& complex)
{
	left.real_ += complex.real_;
	left.imaginary_ += complex.imaginary_;
	return left;
}

complex_number& operator-=(complex_number& left, const complex_number& complex)
{
	left.real_ -= complex.real_;
	left.imaginary_ -= complex.imaginary_;
	return left;
}

complex_number& operator*=(complex_number& left, const complex_number& complex)
{
	left.real_ = left.real_ * complex.real_ - left.imaginary_ * complex.imaginary_;
	left.imaginary_ = left.real_ * complex.imaginary_ + complex.real_ * left.imaginary_;
	return left;
}

complex_number& operator/=(complex_number& left, const complex_number& complex)
{
	const auto denominator = complex.real_ * complex.real_ + complex.imaginary_ * complex.imaginary_;
	if (denominator < 0)
	{
		left.real_ = 0;
		left.imaginary_ = 0;
		return left;
	}
	left.real_ = (left.real_ * complex.real_ + left.imaginary_ * complex.imaginary_) / denominator;
	left.imaginary_ = (left.imaginary_ * complex.real_ - left.real_ * complex.imaginary_) / denominator;
	return left;
}

complex_number operator+(const complex_number& complex1, const complex_number& complex2)
{
	return complex_number(complex1.real_ + complex2.real_, complex1.imaginary_ + complex2.imaginary_);
}

complex_number operator-(const complex_number& complex1, const complex_number& complex2)
{
	return complex_number(complex1.real_ - complex2.real_, complex1.real_ - complex2.imaginary_);
}

complex_number operator*(const complex_number& complex1, const complex_number& complex2)
{
	return complex_number(
		complex1.real_ * complex2.real_ - complex1.imaginary_ * complex2.imaginary_,
		complex1.real_ * complex2.imaginary_ + complex2.real_ * complex1.imaginary_);
}

complex_number operator/(const complex_number& complex1, const complex_number& complex2)
{
	const auto denominator = complex2.real_ * complex2.real_ + complex2.imaginary_ * complex2.imaginary_;
	if (denominator < 0)
	{
		complex_number(0, 0);
	}
	return complex_number(
		(complex1.real_ * complex2.real_ + complex1.imaginary_ * complex2.imaginary_) / denominator,
		(complex1.imaginary_ * complex2.real_ - complex1.real_ * complex2.imaginary_) / denominator);
}

std::ostream& operator<<(std::ostream& outputs_stream, const complex_number& complex)
{
	outputs_stream << "Real: " << std::to_string(complex.get_real()) << std::endl;
	outputs_stream << "Imaginary: " << std::to_string(complex.get_imaginary()) << std::endl;
	return outputs_stream;
}

std::istream& operator>>(std::istream& input_stream, complex_number& complex)
{
	std::cout << "Real Part: ";
	input_stream >> complex.real_;
	std::cout << "Imaginary Part: ";
	input_stream >> complex.imaginary_;
	return input_stream;
}
