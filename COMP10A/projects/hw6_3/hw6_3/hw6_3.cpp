// hw6_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
using namespace std;

void safe_strnAppend(char str1[], char str2[], int size1, int n);

int main()
{
    const int CAPACITY = 40;
    char cStr0[] = "first string,";
    char cStr1[CAPACITY];
    strcpy(cStr1, cStr0);
    cout << cStr1 << endl;

    char cStr2[] = "sec,ond string,";
    char cStr3[] = "third string,";
    char cStr4[] = "forth string,";

    safe_strnAppend(cStr1, cStr2, CAPACITY, 4);
    cout << cStr1 << endl;

    safe_strnAppend(cStr1, cStr3, CAPACITY, 20);
    cout << cStr1 << endl;

    safe_strnAppend(cStr1, cStr4, CAPACITY, 20);
    cout << cStr1 << endl;
}

// implement your function here
void safe_strnAppend(char str1[], char str2[], int size1, int n) {

    int str1_len = strlen(str1);

    int m = size1 - str1_len - 1;

    int p = strlen(str2);

    int list[] = { n, p, m };

    int smallest = list[0];

    for (int i = 0; i < 3; i++) {

        if (smallest > list[i]) {

            smallest = list[i];

        }

    }

    if (smallest > 0) {

        for (int i = 0; i < smallest; i++) {

            str1[str1_len + i] = str2[i];

        }

    }


}



