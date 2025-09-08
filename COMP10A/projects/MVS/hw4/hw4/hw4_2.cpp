#include <iostream>
#include <string>

using namespace std;

int main() {

	string input;

	string lowAlph = "abcdefghijklmnopqrstuvwxyz";

	string upAlph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	string iChar;

	string lowChar;

	string upChar;

	int largestNum = 0;

	string largestChar;

	cout << "Please enter a string: ";

	getline(cin, input, '\n');

	for(int i = 0; i < lowAlph.length(); i++) {

		int count = 0;

		for (int n = 0; n < input.length(); n++) {

			iChar = input.substr(n, 1);

			lowChar = lowAlph.substr(i, 1);

			upChar = upAlph.substr(i, 1);

			if (lowChar == iChar || upChar == iChar) {

				count++;

			}

		}

		if (count > largestNum) {

			largestNum = count;

			largestChar = lowChar;

		}
		else if (count == largestNum) {

			largestChar = largestChar + lowChar;

		}

	}

	cout << "The most frequently occuring letter(s) is: " << largestChar << endl;
		
	return 0;
}