#include <iostream>
#include <cmath> //informed of this by the Big C++ Book, page 39

using namespace std;

//a box that is 8.5 by 11 inches
// this is 215.9 by 279.4 millimeters
const double length = 279.4;
const double width = 215.9;

int main() {

    double perimeter = 2 * length + 2 * width;
    double area = length * width;
    double diagonal = sqrt(length * length + width * width);

    cout << "The perimeter is: " << perimeter << endl;

    cout << "The area is: " << area << endl;

    cout << "The diagonal is: " << diagonal << endl;

    return 0;

}