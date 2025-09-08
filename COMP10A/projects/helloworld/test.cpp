#include <iostream>

using namespace std;

int main() {

    int inputNum;

    cin >> inputNum;

    int minute = inputNum / 60;

    int remainder = inputNum % 60;

    cout << minute << " " << remainder;

}