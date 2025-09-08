#include <iostream>

using namespace std;

int main() {

	int numbers[5] = { 0, 1, 2, 3, 5 };

	for (int i = 0; i < 5; i++) {

		if (numbers[i] < 0) {
			cout << 0 << endl;
			return 0;
		}


	}

	cout << 1 << endl;

	return 1;

}

/*
	int input;

	string numbers[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

		for (int i = 0; i < 10; i++) {

		cout << "Enter a digit: ";

		cin >> input;

		cout << numbers[input] << endl;

		}
		*/