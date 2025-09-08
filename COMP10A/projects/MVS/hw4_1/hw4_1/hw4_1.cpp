#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    string asterisk = "*";
    string space;
    int input;

    cout << "Enter a positive integer: ";
    cin >> input;

    if (input < 1 || cin.fail()) {

        cout << "Please enter a valid number.";

    }
    else {

        for (int i = 1; i < input; i++) {

            space = space + " ";

        }

        int slength = space.length();

        for (int n = 0; n < input; n++) {


            cout << space.substr(space.length() - slength) + asterisk << endl;

            asterisk = asterisk + "*";

            slength--;

        }

    }

    return 0;

}