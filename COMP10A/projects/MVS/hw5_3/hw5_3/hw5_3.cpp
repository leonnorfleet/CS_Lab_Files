// hw5_3.cpp
//

#include <iostream>
#include <cstdlib>
using namespace std;

bool same_set(int a[], int a_size, int b[], int b_size);

void fillArray(int a[], int a_capacity, int& a_size) {
    cout << "Please enter numbers (separated by spaces), Q to quit: ";
    int b;
    while (cin >> b && a_size < a_capacity) {
        a[a_size] = b;
        a_size++;
    }
    cin.clear();
    string item;
    cin >> item;
}

void printArray(int a[], int a_size) {
    for (int i = 0; i < a_size; i++) {
        cout << a[i] << ", ";
    }
    cout << endl;
}

int main()
{
    const int a_capacity = 100;
    const int b_capacity = 100;
    int a_size = 0, b_size = 0;
    int a[a_capacity], b[b_capacity];
    fillArray(a, a_capacity, a_size);
    fillArray(b, b_capacity, b_size);

    printArray(a, a_size);
    printArray(b, b_size);

    cout << "Are these two arrays identical? " <<
        (same_set(a, a_size, b, b_size) ? "Yes" : "No") << endl;


}

// implement your function here
bool same_set(int a[], int a_size, int b[], int b_size) {
    bool is_same_set = false;

    int counter;

    int mismatch = 0;

    for (int i = 0; i < a_size; i++) {

        counter = 0;

        for (int j = 0; j < b_size; j++) {

            if ((a[i] == b[j]) && (mismatch <= 0)) {

                counter++;

                is_same_set = true;

            }

        }

        if (counter <= 0) {

            is_same_set = false;

            mismatch++;

        }

        counter = 0;

    }



    return is_same_set;
}



