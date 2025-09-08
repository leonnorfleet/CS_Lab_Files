#include <iostream>

using namespace std;

int main () {

    int x1, x2, x3, x4;

    cout << "Enter four integers(separated by spaces): ";

    cin >> x1 >> x2 >> x3 >> x4;

    if(x1 == x2 && x3 == x4 || x1 == x4 && x2 == x3 || x1 == x3 && x2 == x4) {

        cout << "Two pairs.\n";

    } else if(x1 == x2 || x2 == x3 || x3 == x4 || x1 == x4 || x2 == x4 || x1 == x3) {

        cout << "One pair.\n";

    } else {
        
        cout << "There are no pairs.\n";
    }

    return 0;

}