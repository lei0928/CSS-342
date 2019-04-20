#include "complex.h"
// assign real and imaginary
complex::complex(double r, double i){
	real = r;
	imaginary = i;
}

// getter of real
double complex::getReal() {
	return real;
}

// getter of imaginary
double complex::getImaginary() {
	return imaginary;
}

// operator+
// overloaded +: addition of 2 complexes, current object and parameter
complex complex::operator+(const complex& a) const {
	complex t;
	t.real = real + a.real;
	t.imaginary = imaginary + a.imaginary;
	return t;
}
// operator-
// overloaded +: subtraction of 2 complexes, current object and parameter
complex complex::operator-(const complex& s) const {
	complex t;
	t.real = real - s.real;
	t.imaginary = imaginary - s.imaginary;
	return t;
}

// operator*
// overloaded +: multiplication of 2 complexes, current object and parameter
complex complex::operator*(const complex& m) const {
	complex t;
	t.real = real * m.real - imaginary * m.imaginary;
	t.imaginary = real * m.imaginary + imaginary * m.real;
	return t;
}

// operator/
// overloaded +: division of 2 complexes, current object and parameter
complex complex::operator/(const complex& d) const {
	complex t;
	const double denominator = d.real * d.real +  d.imaginary * d.imaginary;
	if (denominator == 0) {
			cout << "Divided by Zero: Return with no change"<<endl;
			t.real = real;
			t.imaginary = imaginary;
	} else {
		t.real = (real * d.real + imaginary * d.imaginary) / denominator;
		t.imaginary = (imaginary * d.real - real * d.imaginary) / denominator;
	}
	return t;
}

// conjuate of x+yi is x-yi
complex complex::conjugate() {
	return complex(getReal(), -getImaginary());
}

// operator==
// overloaded ==: true if current object == parameter, otherwise false
bool complex::operator==(const complex &c) const {
	if ((real == c.real) && (imaginary == c.imaginary)) {
		return true;
	}
	else {
		return false;
	}
}

// operator!=
// overloaded !=: true if current object != parameter, otherwise false
bool complex::operator!=(const complex &c) const {
	if ((real != c.real) && (imaginary != c.imaginary)) {
		return true;
	}
	else {
		return false;
	}
}


// operator+=
// overloaded +=: current object = current object + parameter
complex& complex::operator+=(const complex &c) {
	this->real += c.real;
	this->imaginary += c.imaginary;
	return *this;
}

// operator-=
// overloaded -=: current object = current object - parameter
complex& complex::operator-=(const complex &c) {
	this->real -= c.real;
	this->imaginary -= c.imaginary ;
	return *this;
}

// operator*=
// overloaded *=: current object = current object * parameter
complex& complex::operator*=(const complex &c) {
	double originalReal = real;

	this->real = (real * c.real) - (imaginary * c.imaginary);
	this->imaginary = (originalReal * c.imaginary) + (imaginary * c.real);
	return *this;
}

// operator/=
// overloaded /=: current object = current object / parameter
complex& complex::operator/=(const complex &c) {
	const double denominator = c.real * c.real +  c.imaginary * c.imaginary;
	if (denominator == 0) {
				cout << "Divided by Zero: Return with no change" << endl;
				this->real = real;
				this->imaginary = imaginary;
		} else {
			this->real = (real * c.real + imaginary * c.imaginary) / denominator;
			this->imaginary = (imaginary * c.real - real * c.imaginary) / denominator;
		}
	return *this;
}

// overloaded <<: prints "Divided by zero: Return with no change" if the denominator is zero, only prints numerator's value
// otherwise uses "+" "-" "*" "/"
ostream& operator << (ostream &output, const complex &c) {
	if (c.real == 0 && c.imaginary ==0) {
		output << "0";
	} else if (c.imaginary == 0){
	    output << c.real;
	} else if (c.real == 0 && c.imaginary != 0){
		if (c.imaginary == 1) {
			output << "i";
		} else if (c.imaginary == -1) {
			output << "-i";
		} else {
		output << c.imaginary << "i";
		}
	} else if (c.real == 1) {
	    output << "1";
	} else if (c.imaginary > 0 ) {
		if (c.imaginary == 1) {
			output << c.real << "+" << "i";
		} else {
		output << c.real << "+" << c.imaginary << "i";
		}
    } else if (c.imaginary < 0) {
    	output << c.real << c.imaginary << "i";
    }

	return output;
}

// overloaded >>: takes 2 doubles as real and imaginary
istream& operator >> (istream &input, complex &c) {
	input >> c.real;
	input >> c.imaginary;
	return input;
}

