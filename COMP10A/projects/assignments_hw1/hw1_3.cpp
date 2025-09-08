#include <iostream>
#include <cmath>

using namespace std;

int main() {

    double input1, input2;

    cout << "Enter your first number from 0 to 100000: ";

    cin >> input1;

    cout << "Enter your second number from 0 to 100000: ";

    cin >> input2;

        double sum = input1 + input2;

        double difference = input1 - input2;

        long long product = input1 * input2; // using long long because other variables result in overflow

        double average = (input1 + input2) / 2;

    cout << "Their sum is " << sum << endl;

    cout << "Their difference is " << difference << endl;

    cout << "Their product is " << product << endl;

    cout << "Their average is " << average << endl;

    return 0;
}