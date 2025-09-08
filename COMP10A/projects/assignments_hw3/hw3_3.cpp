#include <iostream>
#include <string>

using namespace std;

int main() {

    long long input;

    string s_input;

    cout << "Please enter a positive integer: ";

    cin >> input;

    if (cin.fail() || input < 0) {

        cout << "Please enter a viable integer.\n";

    } else {

        while(input > 0) {

            s_input = s_input + to_string(input % 2);

            input = input / 2;

        }

        int i = s_input.length();

        while (i > 0) {

            cout << s_input.substr(i - 1, 1);

            i--;
        }

    }

    return 0;

}