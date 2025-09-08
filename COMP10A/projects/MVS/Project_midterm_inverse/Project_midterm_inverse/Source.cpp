#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

	int a = 0, b = 0, c = 0;

	cout << "Enter 3 positive integer(s): ";

	cin >> a >> b >> c;

	if ((a % b == 0) && (a % c == 0)) {

		cout << a << " " << "is divisible by both" << " " << b << " " << "and" << " " << c;
	}
	else {

		if ((a % b == 0)) {

			cout << a << " is divisible by " << b << " only" << endl;

		}
		else {

			b = c;

			if ((a % b == 0)) {

				cout << a << " is divisible by " << b << " only" << endl;

			}
			else {

				cout << a << " " << "is not divisible by both" << " " << b << " " << "and" << " " << c;

			}
		}

	}




	return 1;
}

//Answers

/*
srand(time(0))

int x = rand() % (21) - 10;

cout << x << endl;
*/
///////
/*
double aFunction(double x, double eps) {
	if (x < -eps) return x + eps;
	if (x > eps) return x - eps;
}
*/
///////
/*
	int o = 0;

	const double X = 0;

	const double EPSILON = 1E-14;

	cout << aFunction(X, EPSILON) << endl;
*/
///////
/*
double alternatingInverseSum(int N) {

	double sign = 1.0;

	double sum = 0;

	if (N <= 0) {

		return 0;

	}
	else {

		for (double i = 1.0; i <= N; i += 1.0) {

			sum = sum + sign * (1.0 / i);

			sign = -sign;

		}

		return sum;

	}
}
*/
///////
/*
void drawTriangle(int N) {

	for (int i = 0; i < N; i++) {

		int form = N - i;

		cout << setw(2 * form - 1);

		for (int j = 0; j <= 2 * i; j++) {

			cout << "*";
		}

		cout << endl;

	}

}
*/