#include <iostream>

using namespace std;

int main() {

	/*for (int i = 0; i < 10; i++) {

		cout << "*";

	}*/

	int input;

	cout << "Enter a number: ";

	cin >> input;

	for (int i = input; i > 0; i--) {

		for (int n = 0; n < i; n++) {

			cout << "*";

		}

		cout << endl;

	}

	for (int j = 1; j < input; j++) {

		for (int m = 0; m <= j; m++) {

			cout << "*";
		}

		cout << endl;

	}

}