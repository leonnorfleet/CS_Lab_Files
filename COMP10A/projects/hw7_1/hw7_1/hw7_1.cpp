// Homework7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
using namespace std;

int* unique(const int A[], int size_A, int& size_unique);

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
        cout << setw(5) << a[i];
    }
    cout << endl;
}

int main()
{
    const int CAPACITY = 100;
    int size = 0;
    int arr[CAPACITY];
    fillArray(arr, CAPACITY, size);

    cout << "arr =\n";
    printArray(arr, size);

    // call function unique
    int size_unique = 0;
    int* unique_set = unique(arr, size, size_unique);

    cout << "\nUnique elements of arr =\n";
    printArray(unique_set, size_unique);
}

// implement your function here
int* unique(const int A[], int size_A, int& size_unique) {

    int n = size_A;

    int* uni = new int[n];

    int count = 0;

    for (int i = 0; i < n; i++) {

        int j;

        for (j = 0; j < i; j++) {

            if (A[i] == A[j]) {

                break;

            }

        }

        if (i == j) {

            size_unique++;

            uni[count] = A[i];

            count++;

        }

    }

    int* arr = new int[size_unique];

    for (int k = 0; k < size_unique; k++) {

        arr[k] = uni[k];

    }

    delete[] uni;


    return arr;
}