#include <iostream>

#include <cmath>

using namespace std;

int main() {

    int inputHeight;

    cout << "Enter your height in inches: ";

    cin >> inputHeight;

    int heightFeet = inputHeight / 12;

    double heightInches = inputHeight % 12;

    cout << "Your height is: " << heightFeet << " feet " << heightInches << endl;

    return 0;
}