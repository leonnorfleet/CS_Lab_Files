#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

double a, b, c;

double solutionPos;

double solutionNeg;

cout << "Quadratic Equation Solver: ax^2 + bx + c = 0" << endl;

cout << "Please enter three values a, b, and c (seperated by spaces): ";

cin >> a >> b >> c;

if (a == 0) {

    if (b == 0) {

        if (c == 0) {

            cout << "There are infinite solutions\n";

        } else {
            
            cout << "There is no solution\n";

        }

    }

    if (b != 0) {

        cout << fixed << setprecision(4) << "There is one real solution: " << -c / b << endl;

    }

}

if (a != 0) {

    if ((pow(b, 2) - 4 * a * c) < 0) {

        cout << "There is no real solution\n";

    } else if ((pow(b, 2) - 4 * a * c) == 0) {

        cout << fixed << setprecision(4) << "There is one real solution: " << -b / (2 * a) << endl;

    } else if ((pow(b, 2) - 4 * a * c) > 0) {

        solutionPos = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);

        solutionNeg = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);

        cout << fixed << setprecision(4) << "There are two real solutions: " << solutionPos << " and " << solutionNeg << endl;
    }

}

    return 0;
}