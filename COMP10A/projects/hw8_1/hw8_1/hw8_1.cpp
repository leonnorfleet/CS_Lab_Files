#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <math.h>
using namespace std;
const double PI = 3.141592653589793238;

class ComplexNumber {
private:
	double real, imag;
public:
	// constructor
	ComplexNumber() {
		real = 0;
		imag = 0;
	}

	ComplexNumber(double a, double b) {
		real = a;
		imag = b;
	}

	ComplexNumber(const ComplexNumber& obj) {
		this->real = obj.real;
		this->imag = obj.imag;
	}

	// accessors
	double realPart() const {
		return real;
	}
	double imagPart() const {
		return imag;
	}
	double norm() const {
		double norm = sqrt(((real * real) + (imag * imag)));
		return norm;
	}
	void display() const {
		if (imag >= 0) {
			if (imag == 1) {
				cout << real << "+" << "i" << endl;
			}
			else {	
				cout << real << "+" << imag << "i" << endl;
			}
		}
		else {
			if (imag == -1) {
				cout << real << "-" << "i" << endl;
			}
			else {
				cout << real << imag << "i" << endl;
			}
		}
	}
	double angle() const {
		double angle = atan2(real, imag);
		if (angle >= -PI && angle <= PI) {
			return angle;
		}
		else {
			cout << "Invalid Angle";
		}
	}

	// mutators
	void set_real(double re) {
		real = re;
	}
	void set_imag(double im) {
		imag = im;
	}
	void set_value(double re, double im) {
		real = re;
		imag = im;
	}
	void add(const ComplexNumber& z) {
		this->real = this->real + z.real;
		this->imag = this->imag + z.imag;
	}
	void subtract(const ComplexNumber& z) {
		this->real = this->real - z.real;
		this->imag = this->imag - z.imag;
	}
	void multiply(const ComplexNumber& z) {
		double re = (this->real * z.real) - (this->imag * z.imag);
		double im = (this->real * z.imag + z.real * this->imag);
		set_value(re, im);
	}
	void multiply(const double scalar) {
		real = real * scalar;
		imag = imag * scalar;
	}
	ComplexNumber conjugate() {
		return ComplexNumber(real, imag * -1);
	}
};

ComplexNumber add(const ComplexNumber& z1, const ComplexNumber& z2) {
	double re = z1.realPart() + z2.realPart();
	double im = z1.imagPart() + z2.imagPart();

	return ComplexNumber(re, im);
}
ComplexNumber subtract(const ComplexNumber& z1, const ComplexNumber& z2) {
	double re = z1.realPart() - z2.realPart();
	double im = z1.imagPart() - z2.imagPart();

	return ComplexNumber(re, im);
}
ComplexNumber multiply(const ComplexNumber& z1, const ComplexNumber& z2) {
	double re = z1.realPart() * z2.realPart();
	double im = z1.imagPart() * z2.imagPart();

	return ComplexNumber(re, im);
}

int main()
{
	ComplexNumber z1;
	ComplexNumber z2(2.0, 3.0);
	ComplexNumber z3(3.0, -4.0);
	ComplexNumber z4(z3);

	cout << "Test member functions\n";
	cout << "z1 = ";
	z1.display();  //should display 0+0i
	cout << "z2 = ";
	z2.display();  //should display 2+3i
	cout << "real(z2) = " << z2.realPart() << endl; //should display 2;
	cout << "imag(z2) = " << z2.imagPart() << endl; //should display 3;
	cout << "z3 = ";
	z4.display();  //should display 3-4i
	cout << endl;

	cout << "norm(z2) = " << z2.norm() << endl;
	cout << endl;

	cout << "z2 + z3 = ";
	z2.add(z3);    //should display 5-i
	z2.display();

	z2.set_value(2.0, 3.0);
	cout << "z2 - z3 = ";
	z2.subtract(z3);  //should display -1+7i
	z2.display();

	z2.set_value(2.0, 3.0);
	cout << "z2 * z3 = ";
	z2.multiply(z3);
	z2.display();     //should display 18+i

	z2.set_value(2.0, 3.0);
	cout << "2*z2 = ";
	z2.multiply(2.0);
	z2.display();     //should display 4+6i

	z2.set_value(2.0, 3.0);
	ComplexNumber z2_conj = z2.conjugate();
	cout << "conj(z2) = ";
	z2_conj.display();   //should display 2-3i

	cout << endl;

	ComplexNumber z5(1.0, 0);
	cout << "angle( 1+0i) = " << z5.angle() << endl;

	z5.set_real(0); z5.set_imag(1.0);
	cout << "angle( 0+1i) = " << z5.angle() << endl;

	z5.set_value(-1.0, 0);
	cout << "angle(-1+0i) = " << z5.angle() << endl;

	z5.set_value(0.0, -1.0);
	cout << "angle( 0-1i) = " << z5.angle() << endl;

	z5.set_value(1.0, 1.0);
	cout << "angle( 1+1i) = " << z5.angle() << endl;

	z5.set_value(-1.0, 1.0);
	cout << "angle(-1+1i) = " << z5.angle() << endl;

	z5.set_value(-1.0, -1.0);
	cout << "angle(-1-1i) = " << z5.angle() << endl;

	z5.set_value(1.0, -1.0);
	cout << "angle( 1-1i) = " << z5.angle() << endl;

	cout << endl << "Test non-member functions\n";
	ComplexNumber z6 = add(z2, z3);
	cout << "z6 = z2 + z3 = ";
	z6.display();

	ComplexNumber z7 = subtract(z2, z3);
	cout << "z7 = z2 - z3 = ";
	z7.display();

	ComplexNumber z8 = multiply(z2, z3);
	cout << "z8 = z2 * z3 = ";
	z8.display();

}
