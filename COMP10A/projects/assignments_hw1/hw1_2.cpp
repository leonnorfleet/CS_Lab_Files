#include <iostream>
#include <cmath>

using namespace std;

int main() {

    int seconds;

    cin >> seconds;

    int minutes = seconds / 60;

    seconds = seconds % 60;
    
    int hours = minutes / 60;

    minutes = minutes % 60;

    cout << hours << " hours " << minutes << " minutes " << seconds << " seconds" << endl;

    return 0;
}