#include <iostream>

using namespace std;

void printArray(int a[], int size) {

	cout << "[";

	for (int i = 0; i < 10; i++) {

		cout << a[i];

		if (i == (size - 1) ) {

			break;

		}
		else {

			cout << ", ";

		}

	}

	cout << "]" << endl;

}

int main() {

	/*
		1. a set to 15
			b set to 20
			pointer p set to the address of a
			pointer p value set to 20
			a set to 20

		2. b set to 538
			pointer a set to address of b
			pointer a value set to 10
			b set to 10
			value at address (a + 1) is set to 11


	*/

}

//int a[10] = { 5, 13, 5, -8, 3, 5, 2, 1, 0, 17};