#include <iostream>

using namespace std;

int main() {

string months = "          January   February  March     April     May       June      July      August    September October   November  December   ";

int input;

int monthsCalc;

cout << "Enter the month in number (an integer between 1 and 12): ";

cin >> input;

monthsCalc = input * 10;

cout << "The month name is: " << months.substr(monthsCalc, 9) << endl;

}