// hw5_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

// function prototype
long long Fibonacci(int n);

int main() {
    cout << "Please enter a positive number: ";
    int num;
    cin >> num;
    cout << "The " << num << "_th Fibonacci number is: " << Fibonacci(num) << endl;

    return 0;
}

// your implementation goes here
// you need to check input validation:
// if n<=0, return 0
// if n>0, compute and return the Fibonacci number
long long Fibonacci(int n) {

    if (n >= 1) {

        long long fold1 = 1;
        long long fold2 = 1;

        for (int i = 1; i < n; i++) {

            long long fnew = fold1 + fold2;

            fold2 = fold1;

            fold1 = fnew;

        }

        return fold2;

    }
    else {

        n = 0;

        return n;

    }

}