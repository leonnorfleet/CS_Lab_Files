#include <iostream>

using namespace std;

int main() {

    string input;

    cout << "Enter a single character from the alphabet: ";

    cin >> input;

    if((input >= "a" && input <= "z" || input >= "A" && input <= "Z") && input.length() == 1) {

        if(input > "@" && input < "B" || input > "D" && input < "F" || input > "H" && input < "H" || input > "N" && input < "P" || input > "T" && input < "V") {

            cout << "Vowel\n";

        } else if (input > "`" && input < "b" || input > "d" && input < "f" || input > "h" && input < "j" || input > "n" && input < "p" || input > "t" && input < "v"){

            cout << "Vowel\n";

        } else {

            cout << "Consonant\n";

        }

    } else {

        cout << "Please enter a valid character.\n";

    }

return 0;
    
}