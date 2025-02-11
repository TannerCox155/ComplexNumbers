// P03ComplexNumbers complex.h
//
// Written: Tanner Cox
// Date: Fall 2024
// CS-318

#ifndef COMPLEX_H
#define COMPLEX_H

class complex {
public: 
	// Constructors

		// Default Contructor - initialize the complex number to (0,0)
	complex() : re(0), im(0) {}
		// Single Argument Constructor - Set the real part (re) to 'a' and the imaginary part (im) to 0
	complex(double a) : re(a), im(0) {}
		// Dual Argument Constructor - initialize re and im
	complex(double a, double b) : re(a), im(b) {}
		// Copy Constructor - To copy data from an existing object
	complex(const complex& c) : re(c.re), im(c.im) {}

	// Assignment Operation (=)
		// Copy values from rhs object and return reference to current object

		/*
		This overloads the assignment operator (=).
		It assigns values from rhs (the right-hand side) to the
		current object if its not the same object, and then returns the current object.
		*/
	complex& operator =(const complex& rhs) {
		if (this != &rhs) {
			re = rhs.re;
			im = rhs.im;
		}
		return *this;
	}

	// Class complex member arithmetic and additional assignment operators +=, -=, *=, /=
		// Returns reference to current object

	complex& operator +=(const complex& z) {
		re += z.re;
		im += z.im;
		return *this;
	}
	complex& operator -=(const complex& z) {
		re -= z.re;
		im -= z.im;
		return *this;
	}
	complex& operator *=(const complex& z) {
		re *= z.re;
		im *= z.im;
		return *this;
	}
	complex& operator /=(const complex& z) {
		double denom = z.real() * z.real() + z.imag() * z.imag(); // c^2 + d^2
		double newReal = (re * z.real() + im * z.imag()) / denom;  // (ac + bd) / (c^2 + d^2)
		double newImag = (im * z.real() - re * z.imag()) / denom;  // (bc - ad) / (c^2 + d^2)

		re = newReal;
		im = newImag;

		return *this; 
	}
	
	complex& operator +=(const double z) {
		re += z;
		return *this;
	}
	complex& operator -=(const double z) {
		re -= z;
		return *this;
	}
	complex& operator *=(const double z) {
		re *= z;
		return *this;
	}
	complex& operator /=(const double z) {
		re /= z;
		im /= z;

		return *this;
	}

	// Accessors
	double real() const { return re; }
	double imag() const { return im; }
	double magnitude() const { return std::sqrt(re * re + im * im); }

private:
	double re, im; // Cartesian canonical form
};

// Binary Arithmetic Helper Functions
	/*
	These functions define how to add, subtract, multiply, and divide
	complex numbers and handle operations with doubles as well.
	They create and return a new complex object with the result.
	*/

complex operator+(const complex& z1, const complex& z2) {
	double real = z1.real() + z2.real();
	double imag = z1.imag() + z2.imag();

	return complex(real, imag);
}
complex operator+(const complex& z1, const double x) {
	double real = z1.real() + x;
	double imag = z1.imag();

	return complex(real, imag);
}
complex operator+(const double x, const complex& z) {
	double real = z.real() + x;
	double imag = z.imag();

	return complex(real, imag);
}

complex operator-(const complex& z1, const complex& z2) {
	double real = z1.real() - z2.real();
	double imag = z1.imag() - z2.imag();

	return complex(real, imag);
}
complex operator-(const complex& z1, const double x) {
	double real = z1.real() - x;
	double imag = z1.imag();

	return complex(real, imag);
}
complex operator-(const double x, const complex& z) {
	double real = x - z.real();
	double imag = z.imag();

	return complex(real, imag);
}
	// (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
complex operator*(const complex& z1, const complex& z2) {
	double real = z1.real() * z2.real() - z1.imag() * z2.imag();
	double imag = z1.real() * z2.imag() + z1.imag() * z2.real();
	return complex(real, imag);
}
complex operator*(const complex& z1, const double x) {
	double real = z1.real() * x;
	double imag = z1.imag() * x;

	return complex(real, imag);
}
complex operator*(const double x, const complex& z) {
	double real = z.real() * x;
	double imag = z.imag() * x;

	return complex(real, imag);
}
	// (a + bi) / (c + di) = [(ac + bd) / (c^2 + d^2)] + [(bc - ad) / (c^2 + d^2)]i
complex operator/(const complex& z1, const complex& z2) {
	double denom = z2.real() * z2.real() + z2.imag() * z2.imag();
	double real = (z1.real() * z2.real() + z1.imag() * z2.imag()) / denom;
	double imag = (z1.imag() * z2.real() - z1.real() * z2.imag()) / denom;

	return complex(real, imag);
}
complex operator/(const complex& z1, const double x) {
	double real = z1.real() / x;
	double imag = z1.imag() / x;

	return complex(real, imag);
}
complex operator/(const double x, const complex& z) {
	double real = z.real() / x;
	double imag = z.imag() / x;

	return complex(real, imag);
}

// Unary Arithmetic Helper Functions:

	// These overload the unary operators + (which returns the number itself) and - (which returns the negation of the complex number).
complex operator+(const complex& z) {
	return z;
}
complex operator-(const complex& z) {
	return complex(-z.real(), -z.imag());
}

	// These overload == and != to compare two complex numbers based on their real and imaginary parts.
bool operator==(const complex & z1, const complex & z2) {
	return (z1.real() == z2.real()) && (z1.imag() == z2.imag());
}
bool operator!=(const complex& z1, const complex& z2) {
	return !(z1 == z2);
}

// Input/Output Helper Functions:

	// input and parse complex literals of form: (a, b)
	// where a and b are both read as type double literals. 

	/*
	The input operator allows reading a complex number in the format (a, b),
	the output operator allows printing a complex number in the same format.
	*/
std::istream& operator>>(std::istream& in, complex& z) {
	char ch;
	double real, imag;

	in >> ch >> real >> ch >> imag >> ch;

	z = complex(real, imag);

	return in;
}
	
std::ostream& operator<<(std::ostream& out, const complex& z) {
	out << "(" << z.real() << ", " << z.imag() << ")";
	return out;
}

// Other Helper Functions
double magnitude(const complex& z) {
	return sqrt(pow(z.real(), 2) + pow(z.imag(), 2));
}
double real(const complex& z) {
	return z.real();
}
double imag(const complex& z) {
	return z.imag();
}
	// Convert from polar coordinates (r, theta) to Cartesian coordinates
	// rcos(theta) + rsin(theta)
	// converts polar coordinates (magnitude and angle) to a complex number
complex polar(const double r, const double theta) {
	return complex(r * cos(theta), r * sin(theta));
} 
	// Constructs a complex via polar coords.
	// Overload of polar constructs a complex number from the magnitude r, with an angle of 0
complex polar(const double r) {
	return complex(r, 0);
}
	// Returns the conjugate of complex number
complex conj(const complex& z) { 
	return complex(z.real(), -z.imag()); 
} 
	// Returns squared magnitude (absolute) value of z
double norm(const complex& z) {
	return pow(z.real(), 2) + pow(z.imag(), 2);
} 
	// Returns arg (theta) value of complex number z
double arg(const complex& z) {
	return atan2(z.imag(), z.real());
} 

#endif