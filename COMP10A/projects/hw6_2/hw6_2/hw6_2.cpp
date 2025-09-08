// hw6_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int DIM2 = 6;

void fill2DArray(double a[][DIM2], int DIM1) {
    for (int i = 0; i < DIM1; i++) {
        for (int j = 0; j < DIM2; j++) {
            // generate a number between 0 and 1
            a[i][j] = double(rand()) / RAND_MAX;
        }
    }
}

void fillArray(double a[], int DIM2) {
    for (int i = 0; i < DIM2; i++) {
        a[i] = double(rand()) / RAND_MAX;
    }
}

void print2DArray(const double a[][DIM2], int dim1) {
    cout << fixed << setprecision(4);
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < DIM2; j++) {
            cout << setw(8) << a[i][j];
        }
        cout << endl;
    }
}

void printArray(const double a[], int dim) {
    cout << fixed << setprecision(4);
    for (int i = 0; i < dim; i++) {
        cout << setw(8) << a[i];
    }
    cout << endl;
}

void mat_vec_mul(double mat[][DIM2], double vec[], double result[], int dim);

int main()
{
    const int DIM1 = 8;

    double mat[DIM1][DIM2];
    double vec[DIM2];

    fill2DArray(mat, DIM1);
    cout << "Matrix A = " << endl;
    print2DArray(mat, DIM1);

    fillArray(vec, DIM2);
    cout << "\nvector b = " << endl;
    printArray(vec, DIM2);

    double result[DIM1];
    mat_vec_mul(mat, vec, result, DIM1);
    cout << "\nresult A*b = " << endl;
    printArray(result, DIM1);
}

// implement your function here
void mat_vec_mul(double mat[][DIM2], double vec[], double result[], int dim1) {

    double holder = 0;

    for (int i = 0; i < dim1; i++) {

        holder = 0;

        for (int j = 0; j < 6; j++) {

            holder = holder + mat[i][j] * vec[j];

            //cout << result[i] << ", ";

        }

        result[i] = holder;

    }

}


