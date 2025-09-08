// hw8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

vector <int> merge(const vector<int>& a, const vector<int>& b) {
    vector <int> c;
    int val_a = 0;
    int val_b = 0;
    int largest;
    int smallest;
    int selector;// 0 is a, 1 is b
    int f_selector;// for the extra numbers; 0 is a, 1 is b

    for (int i = 0; i < a.size(); i++) {
        val_a++;
    }

    for (int i = 0; i < b.size(); i++) {
        val_b++;
    }

    if (val_b > val_a) {
        largest = val_b;
        smallest = val_a;
        selector = 0;
        f_selector = 1;
    }
    else if (val_a > val_b) {
        largest = val_a;
        smallest = val_b;
        selector = 1;
        f_selector = 0;
    }
    else {
        largest = val_a;
        smallest = val_a;
        selector = 0;
    }

    for (int i = 0; i < smallest; i++) {
        if (selector == 0) {
            c.push_back(a[i]);
            c.push_back(b[i]);
        }
        else if (selector == 1) {
            c.push_back(b[i]);
            c.push_back(a[i]);
        }
    }

    if (largest - smallest > 0) {
        if(f_selector == 0) {
            for (int i = 0; i < largest - smallest; i++) {
                c.push_back(a[smallest + i]);
            }
        } else if (f_selector == 1) {
            for (int i = 0; i < largest - smallest; i++) {
                c.push_back(b[smallest + i]);
            }
        }
    }

    return c;
}

template<class type>
void fillVector(vector<type>& vec) {
    cout << "Please enter numbers (separated by spaces), Q to quit: ";
    int b;
    while (cin >> b) {
        vec.push_back(b);
    }
    cin.clear();
    string item;
    cin >> item;
}

template <class type>
void printVector(const vector<type>& vec) {
    cout << "vector = {";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
}

int main()
{
    vector<int> vec1;
    vector<int> vec2;
    fillVector(vec1);
    fillVector(vec2);
    printVector(vec1);
    printVector(vec2);

    vector<int> vec3 = merge(vec1, vec2);
    printVector(vec3);
}