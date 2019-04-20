#ifndef COMPLEX_H_
#define COMPLEX_H_
#include <iostream>
using namespace std;

class complex {

	// overloaded <<: prints "Divided by zero: Return with no change" if the denominator is zero, only prints numerator's value
	// otherwise uses "+" "-" "*" "/"
	friend ostream& operator << (ostream& output, const complex&);
	// overloaded >>: takes 2 doubles as real and imaginary
	friend istream& operator >> (istream& input, complex&);

public:
    // default constructor: parameters are real and imaginary
	complex(double = 0.0, double = 0.0);

    // getters
	double getReal();
	double getImaginary();

    // arithmetic operators
	complex operator+(const complex &) const; // add 2 complexes
	complex operator-(const complex &) const; // subtract 2 complexes
	complex operator*(const complex &) const; // multiply 2 complexes
	complex operator/(const complex &) const; // divide 2 complexes

	// assignment operators
	complex& operator+=(const complex &);     // current object += parameter
	complex& operator-=(const complex &);     // current object += parameter
	complex& operator*=(const complex &);     // current object += parameter
	complex& operator/=(const complex &);     // current object += parameter

	// conjugate of the complex number
	complex conjugate();

	// boolean comparison operators
	bool operator==(const complex &) const;   // is object == parameter?
	bool operator!=(const complex &) const;   // is object != parameter?

private:

	// members of variable
	double real;
	double imaginary;

};

#endif /* COMPLEX_H_ */
