// hw6_1.cpp
//

#include <iostream>
#include <cstdlib>
using namespace std;

void bar_chart(double values[], int size);

void fillArray(double a[], int a_capacity, int& a_size) {
    cout << "Please enter numbers (separated by spaces), Q to quit: ";
    double b;
    while (cin >> b && a_size < a_capacity) {
        a[a_size] = b;
        a_size++;
    }
    cin.clear();
    string item;
    cin >> item;
}

void printArray(double a[], int a_size) {
    for (int i = 0; i < a_size; i++) {
        cout << a[i] << ", ";
    }
    cout << endl;
}

int main()
{
    const int a_capacity = 100;
    int a_size = 0;
    double a[a_capacity];
    fillArray(a, a_capacity, a_size);

    printArray(a, a_size);

    bar_chart(a, a_size);

}

// implement your function here
void bar_chart(double values[], int size) {

    double max = 0;
    int maxLoc = values[0];

    for (int n = 1; n <= size; n++) {

        if (values[n] > max) {
            max = values[n];
            maxLoc = n;
        }

    }

    double propor = (max / 20);

    for (int i = 20; i > 0; i--) {

            for (int j = 0; j < size; j++) {

                if ( (values[j]) >= (i * propor) ) {

                    cout << "*";

                }
                else {

                    cout << " ";

                }

            }

            cout << endl;

        }

}
