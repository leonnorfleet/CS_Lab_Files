#include <iostream>

using namespace std;

int main() {

    int inputMinutes;

    cout << "Enter a number of minutes: ";

    cin >> inputMinutes;

    int minutes = (30 + inputMinutes) % 60;

    int hours = (11 + (30 + inputMinutes) / 60) % 12;

    cout << "Minutes after 11:30 is: " << hours << ":" << minutes;

    return 0;

}