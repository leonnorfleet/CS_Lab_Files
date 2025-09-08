#include <iostream>

using namespace std;

int main() {

    int testnum;

    cout << "Your number is: ";

    cin >> testnum;
    if(testnum > 7) {
        cout << "Sadly, you are not very smart.." << endl;
    } else {
        cout << "Intelligence is in your future!" << endl;
    }
    return 0;
}