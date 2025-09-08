#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    string a = "a"; //1
    //subtract by 1 when using even character count strings

    string b = a+a; //2
    string c = b+b; // 4
    string d = c+c; //18
    string e = d+d; // 16
    string f = e+e; //32
        cout << f;

}