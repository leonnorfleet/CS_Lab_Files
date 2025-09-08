#include <iostream>

using namespace std;

int main() {

    string input;

    cout << "Enter a number between 1,000,000 and 999,999,999: ";

    cin >> input;

    int spacer = input.length() - 7;

    int spacer2 = input.length() - 3;

    cout << input.substr(0, input.length() - 8) << input.substr(spacer, 3) << input.substr(spacer2, 3) << endl;
    
}